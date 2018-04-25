/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#include <sample/spectreSampleCalc.hpp>

#include <spectreRrf/SpectreRrfReader.hpp>

#include <processing/legacy/legacyTools.hpp>

#if defined(ANDROID)
#define SPECTRE_PATH "/data/sunny/hand"
#else
#define SPECTRE_PATH "../../data/sunny/hand"
#endif
const std::string strPath = SPECTRE_PATH;
std::string spectre::sample::getDefaultDataPath()
{
//    SystemIOReal io;
//    auto exeDir = pmd_getDirectory (io.getOwnExePath());
//    std::string subPath (char_CAST (DATA_PATH));
//    return exeDir + subPath;
    return strPath;
}

void spectre::sample::initSpectre (struct Data &data)
{
    spectreLegacyOutputInit (&data.ps_output, data.ps_param, data.ps_calib);
    auto initRes = spectreAstonInit (data.ps_param, data.ps_calib, &data.ps_inter);
    if (initRes != SPECTRE_PROCESSING_SUCCESS)
    {
        pmd_printf ("Could not initialize processing. Return code was: %d", initRes);
        pmd_printf ("\n");
        throw "Processing init failed!";
    }
}

void spectre::sample::freeMemory (struct Data &data)
{
    pmd_printf ("\n");
    pmd_printf ("Free Memory \n");

    spectreAstonFree (data.ps_inter);
    spectre_freeCalibration (data.ps_calib);
    free (data.ps_param);
    spectreAstonOutputFree (data.ps_output);
    spectreAstonInputFree (data.ps_input);
}

void spectre::sample::calcMeanDistanceAndValidPixels (uint32_t numPixels, float *distances, uint32_t *flags, struct Calculation &calcData)
{
    pmd_printf ("\n");
    pmd_printf ("Run Calculation of mean distance and valid pixels\n");

    for (uint32_t i = 0; i < numPixels; i++)
    {
        if (!flags[i])
        {
            calcData.meanDistance += distances[i];
            calcData.numValidPixels++;
        }
    }

    calcData.meanDistance /= (float) calcData.numValidPixels;
}

void spectre::sample::calcMinAndMaxDistance (uint32_t numPixels, struct Calculation &calcData, float *coords)
{
    pmd_printf ("\n");
    pmd_printf ("Run Calculation of minimum and maximum distance\n");

    for (size_t idx = 0; idx < numPixels; idx++)
    {
        if (coords[3 + 4 * idx] != 0.0f)
        {
            calcData.minDistance = coords[2 + 4 * idx];
            calcData.maxDistance = calcData.minDistance;
            break;
        }
    }
    for (size_t idx = 0; idx < numPixels; idx++)
    {
        if (coords[3 + 4 * idx] != 0.0f)
        {
            if (calcData.minDistance > coords[2 + 4 * idx])
            {
                calcData.minDistance = coords[2 + 4 * idx];
            }
            if (calcData.maxDistance < coords[2 + 4 * idx])
            {
                calcData.maxDistance = coords[2 + 4 * idx];
            }
        }
    }
}

void spectre::sample::printMeanDistanceAndValidPixels (struct Calculation &calcData)
{
    pmd_printf ("Valid Pixel: %d \n", calcData.numValidPixels);
    pmd_printf ("Mean distance: %f \n", calcData.meanDistance);
}

void spectre::sample::printMinAndMaxDistance (struct Calculation &calcData)
{
    pmd_printf ("Minimal distance: %f \n", calcData.minDistance);
    pmd_printf ("Maximal distance: %f \n", calcData.maxDistance);
}
