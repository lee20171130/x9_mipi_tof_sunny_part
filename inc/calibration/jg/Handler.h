/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGHANDLER_H__
#define __JGHANDLER_H__

struct spectre_calibrationHandler spectre_getJGCalibrationHandler();


/**
 * Calculates psf and 3d directions of a given calibration structure
 *
 * The passed calibration struct previously has to be parsed with spectre_readJGCalibration
 *
 * @param calib calibration struct
 * @param numPixel number of pixels
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_calcJGPsfAndDirections (struct SpectreCalibration *calib, const int numPixel);


#endif /*__JGHANDLER_H__*/
