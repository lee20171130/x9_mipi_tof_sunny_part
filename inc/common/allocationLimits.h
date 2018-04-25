/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __ALLOCATIONLIMITS_H__
#define __ALLOCATIONLIMITS_H__

/**
 * @addtogroup libcalibration
 * @{
 */
/**
 * @defgroup libcalibration_internal Implementation details
 * @brief Documentation of modules, and functionality not exposed through the public interface.
 * @{
 */

/**
 * @defgroup libcalibration_allocation Memory allocation limits
 * @{
 * @brief The amount of memory that allocates libcalibration to parse and store a calibration can be fine-tuned here.
 *
 * These values are sensible defaults for allocating the SpectreCalibration structure.
 * <em>Usually, it is not necessary to change them.</em><br />
 * However, it is possible to create valid calibration files which exceed these
 * limits. These files cannot be loaded, and the spectre_calibrationHandler
 * should return #SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED
 */



#ifdef __cplusplus
extern "C" {
#endif

/// Maximum number of calibrated frequencies
#define MAX_NUM_FREQS 5
/// Maximum number of harmonic terms in the phase wiggling correction
#define MAX_NUM_PHASE_WIGGLES 5
/// Maximum number of harmonic terms in the amplitude wiggling correction
#define MAX_NUM_AMPLITUDE_WIGGLES 5
/// Maximum number of characters in the string (excluding terminating \0)
#define MAX_NUM_CHARS 64
// Be aware: Changing these is likely to affect the processing code, too.
/// Maximum number of lens parameter
#define MAX_NUM_LENS_PARAMETERS 9
/// Maximum number of temperature correction terms
#define MAX_NUM_TEMPERATURE_CORRECTION 4
/// Maximum number of noise parameters
#define MAX_NUM_NOISE_PARAMETERS 4
/// Maximum length of product code
#define MAX_LENGTH_PRODUCT_CODE 32
/// Maximum number of custom fields
#define MAX_NUM_CUSTOM_FIELDS 5
/// Maximum number of stray light nodes
#define MAX_NUM_STRAY_LIGHT_NODES 14
// ********************************************************************************

/// Factor for the working memory used by the Junge Grimme decoder
/**
 * This means that 3 * JUNGE_GRIMME_MAX_PACKED_SIZE * numberOfPixels *
 * sizeof(float) bytes are allocated during parsing. It limits the
 * maximum number of elements of packed(!) fields to
 * JUNGE_GRIMME_MAX_PACKED_SIZE times numberOfPixels elements.
 */
#define JUNGE_GRIMME_MAX_PACKED_SIZE 1


#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
 * @}
 */

#endif /*__ALLOCATIONLIMITS_H__*/
