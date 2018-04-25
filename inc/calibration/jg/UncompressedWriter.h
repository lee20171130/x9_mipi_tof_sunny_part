/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __UNCOMPRESSEDWRITER_H__
#define __UNCOMPRESSEDWRITER_H__

#include <stdint.h>
#include <calibration/calibration.h>

/**
 * Converts a uint16_t value to the integer representation used for serialization
 *
 * @param x value to encode
 * @param dest pointer to destination (with space for at least 2 uint8_t values)
 */
enum spectre_CalibrationStatus spectre_toJGUint16 (uint16_t x, uint8_t *dest);

/**
 * Converts a uint32_t value to the integer representation used for serialization
 *
 * @param x value to encode
 * @param dest pointer to destination (with space for at least 4 uint8_t values)
 */
enum spectre_CalibrationStatus spectre_toJGUint32 (uint32_t x, uint8_t *dest);

/**
 * Converts a int32_t value to the uint8_t representation used for serialization
 *
 * @param x original value
 * @param dst destination pointer (with space for at least 4 uint8_t values)
 *
 * @return
 */
enum spectre_CalibrationStatus spectre_toJGInt32 (int32_t x, uint8_t *dst);

/**
 * Converts a float value to the uint8_t representation used for serialization
 *
 * @param x float value
 * @param dest pointer to destination (with space for at least 4 uint8_t values)
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_toJGFloat (float x, uint8_t *dest);

#endif /*__UNCOMPRESSEDWRITER_H__*/
