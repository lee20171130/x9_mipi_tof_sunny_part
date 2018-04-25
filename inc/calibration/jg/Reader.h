/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __JGREADER_H__
#define __JGREADER_H__


#include <calibration/calibration.h>
#include <calibration/jg/IdTable.h>
#include <calibration/jg/CalibrationStream.h>

/**
 * Reads a Junge Grimme file from a given CalibrationStream, and maps the results
 * using a passed dispatchTable.
 *
 * The passed dispatch table is consumed during the run.
 *
 * @param stream calibration stream
 * @param dispatchTable  dispatch table (ownership transferred to callee)
 *
 * @return status of operation
 */
struct spectre_JGValidationError spectre_readJGCalibration (struct spectre_CalibrationStream *stream,
        struct spectre_JGTableRoot *dispatchTable);

/**
 * Reads custom data of a Junge Grimme file from a given CalibrationStream, and maps the results
 * to the passed calibration struct.
 *
 * The passed calibration struct previously has to be parsed with spectre_readJGCalibration.
 *
 * @param stream calibration stream
 * @param calib calibration struct
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_readJGCustomData (struct spectre_CalibrationStream *stream,
        struct SpectreCalibration *calib);

#endif /*__JGREADER_H__*/
