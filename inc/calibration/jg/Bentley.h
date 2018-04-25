/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __BENTLEY_H__
#define __BENTLEY_H__

#include <calibration/jg/IdTable.h>

/// Valid fields for a calibration file in Bentley configuration
enum BentleyIds
{
    SPECTRE_BENTLEY_LENS_MODEL = 0,
    SPECTRE_BENTLEY_LENS_PARAMETER = 1,
    SPECTRE_BENTLEY_MASK = 2,
    SPECTRE_BENTLEY_FPN = 3,
    SPECTRE_BENTLEY_DATE = 4,
    SPECTRE_BENTLEY_SERIAL = 5,
    SPECTRE_BENTLEY_SENSOR_SERIAL = 6,
    SPECTRE_BENTLEY_PRODUCT_CODE = 7,
    SPECTRE_BENTLEY_LENS_CENTER = 8,
    SPECTRE_BENTLEY_PSF = 9,

    // Do not change the order of the frequency blocks, the
    // validation function depends on the used indices
    SPECTRE_BENTLEY_FREQUENCY_1 = 16,
    SPECTRE_BENTLEY_FPPN_1 = 17,
    SPECTRE_BENTLEY_TEMP_COMPENSATION_1 = 18,
    SPECTRE_BENTLEY_NOISE_PARAMETER_1 = 19,
    SPECTRE_BENTLEY_MEAN_EFFICIENCY_1 = 20,
    SPECTRE_BENTLEY_PHASE_WIGGLING_1 = 21,
    SPECTRE_BENTLEY_AMPLITUDE_WIGGLING_1 = 22,

    SPECTRE_BENTLEY_FREQUENCY_2 = 23,
    SPECTRE_BENTLEY_FPPN_2 = 24,
    SPECTRE_BENTLEY_TEMP_COMPENSATION_2 = 25,
    SPECTRE_BENTLEY_NOISE_PARAMETER_2 = 26,
    SPECTRE_BENTLEY_MEAN_EFFICIENCY_2 = 27,
    SPECTRE_BENTLEY_PHASE_WIGGLING_2 = 28,
    SPECTRE_BENTLEY_AMPLITUDE_WIGGLING_2 = 29,

    SPECTRE_BENTLEY_FREQUENCY_3 = 30,
    SPECTRE_BENTLEY_FPPN_3 = 31,
    SPECTRE_BENTLEY_TEMP_COMPENSATION_3 = 32,
    SPECTRE_BENTLEY_NOISE_PARAMETER_3 = 33,
    SPECTRE_BENTLEY_MEAN_EFFICIENCY_3 = 34,
    SPECTRE_BENTLEY_PHASE_WIGGLING_3 = 35,
    SPECTRE_BENTLEY_AMPLITUDE_WIGGLING_3 = 36,

    SPECTRE_BENTLEY_FREQUENCY_4 = 37,
    SPECTRE_BENTLEY_FPPN_4 = 38,
    SPECTRE_BENTLEY_TEMP_COMPENSATION_4 = 39,
    SPECTRE_BENTLEY_NOISE_PARAMETER_4 = 40,
    SPECTRE_BENTLEY_MEAN_EFFICIENCY_4 = 41,
    SPECTRE_BENTLEY_PHASE_WIGGLING_4 = 42,
    SPECTRE_BENTLEY_AMPLITUDE_WIGGLING_4 = 43,

    SPECTRE_BENTLEY_FREQUENCY_5 = 44,
    SPECTRE_BENTLEY_FPPN_5 = 45,
    SPECTRE_BENTLEY_TEMP_COMPENSATION_5 = 46,
    SPECTRE_BENTLEY_NOISE_PARAMETER_5 = 47,
    SPECTRE_BENTLEY_MEAN_EFFICIENCY_5 = 48,
    SPECTRE_BENTLEY_PHASE_WIGGLING_5 = 49,
    SPECTRE_BENTLEY_AMPLITUDE_WIGGLING_5 = 50
};

/// Distance between two frequency block ids
#define SPECTRE_BENTLEY_FREQUENCY_DISTANCE 7

/// Number of (maximum) frequency blocks
#define SPECTRE_BENTLEY_NUM_FREQUENCY_BLOCKS 5


/**
 * Creates a dispatch table for a Bentley configuration of a
 * Junge Grimme file.
 *
 * The dispatcher table allows to map the contents during parsing into a preallocated SpectreCalibration structure
 *
 * @param calib preallocated SpectreCalibration struct
 * @param imageSize size of image
 *
 * @return first table entry
 */
struct spectre_JGTableRoot *spectre_createBentleyTable (struct SpectreCalibration *calib, size_t imageSize);

#endif /*__BENTLEY_H__*/
