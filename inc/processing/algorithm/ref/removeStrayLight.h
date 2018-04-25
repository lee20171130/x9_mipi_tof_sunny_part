/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __REMOVESTRAYLIGHT_H__
#define __REMOVESTRAYLIGHT_H__

/**
 * Removes stray light from the scene
 *
 * This function works in the real and imaginary parts of the phase measurements,
 * and requires a point spread function in the calibration data.
 *
 * It modifies the probeData directly.
 *
 * @param probeData intermediate probe data
 * @param work working buffers for stray light correction
 * @param calib calibration data
 */
void removeStrayLight(struct SpectreIntermediateProbeData *probeData,
                      struct SpectreIntermediateStrayLight *work,
                      const struct SpectreCalibration *calib);

#endif /*__REMOVESTRAYLIGHT_H__*/
