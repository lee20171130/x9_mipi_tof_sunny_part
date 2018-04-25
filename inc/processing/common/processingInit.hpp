/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __PROCESSINGINIT_HPP__
#define __PROCESSINGINIT_HPP__

#include <processing/SpectreProcessingStatus.hpp>
#include <processing/common/processingExport.hpp>
#include <common/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SpectreIntermediate;
struct SpectreParameter;

/**
 * Initializes a new SpectreIntermediate structure
 *
 * The created SpectreIntermediate structure newly matches the type of the passed SpectreInput structure
 * w.r.t. to image dimensions, probe frequencies, and so on.
 *
 *
 * @param input input structure
 * @param calib calibration structure
 * @param inter intermediate structure (will hold the created structure on success)
 *
 * @return status of operation
 */
SPECTRE_PROCESSING_API SpectreProcessingStatus spectreIntermediateInit (const struct SpectreParameter *params,
        const struct SpectreCalibration *calib,
        struct SpectreIntermediate **inter);

/**
 * Frees the SpectreIntermediate structure
 *
 * @param inter pointer to intermediate structure
 */
SPECTRE_PROCESSING_API void spectreIntermediateFree (struct SpectreIntermediate *inter);

/**
 * Adapts the given calibration structure, so that it matches with the given input
 * That is, it swaps the modulation frequency depenendent data in the calibration, so that they
 * match the modulation order specified by the input structure.
 *
 * @param params Spectre configuration
 * @param calib calibration
 *
 * @return status code of operation
 */
SPECTRE_PROCESSING_API SpectreProcessingStatus adaptCalibration (const struct SpectreParameter *params, struct SpectreCalibration *calib);

#ifdef __cplusplus
}
#endif

#endif /*__PROCESSINGINIT_HPP__*/
