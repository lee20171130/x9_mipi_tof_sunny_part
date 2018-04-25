/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

#pragma once

#include <system/toolsIO.hpp>
#include <processing/processing.hpp>
#include <processing/processingInternal.hpp>
#include <common/calibration.hpp>
#include <common/CompUtils.hpp>
#include <processing/algorithm/ref/initCalcAutoExposure.hpp>
#include <processing/common/processingInit.hpp>
#include <SDM450RDIHALInterface.h>
//#include <video.h>

extern "C" {
    bool sunnyGetSingleFreqMode();
}
extern SDM450RDIHALInterface *pTof4Sunny; 

inline bool spectreLegacyParameterLoad (SpectreParameter **params, std::string path)
{
    *params = reinterpret_cast<SpectreParameter *> (malloc (sizeof (SpectreParameter)));
    memset (*params, 0, sizeof (SpectreParameter));

    float temp;
    uint32_t boolTemp{};

    pmd_loadScalar (path + "/param_Type.bin", & ( (*params)->type));
    pmd_loadScalar (path + "/param_Version.bin", & ( (*params)->version));

    int32_t type = 0;
    pmd_loadScalar (path + "/param_AdaptiveNoiseFilterType.bin", &type);
    (*params)->adaptiveNoiseFilterType = static_cast<uint8_t> (type);
    pmd_loadScalar (path + "/param_AmplitudeThreshold.bin", & ( (*params)->amplitudeThreshold));
    pmd_loadScalar (path + "/param_ConsistencyTolerance.bin", & ( (*params)->consistencyTolerance));
    pmd_loadScalar (path + "/param_FlyingPixelF0.bin", & ( (*params)->flyingPixel.f0));
    pmd_loadScalar (path + "/param_FlyingPixelF1.bin", & ( (*params)->flyingPixel.f1));
    pmd_loadScalar (path + "/param_FlyingPixelFarDist.bin", & ( (*params)->flyingPixel.farDist));
    pmd_loadScalar (path + "/param_FlyingPixelNearDist.bin", & ( (*params)->flyingPixel.nearDist));
    pmd_loadScalar (path + "/param_LowerSaturationThreshold.bin", &temp);
    (*params)->saturationThreshold.lower = (uint16_t) temp;
    pmd_loadScalar (path + "/param_UpperSaturationThreshold.bin", &temp);
    (*params)->saturationThreshold.upper = (uint16_t) temp;

    pmd_loadScalar (path + "/param_MPIAmpThreshold.bin", & ( (*params)->mpi.amplitudeThreshold));
    pmd_loadScalar (path + "/param_MPIDistThreshold.bin", & ( (*params)->mpi.distanceThreshold));
    pmd_loadScalar (path + "/param_MPINoiseDistance.bin", & ( (*params)->mpi.noiseDistance));
    pmd_loadScalar (path + "/param_NoiseThreshold.bin", & ( (*params)->noiseThreshold));
    pmd_loadScalar (path + "/param_ReferenceAmplitude.bin", & ( (*params)->exposureReferenceAmplitude));

    // Algorithm Parameters
    pmd_loadScalar (path + "/param_UseAdaptiveNoiseFilter.bin", &boolTemp);
    (*params)->config.useAdaptiveNoiseFilter = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseAutoExposure.bin", &boolTemp);
    (*params)->config.useAutoExposure = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseRemoveFlyingPixel.bin", &boolTemp);
    (*params)->config.useRemoveFlyingPixel = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagAverage.bin", &boolTemp);
    (*params)->config.useMPIFlagAverage = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagAmplitude.bin", &boolTemp);
    (*params)->config.useMPIFlagAmplitude = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseMPIFlagDistance.bin", &boolTemp);
    (*params)->config.useMPIFlagDistance = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;
    pmd_loadScalar (path + "/param_UseValidateImage.bin", &boolTemp);
    (*params)->config.useValidateImage = boolTemp > 0 ? (uint8_t) 1 : (uint8_t) 0;

    // New parameters not supported in legacy format
    (*params)->config.useSparsePointCloud = 0;
    (*params)->config.useRemoveStrayLight = 0;

    return true;
}

inline bool spectreLegacyOutputInit (SpectreOutput **ps_output, SpectreParameter *ps_param, SpectreCalibration *ps_calib)
{
    *ps_output = reinterpret_cast<SpectreOutput *> (malloc (sizeof (SpectreOutput)));
    memset (*ps_output, 0, sizeof (SpectreOutput));
    uint_fast32_t numPixel = ps_param->inputConfig.numCols * ps_param->inputConfig.numRows;

    (*ps_output)->numColumns = ps_param->inputConfig.numCols;
    (*ps_output)->numRows = ps_param->inputConfig.numRows;
    (*ps_output)->pm_amplitude = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_amplitude, 0, sizeof (float) *numPixel);
    (*ps_output)->pm3d_coord = (float *) malloc (numPixel * 4 * sizeof (float));
    memset ( (*ps_output)->pm3d_coord, 0, sizeof (float) * 3 * numPixel);
    (*ps_output)->pm_distance = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_distance, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_distanceNoise = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_distanceNoise, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_intensity = (float *) malloc (numPixel * sizeof (float));
    memset ( (*ps_output)->pm_intensity, 0, sizeof (float) *numPixel);
    (*ps_output)->pm_flags = (uint32_t *) malloc (numPixel * sizeof (uint32_t));
    memset ( (*ps_output)->pm_flags, 0, sizeof (uint32_t) *numPixel);

    memset ( (*ps_output)->pm_intensity, 0, sizeof (float) *numPixel);

    return true;
}

//added by zhudm
inline void shift4Bit2Right(uint16_t *pSrc, uint16_t *pDst, size_t numPixel)
{

    for (uint32_t p_idx = 0; p_idx < numPixel; p_idx++)
    {
        *pDst = (*pSrc >> 4);
        pDst++;
        pSrc++;
    }
}

inline bool spectreLegacyInputLoad (SpectreInput **ps_input, SpectreParameter *param, std::string path)
{
    bool status = true;
    size_t numPixel = 0;
    bool useSingleFreq = sunnyGetSingleFreqMode();

    (*ps_input) = reinterpret_cast<SpectreInput *> (malloc (sizeof (SpectreInput)));


    uint32_t *sensorROI = nullptr;
    status = pmd_loadArray (path + "/input_SensorROI.bin", &sensorROI) == 4 && status;
    if (!status)
    {
        return status;
    }
    param->inputConfig.numCols = sensorROI[2];
    param->inputConfig.numRows = sensorROI[3];
    numPixel = sensorROI[2] * sensorROI[3];
    free (sensorROI);
    
#if (DEBUG_READ_FILE == 1)
    {
        status = pmd_loadScalar(path + "/input_Temperature.bin", &(*ps_input)->temperature) == 1 && status ? true : false;
        pmd_printf("read TEMPERATURE from fake binary = %f\n", (*ps_input)->temperature);
    }
#else
    {
    #if 0
        (*ps_input)->temperature = temperature_read();
        pmd_printf("read TEMPERATURE from hardware = %f\n", (*ps_input)->temperature);
	#else
		float tmp = pTof4Sunny->get_tof_temp();
		(*ps_input)->temperature = tmp;
		pmd_printf("load from real hardware Temp,%f\n", (*ps_input)->temperature);
	#endif
    }
#endif
    uint8_t numFrames;
    status = pmd_loadScalar (path + "/input_NumFrameSets.bin", &numFrames) && status;
    param->inputConfig.numFreqs = numFrames - 1;

    uint32_t count = 0;
#ifndef USE_SUNNY_EEPROM_CALIBRATION_DATA
    status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count++) + ".bin", & ( (*ps_input)->intensity)) == numPixel && status;
    for (auto i = 0; i < param->inputConfig.numFreqs; i++)
    {
        for (uint8_t f_idx = 0; f_idx < SPECTRE_NUM_FRAMES_MODULATED; ++f_idx, ++count)
        {
            if (count > 4)
            {
                status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count) + ".bin", & ( (*ps_input)->modFrames2[f_idx])) == numPixel && status;
            }
            else
            {
                status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count) + ".bin", & ( (*ps_input)->modFrames1[f_idx])) == numPixel && status;
            }
        }
    }
#else
    uint32_t total_frame;
    uint16_t *p_dst, *p_src, *total;

    if(useSingleFreq)
    {
        total_frame = 5;
        param->inputConfig.numFreqs = 1;
    }
    else
    {
        total_frame = 9;
        param->inputConfig.numFreqs = 2;
    }

#if (DEBUG_READ_FILE == 1)
    status = pmd_loadArray (path + "/input_RawData_all_0.bin", &total) == (numPixel * total_frame) && status ? true : false;
#else
    uint32_t framebuf_id, byte_nums;
    // read from camera buf
    total = (uint16_t *)malloc(numPixel * 9 * sizeof(uint16_t));
	pmd_printf("dnx(%d): malloc for tof mipi raw data:%d\n", __LINE__, numPixel * 9 * sizeof(uint16_t));
#if (MIPITOF_USE_MONO_MODE == 1)	
    byte_nums = 224*173*5*2;
#else
    byte_nums = 224*173*9*2;
#endif

	pmd_printf("invoke simt cam hal interface[%s] start\n", "camera_getbuf");
	pTof4Sunny->camera_getbuf((unsigned char *)total, byte_nums, framebuf_id);
	#if 1
	pmd_printf("save unpacked raw mipi tof data to file\n");
#if 0
	pmd_saveArrayToFile ("123", 224*173*9, total/*, "bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc*/);
#endif	
pmd_printf("done\n");
	#endif
	pmd_printf("invoke simt cam hal interface[%s] end, ret=[%d]\n", "camera_getbuf", framebuf_id);
#endif
    //printf("spectreAstonInputLoad path = %s\n", path.c_str());
    if (status == true)
	    printf("dnx(%d): input_RawData_all_0: load data success\n", __LINE__);
    else
	    printf("dnx(%d): input_RawData_all_0: load data fail\n", __LINE__);

    (*ps_input)->intensity = (uint16_t *) malloc(numPixel * sizeof(uint16_t));
    p_dst = (uint16_t *) (*ps_input)->intensity;
    p_src = (uint16_t *) (total + count * numPixel);

    shift4Bit2Right(p_src, p_dst, numPixel);

    count++;

    for (auto i = 0; i < param->inputConfig.numFreqs; i++)
    {
        for (uint8_t f_idx = 0; f_idx < SPECTRE_NUM_FRAMES_MODULATED; ++f_idx, ++count)
        {
            if (count > 4)
            {
//                status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count) + ".bin", & ( (*ps_input)->modFrames2[f_idx])) == numPixel && status;
                (*ps_input)->modFrames2[f_idx] = (uint16_t *) malloc(numPixel * sizeof(uint16_t));
                p_dst = (uint16_t *) (*ps_input)->modFrames2[f_idx];
                p_src = (uint16_t *) (total + count * numPixel);
                shift4Bit2Right(p_src, p_dst, numPixel);
            }
            else
            {
//                status = pmd_loadArray (path + "/input_RawData_" + pmd_numberToString (count) + ".bin", & ( (*ps_input)->modFrames1[f_idx])) == numPixel && status;
                (*ps_input)->modFrames1[f_idx] = (uint16_t *) malloc(numPixel * sizeof(uint16_t));
                p_dst = (uint16_t *) (*ps_input)->modFrames1[f_idx];
                p_src = (uint16_t *) (total + count * numPixel);
                shift4Bit2Right(p_src, p_dst, numPixel);
            }
        }
    }

    free(total);
#endif
    uint32_t *expTimesIn = nullptr;
    if(useSingleFreq)
        status = pmd_loadArray (path + "/input_Single_InExposureTimes.bin", &expTimesIn) == param->inputConfig.numFreqs + 1u;
    else
        status = pmd_loadArray (path + "/input_InExposureTimes.bin", &expTimesIn) == param->inputConfig.numFreqs + 1u;
    if (status)
    {
        std::copy (expTimesIn, expTimesIn + param->inputConfig.numFreqs + 1, PMD_CHECKED_ITERATOR ( (*ps_input)->exposureTimesIn, param->inputConfig.numFreqs+1));
    }
    free (expTimesIn);

    uint32_t *freqs;
    status = pmd_loadArray (path + "/input_Frequencies.bin", &freqs) == 2 + 1u; //zhudm, fix to dual frequence
    if (status)
    {
        std::copy (freqs + 1, freqs + param->inputConfig.numFreqs + 1, PMD_CHECKED_ITERATOR (param->inputConfig.freqs, 2));
    }
    free (freqs);

    return status;
}

//added by zhudm, copy from spectre-v2.6.1
#if 1
inline bool spectreAstonCalibrationLoad (SpectreCalibration **ps_calib, SpectreInput *ps_input, std::string path)
{
    bool status = true;
    size_t size = 0;
    uint8_t sizeProbeData = 2;
    uint32_t freq[] = {80320000, 60240000};
//    uint8_t *posDepthProbe = (uint8_t *) malloc (ps_input->numFrameSets * sizeof (uint8_t));
//
//    for (uint8_t idx = 0; idx < ps_input->numFrameSets; ++idx)
//    {
//        if (ps_input->pv_imagerModes[idx] == 0)
//        {
//            posDepthProbe[sizeProbeData] = idx;
//            sizeProbeData++;
//        }
//    }

    *ps_calib = reinterpret_cast<SpectreCalibration *> (malloc (sizeof (SpectreCalibration)));
    memset (*ps_calib, 0, sizeof (SpectreCalibration));
    (*ps_calib)->sizeProbeData = sizeProbeData;
    (*ps_calib)->pns_probeData = reinterpret_cast<SpectreCalibrationProbeData *> (malloc (sizeof (SpectreCalibrationProbeData) * sizeProbeData));
    memset ( (*ps_calib)->pns_probeData, 0, sizeof (SpectreCalibrationProbeData) * sizeProbeData);

    // dimension information calibrationROI
    status = pmd_loadArray (path + "/calib_CalibrationROI.bin", & ( (*ps_calib)->pv_calibrationROI)) ==  4 && status ? true : false;

    // general information
    status = pmd_loadArray (path + "/calib_date.bin", & ( (*ps_calib)->pc_date)) == 19 && status ? true : false;
    status = pmd_loadArray (path + "/calib_serial.bin", & ( (*ps_calib)->pc_serial)) == 9 && status ? true : false;
    status = pmd_loadArray (path + "/calib_SensorSerial.bin", & ( (*ps_calib)->pc_sensorSerial)) == 19 && status ? true : false;

    status = pmd_loadScalar (path + "/calib_version.bin", & ( (*ps_calib)->version)) == 1 && status ? true : false;
    status = pmd_loadScalar (path + "/calib_type.bin", & ( (*ps_calib)->type)) == 1 && status ? true : false;

    // ps_calib->ation data
    uint32_t width = (*ps_calib)->pv_calibrationROI[2];
    uint32_t height = (*ps_calib)->pv_calibrationROI[3];
    uint32_t numPixel = width * height;

    // directions
    (*ps_calib)->pm3d_directions = (float *) malloc (numPixel * 3 * sizeof (float));
    int16_t *directionsTemp = NULL;
    status = pmd_loadArray (path + "/calib_directions.bin", &directionsTemp) == 3 * numPixel && status ? true : false;
    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        (*ps_calib)->pm3d_directions[ (3 * idx)] = (float) directionsTemp[ (3 * idx)] / (float) INT16_MAX;
        (*ps_calib)->pm3d_directions[ (3 * idx) + 1] = (float) directionsTemp[ (3 * idx) + 1] / (float) INT16_MAX;
        (*ps_calib)->pm3d_directions[ (3 * idx) + 2] = (float) directionsTemp[ (3 * idx) + 2] / (float) INT16_MAX;
    }
    free (directionsTemp);

    // lensparam
    int *lensparamTemp = NULL;
    size = pmd_loadArray (path + "/calib_lensparam.bin", &lensparamTemp);
    (*ps_calib)->sizeLensParam = (uint8_t) size;
    (*ps_calib)->pv_lensparam = (float *) malloc (size * sizeof (float));
    for (size_t idx = 0; idx < size; ++idx)
    {
        (*ps_calib)->pv_lensparam[idx] = (float) lensparamTemp[idx];
//        printf("(*ps_calib)->pv_lensparam[idx] = %f\n", (*ps_calib)->pv_lensparam[idx]);
    }
    free (lensparamTemp);

    // mask
    (*ps_calib)->pm_mask = (uint8_t *) malloc (numPixel * sizeof (uint8_t));
    uint8_t *maskTemp = NULL;
    status = pmd_loadArray (path + "/calib_mask.bin", &maskTemp) == numPixel && status ? true : false;
    for (size_t idx = 0; idx < numPixel; ++idx)
    {
        (*ps_calib)->pm_mask[idx] = maskTemp[idx] != 0 ? true : false;
    }
    free (maskTemp);

    // fpn
    (*ps_calib)->pm_fpn = (float *) malloc (numPixel * sizeof (float));
    uint16_t *fpnTemp = NULL;
    status =  pmd_loadArray (path + "/calib_fpn.bin", &fpnTemp) == numPixel && status ? true : false;
    for (uint32_t i = 0; i < numPixel; ++i)
    {
        (*ps_calib)->pm_fpn[i] = (float) fpnTemp[i] / 16.0f;
    }
    free (fpnTemp);

    for (uint32_t idx = 0; idx < 2; ++idx)
    {
        std::stringstream temp;
        temp << freq[idx];
        std::string calib_req_str = temp.str() + "Hz.bin";
        temp.str ("");

        // frequency
//        (*ps_calib)->pns_probeData[idx].frequency = ps_input->pv_frequencies[posDepthProbe[idx]];
        (*ps_calib)->pns_probeData[idx].frequency = freq[idx];

        // FPPN
        status = pmd_loadArray (path + "/calib_fppn_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pm_fppn)) == numPixel && status ? true : false;

        // TempCompensation
        size = pmd_loadArray (path + "/calib_TempCompensation_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pv_tempCompensation));
        (*ps_calib)->pns_probeData[idx].sizeTempCompensation = (uint8_t) size;

        // NoiseParameter
        size = pmd_loadArray (path + "/calib_NoiseParameter_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].pv_noiseParameter));
        (*ps_calib)->pns_probeData[idx].sizeNoiseParamter = (uint8_t) size;

        // Wiggling correction
        auto numWiggles = pmd_loadArray (path + "/calib_WigglingAmplitude_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_amplitude));
        (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.size = (uint8_t) numWiggles;
        status = pmd_loadArray (path + "/calib_WigglingHarmonic_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_harmonic)) == numWiggles && status ? true : false;
        status = pmd_loadArray (path + "/calib_WigglingPhase_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.pv_phase)) == numWiggles && status ? true : false;
        (*ps_calib)->pns_probeData[idx].ps_phaseWiggling.offset = 0.0f;

        if (sizeProbeData > 1)
        {
            // Amplitude Wiggling correction
            uint32_t numWigglesAmp;
            numWigglesAmp = (uint32_t) pmd_loadArray (path + "/calib_AmplitudeWigglingAmplitude_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_amplitude));
            (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.size = (uint8_t) numWigglesAmp;

            status = pmd_loadArray (path + "/calib_AmplitudeWigglingHarmonic_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_harmonic)) == numWigglesAmp && status ? true : false;
            status = pmd_loadScalar (path + "/calib_AmplitudeWigglingOffset_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.offset)) == 1 && status ? true : false;
            status = pmd_loadArray (path + "/calib_AmplitudeWigglingPhase_" + calib_req_str, & ( (*ps_calib)->pns_probeData[idx].ps_amplitudeWiggling.pv_phase)) == numWigglesAmp && status ? true : false;
        }
    }

//    free (posDepthProbe);

    return status;
}
#endif

inline void spectreAstonInputFree (SpectreInput *ps_input)
{
    if (!ps_input)
    {
        return;
    }

    free (ps_input->intensity);
    for (uint8_t f_idx = 0; f_idx < SPECTRE_NUM_FRAMES_MODULATED; ++f_idx)
    {
        free (ps_input->modFrames1[f_idx]);
        free (ps_input->modFrames2[f_idx]);
    }
    free (ps_input);
}

inline void spectreAstonOutputFree (SpectreOutput *ps_output)
{
    if (!ps_output)
    {
        return;
    }

    free (ps_output->pm_amplitude);
    free (ps_output->pm3d_coord);
    free (ps_output->pm_distance);
    free (ps_output->pm_distanceNoise);
    free (ps_output->pm_flags);
    free (ps_output->pm_intensity);
    free (ps_output);
}

