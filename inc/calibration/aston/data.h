/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DATA_H__
#define __DATA_H__

#include <stdint.h>
#include <calibration/calibration.h>

/**
 * @addtogroup libcalibration_aston
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads a string written by spectre::element::data::Data<char> binarize into the stream
 *
 * @param dest destination buffer
 * @param size length of string including terminating \0 with is appended
 * @param stream data stream
 * @param idx offset where the Data<char> starts, idx is updated
 * @param streamSize size of the stream
 *
 * @return status of operations
 */
enum spectre_CalibrationStatus spectre_readAstonDataString (char *dest, uint32_t size, const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads a uint32_t array written by spectre::element::data::Data<uint32_t> binarize
 *
 * @param dest destination buffer
 * @param size number of uint32_ts
 * @param stream data stream
 * @param idx offset where the spectre::element::data::Data<uint32_t> starts, idx is updated
 * @param streamSize size of the stream
 *
 * @return status of operations
 */
enum spectre_CalibrationStatus spectre_readAstonDataUint32 (uint32_t *dest, uint32_t size, const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads a uint32_t array written by Data<float> binarize
 *
 * @param dest destination buffer
 * @param size number of floats
 * @param stream data stream
 * @param idx offset where the spectre::element::data::Data<float> starts, idx is updated
 * @param streamSize size of the stream
 *
 * @return status of operations
 */
enum spectre_CalibrationStatus spectre_readAstonDataFloat (float *dest, uint32_t size, const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads the number of elements of a spectre::element::data::DataDynSize<> node
 *
 *
 * @param noValues no of values in node
 * @param stream data stream
 * @param idx offset where the spectre::element::data::DataDynSize<> starts, idx is updated
 * @param streamSize size of operation
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonDataDynNoValues (uint32_t *noValues, const uint8_t *stream, long *idx, long streamSize);


/**
 * @brief Checks if the number of values is <= the maximum expected number
 *
 * @param actualNoValues actual number of values
 * @param maxNoValues maximum expected number
 *
 * @return #SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED if actualNoValuea > maxNoValues, #SPECTRE_STATUS_SUCCESS otherwise
 */
enum spectre_CalibrationStatus spectre_checkAstonNoValues (uint32_t actualNoValues, uint32_t maxNoValues);

/**
 * @brief Checks if the number of values matches the expected numbers exactly.
 *
 * For example, this needs to be the case for a given wiggling configuration.
 * The number of terms needs to be same for phase, amplitude and harmonics.
 *
 * @param actualNoValues values in stream
 * @param expectedNoValus expected values
 *
 * @return #SPECTRE_STATUS_UNSUPPORTED_FORMAT if the numbers are not equal, #SPECTRE_STATUS_SUCCESS otherwise
 */
enum spectre_CalibrationStatus spectre_checkAstonConsistentNoValues (uint32_t actualNoValues, uint32_t expectedNoValus);

/**
 * @brief Updates the given field with the integer
 *
 * The value is cast to uint8_t
 *
 * @param dest destination
 * @param actualNoValues value to write
 *
 * @return #SPECTRE_STATUS_UNSUPPORTED_FORMAT if actualNoValues > UINT8_MAX, #SPECTRE_STATUS_SUCCESS otherwise
 */
enum spectre_CalibrationStatus spectre_updateAstonWithActualNo (uint8_t *dest, uint32_t actualNoValues);

#ifdef __cplusplus
}
#endif

/// @}

#endif /*__DATA_H__*/

