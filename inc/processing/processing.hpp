/****************************************************************************\
* Copyright (C) 2016 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

/**
 * \defgroup libprocessing libprocessing - Spectre Data Processing
 *
 * @brief Implementation of the Spectre ToF - Data processing to compute depth data from the sensor's raw input.
 * @{
 */


#pragma once

#include <stdint.h>
#include <stddef.h>
#include <float.h>
#include <processing/SpectreProcessingStatus.hpp>
#include <common/defines.h>
#include <processing/common/processingExport.hpp>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38F
#endif // FLT_MAX

#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38F
#endif // FLT_MIN

// Constants
#define PMD_INVALID 0;
#define SPECTRE_MAX_NUM_FREQS 2
#define SPECTRE_NUM_FRAMES_INTENSITY 1
#define SPECTRE_NUM_FRAMES_MODULATED 4

/// invalid flag
static const uint32_t PMD_FLAG_INVALID = 0x00000001u;
/// saturation flag
static const uint32_t PMD_FLAG_SATURATED = 0x00000002u;
/// inconsistency flag
static const uint32_t PMD_FLAG_INCONSISTENT = 0x00000004u;
/// low signal flag
static const uint32_t PMD_FLAG_LOW_SIGNAL = 0x00000008u;
/// flying pixel flag
static const uint32_t PMD_FLAG_FLYINGPIXEL = 0x00000010u;
/// Masked flag
static const uint32_t PMD_FLAG_MASKED = 0x00000020u;
/// mpi amplitude
static const uint32_t PMD_FLAG_MPI_DIST = 0x00000040u;
/// mpi distance
static const uint32_t PMD_FLAG_MPI_AMP = 0x00000080u;
/// mask
static const uint32_t PMD_MASK_ILLUMINATION = 0x00000001u;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MPI_AMP = PMD_FLAG_INVALID | PMD_FLAG_MPI_AMP;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MPI_DIST = PMD_FLAG_INVALID | PMD_FLAG_MPI_DIST;
static const uint32_t PMD_COMBINED_FLAG_INVALID_INCONSISTENT = PMD_FLAG_INVALID | PMD_FLAG_INCONSISTENT;
static const uint32_t PMD_COMBINED_FLAG_INVALID_LOWSIGNAL = PMD_FLAG_INVALID | PMD_FLAG_LOW_SIGNAL;
static const uint32_t PMD_COMBINED_FLAG_INVALID_MASKED = PMD_FLAG_INVALID | PMD_FLAG_MASKED;
static const uint32_t PMD_COMBINED_FLAG_INVALID_SATURATED = PMD_FLAG_INVALID | PMD_FLAG_SATURATED;
static const uint32_t PMD_COMBINED_FLAG_INVALID_FLYINGPIXEL = PMD_FLAG_INVALID | PMD_FLAG_FLYINGPIXEL;

/**
*   @brief Container of input values for depth data calculation
*/
struct SpectreInput
{
    float temperature; ///< Handle to the measured temperature value for systematic error compensation ( d0:1 )
    uint16_t *intensity; ///< Intensity frame set (d1:sensorROI[2]*sensorROI[3])
    uint16_t *modFrames1[SPECTRE_NUM_FRAMES_MODULATED];  ///< Modulated frame sets for first frequency (d0:4 | d1:sensorROI[2]*sensorROI[3] )
    uint16_t *modFrames2[SPECTRE_NUM_FRAMES_MODULATED];  ///< Modulated frame sets for second frequency (d0:4 | d1:sensorROI[2]*sensorROI[3] )
    uint32_t exposureTimesIn[SPECTRE_MAX_NUM_FREQS + 1]; ///< Processed exposure time, whereasa the first entry always refers to the intensity frame ( d0:numFrameSets )
};

/**
*   @brief Container of output values of the depth data calculation
*/
struct SpectreOutput
{
    uint16_t numColumns;                        ///< Total number of columns of output data
    uint16_t numRows;                           ///< Total number of rows of output data

    float *pm_distance;                         ///< Distance information of the output data ( d0:numColumns*numRows )
    float *pm_distanceNoise;                    ///< Noise value related to the distance calculation ( d0:numColumns*numRows )
    float *pm_amplitude;                        ///< Image data of the recorded amplitude ( d0:numColumns*numRows )
    float *pm3d_coord;                          ///< Distance information transformed into cartesian corrdinate space ( d0:numColumns*numRows*4 )
    uint32_t sizeCoords;                        ///< Size of pm3d_coords
    float *pm_intensity;                        ///< Image data of the recorded intensity ( d0:numColumns*numRows )

    uint32_t *pm_flags;                         ///< Flag status information of the processed pixel ( d0:numColumns*numRows )
    uint32_t pv_exposureTimesOut[SPECTRE_MAX_NUM_FREQS + 1]; ///< Proposed integration by auto exposure calculation ( d0:numFrameSets )
};

/**
*   @brief Flying pixel detection parametrization
*/
struct SpectreParameterFlyingPixel
{
    float f0;            ///< Linear scale value of first order for flying pixel removal
    float f1;            ///< Linear scale value of second order for flying pixel removal
    float farDist;       ///< Maximum validity check parameter for flying pixel removal
    float nearDist;      ///< Minimum validity check parameter for flying pixel removal
};

/**
*   @brief Saturation detection parametrization
*/
struct SpectreParameterSaturationThreshold
{
    uint16_t lower;     ///< Lower limit for saturation flag verification
    uint16_t upper;     ///< Upper limit for saturation flag verification
};

/**
*   @brief MPI processing parametrization
*/
struct SpectreParameterMPI
{
    float amplitudeThreshold;       ///< Amplitude level threshold for MPI calculation
    float distanceThreshold;        ///< Distance level threshold for MPI calculation
    float noiseDistance;            ///< Noise Distance
};

/**
*   @brief Processing configuration parameters
*/
struct SpectreParameterConfiguration
{
    uint8_t useAdaptiveNoiseFilter;     ///< Activate auto exposure
    uint8_t useAutoExposure;            ///< Activate auto exposure
    uint8_t useRemoveFlyingPixel;       ///< Activate FlyingPixel flag
    uint8_t useMPIFlagAverage;          ///< Activate spatial averaging MPI value before thresholding
    uint8_t useMPIFlagAmplitude;        ///< Activates MPI-amplitude flag calculation
    uint8_t useMPIFlagDistance;         ///< Activates MPI-distance flag calculation
    uint8_t useValidateImage;           ///< Activates output image validation
    uint8_t useSparsePointCloud;        ///< Activates the output of sparse point cloud
    uint8_t useRemoveStrayLight;
};

struct SpectreParameterInput
{
    uint_fast16_t numRows;
    uint_fast16_t numCols;
    uint_fast8_t numFreqs;
    uint_fast32_t freqs[2];
    uint_fast32_t exposureLimits[2];        ///< Holds the permittable exposure limits as [minExposure, maxExposure]
};

/**
*   @brief Use case dependent constant processing parameters
*/
struct SpectreParameter
{
    uint16_t version;                           ///< Spectre processing version
    uint16_t type;                              ///< Parameter data type, value corresponds to SpectreTypeParameter definition

    float amplitudeThreshold;                   ///< Upper limit values for amplitude value flags
    float consistencyTolerance;                 ///< Consistency limit for asymmetry validation
    float noiseThreshold;                       ///< Upper limit value for noise flag verification
    uint8_t adaptiveNoiseFilterType;                ///< Kerneltype value of the adaptive noise filter
    float exposureReferenceAmplitude;           ///< Reference amplitude for the auto exposure estimate

    struct SpectreParameterFlyingPixel flyingPixel;                     //< Flying pixel detection parametrization
    struct SpectreParameterMPI mpi;                                     //< MPI processing parametrization
    struct SpectreParameterSaturationThreshold saturationThreshold;     //< Saturation detection parametrization
    struct SpectreParameterConfiguration config;                        //< Processing configuration parameters
    struct SpectreParameterInput inputConfig;
};


/**
 * @brief Unscrambling of the intensity image
 *
 * @param ps_input input data
 * @param ps_calib calibration data
 * @param param Spectre configuration
 * @param ps_inter intermediate structure
 * @param ps_output output structure
 */
SPECTRE_PROCESSING_API void spectre_processIntensity (const struct SpectreInput *ps_input,
        const struct SpectreCalibration *ps_calib,
        const struct SpectreParameter *params,
        struct SpectreIntermediate *ps_inter,
        struct SpectreOutput *ps_output);
/**
 * @brief Unscrambling of the phase image for a given frequency index
 *
 * Note that spectre_processIntensity must be called previously
 * before this function can be applied.
 *
 * @param ps_input input data
 * @param ps_calib calibration data
 * @param ps_param parameter structure
 * @param ps_inter intermediate structure
 * @param ps_output output structure
 * @param freqIdx frequency index (starts with 0)
 */
SPECTRE_PROCESSING_API void spectre_processModFrames (const struct SpectreInput *ps_input,
        const struct SpectreCalibration *ps_calib,
        struct SpectreParameter *ps_param,
        struct SpectreIntermediate *ps_inter,
        struct SpectreOutput *ps_output,
        unsigned freqIdx);
/**
 * @brief Combines the previous output to calculate the final results
 *
 * Note that spectre_processIntensity and spectre_processModFrames must
 * be called previously before this function can be applied.
 *
 * @param ps_input input data
 * @param ps_calib calibration data
 * @param ps_param parameter structure
 * @param ps_inter intermediate structure
 * @param ps_output output structure
 * @return true if the processing was successful, false otherwise
 */
SPECTRE_PROCESSING_API void spectre_combineResults (const struct SpectreInput *ps_input,
        const struct SpectreCalibration *ps_calib,
        struct SpectreParameter *ps_param,
        struct SpectreIntermediate *ps_inter,
        struct SpectreOutput *ps_output);

/**
 * @brief Calls the processing for a single frame
 *
 * This function assumes that all initialization work has been already performed. That is, the passed ps_inter parameter
 * as well as the ps_calib parameter is initialized by the ::spectreAstonInit method, for the given SpectreInput configuration.
 * If the contents of SpectreInput::pv_frequencies, SpectreInput::numFrameSets or SpectreInput::pv_numFrames changed
 * after calling ::spectreAstonInit, you need to call this method again prior to calling ::spectreAstonRun.
 *
 * @param ps_input input data for this frame
 * @param ps_calib calibration data
 * @param ps_param pipeline parametrization
 * @param ps_inter (initialized) intermediate structure
 * @param ps_output output structure
 *
 */
SPECTRE_PROCESSING_API void spectreAstonRun (const struct SpectreInput *ps_input,
        const  void *ps_calib,
        struct SpectreParameter *ps_param,
        void *ps_inter,
        struct SpectreOutput *ps_output);

/**
 * @brief Initializes the processing
 *
 * This method needs to be called once before calling the processing with a specific use case (1-Freq/2-Freq mode),
 * and calibration. It initializes the internal SpectreIntermediate data structure. Ownership of the structure is
 * transferred to the caller. Additionally, it adapts the calibration with respect to the passed SpectreParameter structure.
 *
 *
 * @param param Spectre configuration
 * @param calib calibration structure
 * @param intermediate internal processing working structures
 *
 * @return status of operation
 */
SPECTRE_PROCESSING_API SpectreProcessingStatus spectreAstonInit (const struct SpectreParameter *param,
        struct SpectreCalibration *calib,
        struct SpectreIntermediate **intermediate);

/**
 * @brief Frees the SpectreIntermediate structure
 *
 * The passed pointer must be allocated with the spectreAstonInit function. If the pointer
 * is null, no action is performed.
 *
 *
 * @param intermediate intermediate structure
 *
 */
SPECTRE_PROCESSING_API void spectreAstonFree (struct SpectreIntermediate *intermediate);


#ifdef __cplusplus
}
#endif
/// @}
