/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __DATACOMPRESSED_H__
#define __DATACOMPRESSED_H__

#include <stdint.h>
#include <calibration/calibration.h>
#include <calibration/aston/datadescriptor.h>

/**
 * @addtogroup libcalibration_aston
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads a compressed array of uint32_t
 *
 * The array should be written by a registered spectre::element::data::Data with type uint32_t with a non-default spectre::element::data::DataDescriptor.
 *
 * @param dest destination
 * @param size number of values
 * @param workingMem working memory (at least sizeof(uint32_t) * size)
 * @param desc data descriptor
 * @param stream binary stream
 * @param idx offset where spectre::element::data::Data<uint32_t> starts
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCompressedDataUint32 (uint32_t *dest, uint32_t size, uint32_t *workingMem,
        const struct spectre_astonIntegralDescriptor *desc,
        const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads a compressed array of uint8_t
 *
 * The array should be written by a registered spectre::element::data::Data with type uint8_t with a non-default spectre::element::data::DataDescriptor.
 *
 * @param dest destination
 * @param size number of values
 * @param workingMem working memory (at least sizeof(uint32_t) * size)
 * @param desc data descriptor
 * @param stream binary stream
 * @param idx offset where the spectre::element::data::Data<uint8_t> starts
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCompressedDataUint8 (uint8_t *dest, uint32_t size, uint32_t *workingMem,
        const struct spectre_astonIntegralDescriptor *desc,
        const uint8_t *stream, long *idx, long streamSize);

/**
 * @brief Reads a compressed array of floats
 *
 * The array should be written by registered spectre::element::data::Data with type float with a non-default spectre::element::data::DataDescriptor
 *
 * @param dest destination
 * @param size number of values
 * @param workingMem working memory (at least sizeof(uint32_t) * size)
 * @param desc data descriptor
 * @param stream binary stream
 * @param idxoffset where the spectre::element::data::Data<float> starts
 * @param streamSize size of stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readAstonCompressedDataFloat (float *dest, uint32_t size, uint32_t *workingMem,
        const struct spectre_astonFloatDescriptor *desc,
        const uint8_t *stream, long *idx, long streamSize);

#ifdef __cplusplus
}
#endif
/// @}
#endif /*__DATACOMPRESSED_H__*/
