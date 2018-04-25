/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __CALIBRATIONSTREAMWRITER_H__
#define __CALIBRATIONSTREAMWRITER_H__


#include <calibration/calibration.h>
#include <calibration/jg/CalibrationStream.h>

/**
 * Ensures that a given number of bytes can be written to the stream
 * This ensures that stream->data is at least of size stream->idx + bytes.
 *
 * @param stream stream to adjust
 * @param bytes number of bytes to be written
 *
 * @return SUCCESS if read would be successful, UNKNOWN_ERROR if allocation failed
 */
enum spectre_CalibrationStatus spectre_ensureWrite (struct spectre_CalibrationStream *stream,
        size_t bytes);

/**
 * Creates a new stream
 *
 * @param bytes initialize size
 *
 * @return stream
 */
struct spectre_CalibrationStream spectre_createNewStream (size_t bytes);


#endif /*__CALIBRATIONSTREAMWRITER_H__*/
