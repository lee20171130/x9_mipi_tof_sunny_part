/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __ASTONREADER_H__
#define __ASTONREADER_H__

#include <calibration/aston/astoncalibration.h>
#include <calibration/calibration.h>

/**
 * @addtogroup libcalibration_aston
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads the header of an ASTON calibration container
 *
 * @param header header structure to fill
 * @param stream binary stream
 * @param idx index where the container starts (updated to point behind the header)
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCalibrationHeader (struct spectre_astonHeader *header, const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads the calibration body (that is, everything besides the header) of an ASTON calibration container
 *
 * This function assumes that the header has been already read, and that idx points at the body start (behind the header).
 * Additionally, it is assumed that the arrays in calib have been allocated, and that workingMem is at least
 * sizeof(uint32_t) * imageWidth.
 *
 * @param calib calibration structure to fill
 * @param workingMem working memory
 * @param stream binary stream
 * @param idx index where the body starts (updated to point behind the body)
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCalibrationBody (struct SpectreCalibration *calib,
        void *workingMem,
        const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads a calibration
 *
 * This function reads header and body. Additionally, it allocates the arrays inside calib.
 *
 * @param calib calibration structure to fill
 * @param stream binary stream
 * @param idx index where the container starts (updated to point behind the container)
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCalibration (struct SpectreCalibration *calib, const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Calculates psf and 3d directions
 *
 * The calibration structure previously has to be parsed with spectre_readAstonCalibration
 *
 * @param calib calibration structure
 * @param numPixel number of pixels
 *
 * @return status or operation
 */
enum spectre_CalibrationStatus spectre_calcAstonPsfAndDirections (struct SpectreCalibration *calib, const int numPixel);
#ifdef __cplusplus
}
#endif

/// @}

#endif /*__ASTONREADER_H__*/
