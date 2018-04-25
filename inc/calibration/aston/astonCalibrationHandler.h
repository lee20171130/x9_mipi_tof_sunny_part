/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __ASTONCALIBRATIONHANDLER_H__
#define __ASTONCALIBRATIONHANDLER_H__

#include <calibration/dispatcher.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup libcalibration_internal
 * @{
 */

/**
 * @defgroup libcalibration_aston Aston Support
 *
 * @brief Adds support for the Aston (Spectre V1) calibration format
 * @{
 */


/**
 * @brief Returns the aston calibration handler
 *
 * @return aston calibration handler
 *
 */
struct spectre_calibrationHandler spectre_getAstonCalibrationHandler();

/**
 * @}
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /*__ASTONCALIBRATIONHANDLER_H__*/
