/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGCOMPRESSED_H__
#define __JGCOMPRESSED_H__

#include <stdint.h>
#include <stddef.h>
#include <calibration/calibration.h>
#include <calibration/jg/Header.h>


/**
 * Gets the size of a packed data block in bytes
 *
 * @param size number of elements
 * @param bits bits per element
 *
 * @return size of packed block (in bytes)
 */
size_t spectre_getJGPackedSize (size_t numElements, uint8_t bits);

/**
 * Unpacks a packed integer sequence packed with spectre_packJGUint
 * The passed dest buffer needs to hold at least noEncodedVals*size(uint32_t) bytes.
 *
 * @param src packed sequence
 * @param size entries in src
 * @param noEncodedVals number of values encoded in src
 * @param bits bits used to encode an individual values
 * @param dest destination buffer
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_unpackJGUint (const uint32_t *src, size_t size, size_t noEncodedVals,
        uint8_t bits, uint32_t *dest);

/**
 * Unpacks a packed fixed-point sequence packed with spectre_packJGFloat
 * The passed dest buffer needs to hold at least noEncodedVals*sizeof(float) bytes, and
 * the workingMem buffer needs to hold at least noEncodedVals*sizeof(uint32_t) bytes
 *
 * @param src packed sequence
 * @param size entries in src
 * @param noEncodedVals number of values encoded in src
 * @param bits bits used to encode an individual values
 * @param desc descriptor of fixed-point system
 * @param workingMem temporary working memory
 * @param dest destination buffer
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_unpackJGFloat (const uint32_t *src, size_t size, size_t noEncodedVals,
        uint8_t bits, struct spectre_JGFixedPointDescriptor desc,
        void *workingMem, float *dest);



/**
 * Unpacks the given fixed-point array into a float array
 * The given dest array needs to hold at least size*sizeof(float) bytes
 *
 * @param src source data
 * @param size size of src
 * @param desc descriptor of fixed-point system
 * @param dest destination array
 */
float spectre_decodeFromJGFixedPoint (uint32_t src, struct spectre_JGFixedPointDescriptor desc);



#endif /*__JGCOMPRESSED_H__*/
