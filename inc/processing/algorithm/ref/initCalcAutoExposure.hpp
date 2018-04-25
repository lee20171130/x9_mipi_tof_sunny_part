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

/**
 * \addtogroup libprocessing
 * @{
 *
 * \defgroup libprocessing_ref Reference Algorithms
 *
 * @brief The reference algorithms are implementations suitable for all platforms supported by Spectre.
 *
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif

#include <processing/common/commonMethods.hpp>
#include <processing/common/processingExport.hpp>

/*
* @brief Retrieves the bin size to be allocated for the autoexposure calculation
*
* @param numColumns Image width
* @param numColumns Image height
* @param binSize Dimensional properties of the binning container
*
* @return Status of Operation
*/
SPECTRE_PROCESSING_API void initCalcAutoExposureGetMaxBinSize (uint32_t numColumns,
        uint32_t numRows,
        uint32_t *binSize);


/*
* @brief Defines the auto-exposure mask and quantile threshold position
*
* @param autoExposure Reference to the spectre auto exposure data structure
* @param calib Reference to the spectre calibration data structure
* @param numColumns Number of image columns
* @param numRows Number of image rows
*
*/
SPECTRE_PROCESSING_API void initCalcAutoExposure (struct SpectreIntermediateAutoExposure *autoExposure,
        const struct SpectreCalibration *calib,
        uint32_t numColumns,
        uint32_t numRows);
#ifdef __cplusplus
}

/// @}
/// @}

#endif // __cplusplus
