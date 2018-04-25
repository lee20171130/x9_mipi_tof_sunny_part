/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <sample/spectreSample.hpp>
#include <sample/spectreSampleCalc.hpp>
#include <thread>
#include <processing/processingInternal.hpp>
#include <spectreRrf/SpectreRrfReader.hpp>
#include <processing/legacy/legacyTools.hpp>

#include <sys/time.h>

static __int64_t get_tick_count()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((__int64_t)tv.tv_sec * 1000 + tv.tv_usec/1000);
}
__int64_t start_time, last_time, stage_time;

int sunnySaveDepthToFile(void *data, uint32_t size, char *filename)
{
    struct depthpoint {
        float x;
        float y;
        float z;
        float noise;
    };

    struct depthpoint *p = (struct depthpoint *) data;
    FILE *fp;
    //float val;
    unsigned int i;
    unsigned short tmp;

    fp = fopen(filename, "wb+");
    if (fp) {
        for (i = 0; i < size; i++) {
            tmp = (unsigned short)(p[i].z * 5460); //4096
            fwrite(&tmp, 1, 2, fp);
        }
        fclose(fp);
    }

    return 0;
}

static bool singleFreqMode = false;
void sunnySetSingleFreqMode(bool set)
{
    if(set)
        singleFreqMode = true;
    else
        singleFreqMode = false;
}

bool sunnyGetSingleFreqMode()
{
    return singleFreqMode;
}

/** \brief parses the commandline arguments and writes the given path to data structure
 *
 * \param argc number of command line arguments
 * \param argv command line arguments
 * \param waitOnKey specifies weither a key press event will close the application manually
 * \param data data structure
 */

void parseCommandline (int argc, char **argv, bool &waitOnKey, struct spectre::sample::Data &data)
{
    switch (argc)
    {
        case 0:
        case 1:
            {
                break;
            }
        default:
            {
                for (auto i = 1; i < argc - 1; ++i)
                {
                    std::string input_one = std::string (argv[i]);
                    if (input_one.compare ("-y") == 0)
                    {
                        waitOnKey = false;
                    }
                }
                data.workingDir = std::string (argv[argc - 1]);
                break;
            }
    }
}

/** \brief loads sample binary data
 *
 * \param data structure that containes a valid path to sample binary data
 */
void loadData (struct spectre::sample::Data &data)
{
    const std::string paramDir = "Process_Param";
    const std::string inputDir = "Process_Input";
    const std::string calibDir = "Process_Calib"; //added by zhudm

    pmd_printf ("\n");
    pmd_printf ("Reading sample data from: %s\n", data.workingDir.c_str());
    pmd_printf ("Initialize Memory \n");

    sunnySetSingleFreqMode(false);
    // initializiation
    // TODO SK: Remove with PP-650
    spectreLegacyParameterLoad (&data.ps_param, data.workingDir + "/" + paramDir);
    spectreLegacyInputLoad (&data.ps_input, data.ps_param, data.workingDir + "/" + inputDir);

    uint8_t *calibBlob;
#ifndef USE_SUNNY_EEPROM_CALIBRATION_DATA
    auto calibSize = pmd_loadArray (data.workingDir + "/calibration.scl", &calibBlob);
#else
    auto calibSize = pmd_loadArray (data.workingDir + "/" + calibDir + "/eeprom.bin", &calibBlob);
#endif
    std::ifstream roifile (data.workingDir + "/" + calibDir + "/calib_CalibrationROI.bin", std::fstream::binary  | std::fstream::in);
    if(!roifile.good())
    {
        pmd_printf("Calibration file not exist, read eeprom!\n");
        spectre_readCalibration (calibBlob, calibSize, &data.ps_calib);
    }
    else
    {
        pmd_printf("Calibration file exist!\n");
        spectreAstonCalibrationLoad (&data.ps_calib, data.ps_input, data.workingDir + "/" + calibDir);
    }

    data.numFrames = 1;

    free (calibBlob);
}

/** \brief runs spectre processing
 *
 * \param data data structure inititialized by loadData
 */

void runProcessing (struct spectre::sample::Data &data)
{
    pmd_printf ("\n");
    pmd_printf ("Run spectre processing\n");

    // start_time = get_tick_count();
    spectreAstonRun (data.ps_input, data.ps_calib, data.ps_param, data.ps_inter, data.ps_output);
    // last_time = get_tick_count()-start_time;
    // printf("\n--spectreAstonRun---exec time :%8.6f ms\n ", (float)last_time);
}

int spectre_produce(unsigned int exposureTime)
{
    struct spectre::sample::Data data;
    struct spectre::sample::Calculation calcData;

    start_time = get_tick_count();
    loadData (data);
    stage_time = get_tick_count();
    printf("======= Load Data time cost :%8.6f ms\n", (float)(stage_time-start_time));
    spectre::sample::initSpectre (data);
    last_time = get_tick_count();
    printf("======= initSpectre time cost :%8.6f ms\n", (float)(last_time-stage_time));

    // run and print sample calculation
    runProcessing (data);
    stage_time = get_tick_count();
    printf("======= runProcessing time cost :%8.6f ms\n", (float)(stage_time-last_time));

    spectre::sample::calcMeanDistanceAndValidPixels ( (uint32_t) data.ps_output->numColumns * (uint32_t) data.ps_output->numRows,
            data.ps_output->pm_distance,
            data.ps_output->pm_flags,
            calcData);
    last_time = get_tick_count();
    printf("======= calcMeanDistanceAndValidPixels time cost :%8.6f ms\n", (float)(last_time-stage_time));
    spectre::sample::printMeanDistanceAndValidPixels (calcData);

    last_time = get_tick_count() - start_time;
    printf("======= Total Spectre Run time cost :%8.6f ms\n", (float)last_time);

#ifdef USE_SUNNY_EEPROM_CALIBRATION_DATA
    sunnySaveDepthToFile((void *)data.ps_output->pm3d_coord, 224*172, "output_depth.bin");
#else
    sunnySaveDepthToFile((void *)data.ps_output->pm3d_coord, 224*168, "output_depth.bin");
#endif

    spectre::sample::freeMemory (data);
    return 0;
}

int main (int argc, char **argv)
{
    // struct spectre::sample::Data data;
    // struct spectre::sample::Calculation calcData;

    // auto waitOnKey = true;
    // parseCommandline (argc, argv, waitOnKey, data);

    pmd_printf ("PMD Spectre Sample for C API\n");
    pmd_printf ("Version: ");
    pmd_printf ("%s \n", spectre_getVersion());
    pmd_printf ("\n");
    pmd_printf ("\n");

    pmd_printf ("Test Operation Mode MODE_9_5FPS_2000: \n");
    pmd_printf ("===================================== \n");

    // loadData (data);
    // spectre::sample::initSpectre (data);

    // // run and print sample calculation
    // runProcessing (data);
    // spectre::sample::calcMeanDistanceAndValidPixels ( (uint32_t) data.ps_output->numColumns * (uint32_t) data.ps_output->numRows,
    //         data.ps_output->pm_distance,
    //         data.ps_output->pm_flags,
    //         calcData);
    // spectre::sample::printMeanDistanceAndValidPixels (calcData);
    
    // spectre::sample::freeMemory (data);

    // start_time = get_tick_count();
    spectre_produce(0);
    // last_time = get_tick_count() - start_time;
    // printf("\n--spectre_produce---exec time :%8.6f ms\n ", (float)last_time);

    pmd_printf ("\n");
    pmd_printf ("======================== \n");
    pmd_printf ("\n");
    pmd_printf ("\n");
    pmd_printf ("Spectre_sample finished succesfully. \n");
    pmd_printf ("\n");
    pmd_printf ("======================== \n");

    // if (waitOnKey)
    // {
    //     pmd_printf ("\n");
    //     pmd_printf ("Press any key to close the application. \n");
    //     std::cin.ignore();
    // }

    return 0;
}
