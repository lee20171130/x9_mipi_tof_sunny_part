/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DIRECTIONS_H__
#define __DIRECTIONS_H__

#include <calibration/calibration.h>

/**
 * @addtogroup libcalibration_internal
 *
 * Updates the directions based on the lensParameters and the calibrationROI
 * The preallocated float array needs to be of size SpectreCalibration::pv_calibrationROI[2] * SpectreCalibration::pv_calibrationROI[3] * 3
 *
 * @param directions destination for directions
 * @param size number of entries in directions (see above)
 * @param lensParameters lensparameters from calibration (array of size 9)
 * @param calibrationROI calibration ROI (array of size 4)
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_updateDirections (float *directions, long size, const float *lensParameters, const uint32_t *calibrationROI);


#endif /*__DIRECTIONS_H__*/
