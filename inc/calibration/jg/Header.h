/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGHEADER_H__
#define __JGHEADER_H__

#include <stdint.h>
#include <stddef.h>

/// Identifier of the EOF block of a Junge Grimme file
#define SPECTRE_JUNGE_GRIMME_END_ID 255

/**
 * Supported format configurations of the "Junge Grimme" format
 */
enum spectre_JGConfiguration {
    SPECTRE_JG_BENTLEY = 1
};

/// Descriptor of a fixed-point system
struct spectre_JGFixedPointDescriptor
{
    /// Scaling factor for fixed-point system
    /**
     * The value is only defined if a fixed-point system is described
     */
    float scale;
    /// Offset for fixed-point system
    /**
     * The value is only defined if a fixed-point system is described
     */
    float min;
};


/**
 * Data block types of the "Junge Grimme" format
 * The data block type specifies which type of data is encoded in the block.
 */
enum spectre_JGType {
    SPECTRE_JG_UNSIGNED8 = 0,
    SPECTRE_JG_UNSIGNED16 = 1,
    SPECTRE_JG_UNSIGNED32 = 2,
    SPECTRE_JG_SIGNED32 = 3,
    SPECTRE_JG_FLOAT = 4,
    SPECTRE_JG_PACKED_UNSIGNED32 = 5,
    SPECTRE_JG_PACKED_FIXED = 6
};

/// Global header of "Junge Grimme" file
struct spectre_JGHeader
{
    /// Configuration of the file
    enum spectre_JGConfiguration configuration;
    /// Width of the calibrated area
    uint16_t width;
    /// Height of the calibrated area
    uint16_t height;
};

/// Header for an individual data block
struct spectre_JGBlockHeader
{
    /// Unique block id
    uint8_t id;
    /// Data block type
    enum spectre_JGType type;
    /// Number of elements in the block
    uint32_t numElements;
    /// Number of bits used per entry
    /**
     * Depending on type this element might be undefined
     */
    uint8_t bits;
    /// Descriptor of compressed data
    /**
     * Depending on type this element might be undefined
     */
    struct spectre_JGFixedPointDescriptor descriptor;
};

#endif /*__JGHEADER_H__*/
