/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGCOMPRESSEDWRITER_H__
#define __JGCOMPRESSEDWRITER_H__


#include <calibration/calibration.h>
#include <calibration/jg/Header.h>

/**
 * Packs the specified number of less significant bits of
 * unsigned numbers together.  Effectively, this allows us to
 * store integers with an arbitrary number of bits.  The passed
 * destination buffer needs to hold at least
 * spectre_getJGPackedSize(size, bits) bytes.
 *
 * @param src source array
 * @param size entries in src
 * @param bits number of bits to encode
 * @param dest destination buffer
 *
 * @return on success number of entries in dest, otherwise an error code
 */
int spectre_packJGUint (const uint32_t *src, size_t size, uint8_t bits, uint32_t *dest);


/**
 * Creates a descriptor for packed fixed-point numbers
 *
 * @param min min. representable value
 * @param max max. reperesentable value
 * @param bits bits per element
 *
 * @return descriptor
 */
SPECTRE_CALIBRATION_API struct spectre_JGFixedPointDescriptor spectre_createJGDescriptor (float min, float max, uint8_t bits);

/**
 * Creates a descriptor for packed fixed-point numbers
 * This function calculates the minimum offset of the fixed-point system automatically, by choosing the
 * the lowest/largest element from src
 *
 * @param src source data
 * @param size number of elements in src
 * @param bits bits per element
 *
 * @return descriptor
 */
SPECTRE_CALIBRATION_API struct spectre_JGFixedPointDescriptor spectre_createJGAutoDescriptor (const float *src, size_t size, uint8_t bits);


// *****************************************************************************************************************
// TODO SK: Not part of public interface

/**
 * Converts the given floating-point value to a given fixed-point systen
 *
 * @param x value to convert
 * @param desc descriptor of fixed-point value
 *
 * @return fixed-point value
 */
uint32_t spectre_encodeToJGFixedPoint (float x, struct spectre_JGFixedPointDescriptor desc);

/**
 * Packs floating-point numbers into an array using the specified number of bits in the given
 * fixed-point system.
 * The passed destination buffer needs to hold at least spectre_getJGPackedSize(size, bits) bytes, and
 * the workingMem needs to hold at least size*sizeof(uint32_t) bytes.
 *
 * @param src source array
 * @param size entries in src
 * @param bits number of bits to encode
 * @param desc descriptor of fixed-point system
 * @param workingMem temporary working memory
 * @param dest destination buffer
 *
 * @return on success number of entries in dest, otherwise an error code
 */
int spectre_packJGFloat (const float *src, size_t size, uint8_t bits,
                         struct spectre_JGFixedPointDescriptor desc,
                         void *workingMem, uint32_t *dest);

#endif /*__JGCOMPRESSEDWRITER_H__*/
