/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __MOCKCALIBRATIONHANDLER_HPP__
#define __MOCKCALIBRATIONHANDLER_HPP__

struct spectre_calibrationHandler getMockCalibrationHandler();

struct spectre_calibrationHandler getMockCalibrationHandlerMissingField();

struct spectre_calibrationHandler getMockCalibrationHandlerZeroNumPixel();

/**
 * Returns a mock calibration handler of the aston format
 * in order to test the return value of features that are not supported
 * by older fromats
 *
 * @return calibration handler of aston format
 */
struct spectre_calibrationHandler getMockCalibrationHandlerOlderFormat();

#endif /*__MOCKCALIBRATIONHANDLER_HPP__*/
