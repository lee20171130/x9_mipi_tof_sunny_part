/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __CALIBRATIONFIELDDEFINITIONS_H__
#define __CALIBRATIONFIELDDEFINITIONS_H__

/**
 * @addtogroup libcalibration_internal
 * @{
 */

#include <stdint.h>
#include <math.h>
#include <calibration/calibration.h>
#ifdef __cplusplus
extern "C" {
#endif


// ********************************************************************************
// These values are defaults for the initialization of the calibration structure
// fields.

/// Default value for an unsigned intger field which is unset
#define UNINITIALIZED_CHAR_FIELD '\0'
/// Default value for an unsigned intger field which is unset
#define UNINITIALIZED_UINT_FIELD UINT_MAX
/// Default value for an unsigned 8 bit intger field which is unset, e.g. customDataStartId
#define UNINITIALIZED_UINT8_FIELD UINT8_MAX
/// Default value for an unsigned 16 bit intger field which is unset, e.g. lensCenter
#define UNINITIALIZED_UINT16_FIELD UINT16_MAX
/// Default value for an float field which is unset
#define UNINITIALIZED_FLOAT_FIELD NAN
// ********************************************************************************


/**
 * @brief Checks if an optional field contains a valid value.
 *
 * @param field unsigned integer parameter
 *
 * @return 1 or 0 zero here (for bool)
 */
int spectre_validUnsigndField (const unsigned field);

/**
 * @brief Checks if an optional field contains a valid value.
 *
 * @param field unsigned 8 bit integer parameter
 *
 * @return 1 or 0 zero here (for bool)
 */
int spectre_validUnit8Field (const uint8_t field);


/**
 * @brief Checks if an optional field contains a valid value.
 *
 * @param field unsigned 16 bit integer parameter
 *
 * @return 1 or 0 zero here (for bool)
 */
int spectre_validUnit16Field (const uint16_t field);

/**
 * @brief Checks if an optional field contains a valid value.
 *
 * @param field float parameter
 *
 * @return 1 or 0 zero here (for bool)
 */
int spectre_validFloatField (const float field);

#ifdef __cplusplus
}
#endif

/// @}

#endif /*__CALIBRATIONFIELDDEFINITIONS_H__*/
