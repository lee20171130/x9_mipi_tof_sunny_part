/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGBLOCK_H__
#define __JGBLOCK_H__

#include "CalibrationStream.h"
#include "Header.h"

#include <calibration/calibration.h>


/**
 * Reads the block header of a data block
 * Stream should point to the start of the header
 *
 * @param stream stream (index is adjusted during read)
 * @param header file header
 * @param blockHeader structure to be filled
 *
 * @return status code
 */
enum spectre_CalibrationStatus spectre_readJGBlockHeader (struct spectre_CalibrationStream *stream,
        const struct spectre_JGHeader *header,
        struct spectre_JGBlockHeader *blockHeader);

/**
 * Reads the global header of the calibration data
 * Stream index should point to the start of the header
 *
 * @param stream data stream (index is adjusted during read)
 * @param header structure to be filled
 *
 * @return status code
 */
enum spectre_CalibrationStatus spectre_readJGHeader (struct spectre_CalibrationStream *stream,
        struct spectre_JGHeader *header);

/**
 * Gets the unpacked size of a data block
 *
 * @param header data block header
 *
 * @return size in bytes if the block is unpacked (excluding the header)
 */
size_t spectre_getJGUnpackedBlockSize (const struct spectre_JGBlockHeader *header);

/**
 * Gets the complete packed size of a data block (excluding) header
 *
 * @param blockHeader data block header
 *
 * @return size in bytes if packed (excluding the header)
 */
size_t spectre_getJGPackedBlockSize (const struct spectre_JGBlockHeader *blockHeader);

/**
 * Decodes a data block and unpacks it
 * Passed stream should point to the start of block
 *
 * @param stream stream (index is adjusted)
 * @param header global file header
 * @param blockHeader header of the data block
 * @param dst destination for the unpacked data
 * @param dstSize size of dst in bytes
 *
 * @return status of the operation
 */

/**
 * Decodes a data block and unpacks it
 * Passed stream should point to the start of the block (after the header)
 *
 * dst needs to hold at least spectre_getJGUnpackedBlockSize(blockHeader) bytes.
 * workingMem needs to hold at least dstSize + spectre_getPackedBlockSize(blockHeader) bytes if a
 * packed type is decoded. Otherwise workingMem is not used, and its size ignored.
 *
 * Both buffers need to be properly aligned for the decoded types (depending on blockHeader->type)
 *
 *
 * @param stream stream
 * @param blockHeader header of data block
 * @param workingMem working memory
 * @param workingSize size of working memory
 * @param dst destination for the unpacked data
 * @param dstSize size of dst in bytes
 *
 * @return status of the operation
 */
enum spectre_CalibrationStatus spectre_decodeJGBlock (struct spectre_CalibrationStream *stream,
        const struct spectre_JGBlockHeader *blockHeader,
        void *workingMem, size_t workingSize,
        void *dst, size_t dstSize);


#endif /*__JGBLOCK_H__*/
