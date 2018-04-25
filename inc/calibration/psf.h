/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/


#ifndef __PSF_H__
#define __PSF_H__
#include <calibration/calibration.h>

/**
 * @addtogroup libcalibration_internal
 * @{
 */


struct SpectreCalibration;

/**
 * @brief Computes the PSF from the calibrated straylight parametrization if it exists.
 *
 * Since, this function modifies the calibration in a non-idempotent way, it must be called only once.
 * If calib contains no straylight parameters the function returns #SPECTRE_STATUS_INVALID_ARGUMENTS to indicate this.
 * It may return other error codes to indicate different error. On success #SPECTRE_STATUS_SUCCESS is returned.
 *
 *
 * @param calib calibration structure to update
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_allocateAndCalculatePsf(struct SpectreCalibration *calib);

/// @}

#endif /*__PSF_H__*/
