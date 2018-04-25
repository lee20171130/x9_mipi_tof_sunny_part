/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGBLOCKWRITER_H__
#define __JGBLOCKWRITER_H__

#include "CalibrationStream.h"
#include "Header.h"

#include <calibration/calibration.h>

/**
 * Writes the header to a given stream
 *
 * @param header header to write
 * @param stream destination stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_encodeJGHeader (const struct spectre_JGHeader *header,
        struct spectre_CalibrationStream *stream);


/**
 * Encodes a block of data and writes it (excluding header) to a given stream
 * The type of the data is determined by the given blockHeader
 *
 * @param data data to encode
 * @param blockHeader header of block
 * @param workingMem temporary working memory (at least spectre_getPackedBlockSize(blockHeader) + spectre_getJGUnpackedBlockSize(blockHeader))
 * @param workingSize size of working memory
 * @param stream destination stream
 *
 * @return status of operation
 */

enum spectre_CalibrationStatus spectre_encodeJGBlock (const void *data,
        const struct spectre_JGBlockHeader *blockHeader,
        void *workingMem, size_t workingSize,
        struct spectre_CalibrationStream *stream);

/**
 * Writes the block header to the given stream
 *
 * @param blockHeader block header to write
 * @param header main header of file
 * @param stream destination stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_encodeJGBlockHeader (const struct spectre_JGBlockHeader *blockHeader,
        const struct spectre_JGHeader *header,
        struct spectre_CalibrationStream *stream);

/**
 * Writes the EOF marker to the calibration stream
 *
 * @param stream destination stream
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_encodeJGEndBlock (struct spectre_CalibrationStream *stream);

#endif /*__JGBLOCKWRITER_H__*/
