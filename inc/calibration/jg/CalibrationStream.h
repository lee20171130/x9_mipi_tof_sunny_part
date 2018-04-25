/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __CALIBRATIONSTREAM_H__
#define __CALIBRATIONSTREAM_H__

#include <stdint.h>
#include <stddef.h>

#include <calibration/calibration.h>

struct spectre_CalibrationStream
{
    uint8_t *data;
    size_t idx;
    size_t size;
};

/**
 * Tests if the given number of bytes can be read from the stream
 *
 * @param stream stream to read from
 * @param bytes bytes to read
 *
 * @return SUCCESS if read would be successful, UNEXPECTED_END otherwise
 */
enum spectre_CalibrationStatus spectre_canRead (struct spectre_CalibrationStream *stream,
        size_t bytes);

/**
 * Creates a stream from existing data
 *
 * @param data data
 * @param dataSize size of data
 *
 * @return stream backed by data
 */
struct spectre_CalibrationStream spectre_createStreamFromData (uint8_t *data, size_t dataSize);

#endif /*__CALIBRATIONSTREAM_H__*/
