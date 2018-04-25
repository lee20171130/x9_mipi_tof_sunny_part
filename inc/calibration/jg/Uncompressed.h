/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __UNCOMPRESSED_H__
#define __UNCOMPRESSED_H__

#include <stdint.h>
#include <calibration/calibration.h>

/**
 * Converts a serialized uint16_t to the native platform format
 *
 * @param src pointer to serialized data (must contain at least 2 uint8_t values)
 * @param dst destination pointer
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_fromJGUint16(const uint8_t *src, uint16_t *dst);

/**
 * Converts a serialized uint32_t to the native platform format
 *
 * @param src pointer to serialized data (must contain at least 4 uint8_t values)
 * @param dst destination pointer
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_fromJGUint32(const uint8_t *src, uint32_t *dst);

/**
 * Converts a serialized float to the native platform format
 *
 * @param src pointer to serialized data (must contain at least 4 uint8_t values)
 * @param dst destination pointer
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_fromJGFloat(const uint8_t *src, float *dst);

/**
 * Converts a serialized int32_t to the native platform format
 *
 * @param src pointer to serialized data (must contain at least 4 uint8_t values)
 * @param dst destination pointer
 *
 * @return status of operation
 */

enum spectre_CalibrationStatus spectre_fromJGInt32(const uint8_t *src, int32_t *dst);

#endif /*__UNCOMPRESSED_H__*/
