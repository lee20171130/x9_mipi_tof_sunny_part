/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__


// Export Definition
#ifdef SPECTRE_CALIBRATION_SHARED
#if defined(_WIN32) && !defined(SPECTRE_CALIBRATION_EXPORT)
#define SPECTRE_CALIBRATION_API __declspec( dllimport  )
#elif defined(_WIN32)
#define SPECTRE_CALIBRATION_API __declspec( dllexport )
#elif defined(SPECTRE_CALIBRATION_EXPORT)
#define SPECTRE_CALIBRATION_API __attribute__ ((visibility ("default")))
#else
#define SPECTRE_CALIBRATION_API
#endif
#else
#define SPECTRE_CALIBRATION_API
#endif


/**
 * @defgroup libcalibration libcalibration - Spectre Calibration Handling
 * @brief The libcalibration is the C implementation of Spectre's calibration reading, and writing functionality.
 *
 * The public interface of libcalibration exposes functionality to read calibration files, and exposes only limited information about the calibration's content.
 * It is available through the header file calibration/calibration.h.
 * This interface can be used to read calibration through ::spectre_readCalibration, and aquire a handle to a SpectreCalibration structure which can be used by the
 * processing module. Additionally, the functions ::spectre_getCalibrationTypeFromHandle, and ::spectre_getField allow to retrieve the type of the calibration, and
 * the contents of certain fields (defined by #spectre_CalibrationField).
 *
 * A high-level overview on libcalibration, its architecture, and specifications of the supported calibration formats
 * can be found in the Sect. [Calibration handling](@ref calibration_handling).
 *
 * @{
 */

#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <common/defines.h>
#include <common/CalibrationField.def>

#ifdef __cplusplus
extern "C" {
#endif

/// Uncompressed calibration suitable for the processing
struct SpectreCalibration;

/// Calibration format
enum spectre_CalibrationType
{
    /// Unsupported format
    SPECTRE_TYPE_UNSUPPORTED,
    /// Legacy PMD TAR format
    SPECTRE_TYPE_LEGACY,
    /// ASTON old (Spectre) calibration format
    SPECTRE_TYPE_ASTON,
    /// JungeGrimme (Spectre) calibration format
    SPECTRE_TYPE_JUNGE_GRIMME
};

/// Status of operations in libcalibration
enum spectre_CalibrationStatus
{
    /// The requested field is unknown to libcalibration
    SPECTRE_STATUS_UNKNOWN_FIELD = INT_MIN,
    /// The requested field is not supported for the given calibration type
    SPECTRE_STATUS_UNSUPPORTED_FIELD,
    /// The requested custom field has not yet been parsed
    SPECTRE_STATUS_CUSTOM_FIELD_NOT_PARSED,
    /// The calibration blob is in an unsupported format
    SPECTRE_STATUS_UNSUPPORTED_FORMAT,
    /// The calibration blob ended unexpectedly
    SPECTRE_STATUS_UNEXPECTED_END,
    /// Invalid arguments where passed to the callee,
    SPECTRE_STATUS_INVALID_ARGUMENTS,
    /// A field has faild the validation
    SPECTRE_STATUS_INVALID_FIELD,
    /// A dynamic field in the calibration is bigger the defined maximum size
    SPECTRE_STATUS_MAXIMUM_SIZE_EXCEEDED,
    /// The minimum number of elements for a calibration field was violated
    SPECTRE_STATUS_MINIMUM_SIZE_VIOLATED,
    /// The calibration data is corrupt
    SPECTRE_STATUS_DATA_CORRUPT,
    /// A required field is missing
    SPECTRE_STATUS_MISSING_FIELD,
    /// An unknown error occurred
    SPECTRE_STATUS_UNKNOWN_ERROR,
    /**
     *  The parsing of the calibration was successful, but some data is missing.
     *
     *  Missing data has been replaced by default values.
     *  Quality of the depth data processing might be degraded due to this fact.
     */
    SPECTRE_STATUS_SUCCESS_INCOMPLETE,
    /// The operation succeeded
    SPECTRE_STATUS_SUCCESS = 0
};

#define SPECTRE_ENUM_NAME(KEY,...) SPECTRE_FIELD_##KEY,
/// Publicly exposed calibration fields
enum spectre_CalibrationField
{
    SPECTRE_CALIBRATION_FIELDS (SPECTRE_ENUM_NAME)
};
#undef SPECTRE_ENUM_NAME


/*!\brief Publicly exposed custom calibration fields
 *
 * The custom field identifier of the first custom field starts at SpectreCalibration::customDataStartId,
 * the identifier of the following custom field is an adjacent integer, that is customDataStartId + 1,
 * and so on.
 */

/**
 * @brief Tries to determine the type of a calibration blob
 *
 * Users should use this function to determine if a given calibration blob is in a
 * format supported by libcalibration.
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return type of the calibration or UNSUPPORTED
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationType spectre_getCalibrationType (const uint8_t *calibBlob, size_t size);

/**
 * @brief Tries to determine the type of a calibration handle.
 *
 * @param calib given calibration
 *
 * @return type of the calibration or UNSUPPORTED
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationType spectre_getCalibrationTypeFromHandle (const struct SpectreCalibration *calib);

/**
 * @brief Deallocates the given spectre_Calibration
 *
 * If calib is (struct SpectreCalibration*)0 no operation is performed.
 *
 * @param calib pointer to calibration
 */
SPECTRE_CALIBRATION_API void spectre_freeCalibration (struct SpectreCalibration *calib);

/**
 * @brief Adds psf data to a given calibration structure.
 *
 * This function should not be called twice, since it modifies the calibration in a non-idempotent way.
 * If an error occurred calib remains unchanged.
 *
 *
 * @param calib given calibration structure
 * @param psf psf data
 * @param psfSize size of psf data
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addPsf (struct SpectreCalibration *calib,
        float *psf, size_t psfSize);

/**
 * @brief Adds 3d directions data to a given calibration structure.
 *
 * This function should not be called twice, since it modifies the calibration in a non-idempotent way.
 * If an error occurred calib remains unchanged.
 *
 *
 * @param calib given calibration structure
 * @param directions 3d directions data
 * @param numPixel number of pixels
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addDirections (struct SpectreCalibration *calib,
        float *directions, size_t numPixel);

/**
 * @brief Analog to spectre_readCalibration below. Additionally one can
 * adjust wether psf and 3d directions should be computed or not.
 *
 * The caller is the owner of the new spectre_Calibration object, and responsible to free it through
 * spectre_freeCalibration if the object is no longer needed.
 *
 * If an error occurred calib remains unchanged.
 *
 *
 * @param calibBlob pointer to the calibration blob
 * @param size size of calibBlob
 * @param calib pointer to pointer of spectre_Calibration
 * @param calculate if set to a non-zero value psf and 3d directions will be calculated, otherwise they won't be calculated
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_readCalibrationExt (const uint8_t *calibBlob, size_t size,
        struct SpectreCalibration **calib, int calculate);

/**
 * @brief Reads the given calibration blob, allocates a new SpectreCalibration, and fills it with the
 * calibration data contained in calibBlob.
 *
 * The caller is the owner of the new spectre_Calibration object, and responsible to free it through
 * spectre_freeCalibration if the object is no longer needed.
 *
 * If an error occurred calib remains unchanged.
 *
 *
 * @param calibBlob pointer to the calibration blob
 * @param size size of calibBlob
 * @param calib pointer to pointer of spectre_Calibration
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_readCalibration (const uint8_t *calibBlob, size_t size,
        struct SpectreCalibration **calib);

/**
 * @brief Reads the given calibration blob, and fills the custom data structure
 * within the passed spectre_Calibration structure. If an error occurred calib remains unchanged.
 *
 * @param calibBlob pointer to the calibration blob
 * @param size size of calibBlob
 * @param calib pointer to pointer of spectre_Calibration
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_readCustomFields (const uint8_t *calibBlob, size_t size,
        struct SpectreCalibration *calib);

/**
 *
 * @brief Gets the number of bytes of public calibration field for a given calibration.
 *
 * If the returned value is < 0 an error occurred. The function spectre_getStatusFromCode
 * can be used to derive a spectre_CalibrationStatus from the returned error code.
 *
 * The identifier of the first public custom field starts at SpectreCalibration::customDataStartId,
 * the identifier of the following custom field is an adjacent integer, that is customDataStartId + 1,
 * and so on.
 *
 * @param field requested field that can be a custom field identifier or an instance of spectre_CalibrationField
 * @param calib given calibration
 *
 * @return number of bytes (>= 0), or an error code (<0)
 */
SPECTRE_CALIBRATION_API int spectre_getFieldSize (int field, const struct SpectreCalibration *calib);

/**
 * @brief Copies all array elements of a given public calibration field to the given buffer.
 *
 * The caller is responsible for allocating the necessary amount of memory for dest, which should
 * be at least spectre_getFieldSize(field, calib). Ownership of the
 * passed buffer is retained by the caller.
 *
 * The identifier of the first public custom field starts at SpectreCalibration::customDataStartId,
 * the identifier of the following custom field is an adjacent integer, that is customDataStartId + 1,
 * and so on.
 *
 * @param field requested field that can be a custom field identifier or an instance of spectre_CalibrationField
 * @param calib given calibration
 * @param dest destination buffer
 *
 * @return status of operation
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_getField (int field,
        const struct SpectreCalibration *calib,
        void *dest);

/**
 * @brief Returns the number of public custom fields for a given calibration
 *
 * @param calib given calibration
 *
 * @return number of costum fields or SPECTRE_STATUS_UNKNOWN_FIELD
 */
SPECTRE_CALIBRATION_API int spectre_getNumCustomFields (const struct SpectreCalibration *calib);

/**
 * @brief Gets the version of libcalibration
 *
 * @return libcalibration version
 */
SPECTRE_CALIBRATION_API const char *spectre_getVersion();

/**
 * @brief Converts an error code to the corresponding SpectreCalibration value
 *
 * @param code error code
 *
 * @return corresponding value
 */
SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_getStatusFromCode (int code);


/**
 * @brief Gets the total amount of dynamic memory which will be allocated for the final
 * SpectreCalibration which contains the calibration after parsing and
 * uncompressing done by libcalibration.
 *
 * It is not guaranteed that this function is supported for all calibration types.
 * If the return value is < 0 an error occurred. Use the function spectre_spectre_getStatusFromCode
 * to convert the error code to a spectre_CalibrationStatus.
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return number of bytes to be allocated (>= 0), or an error code (< 0)
 */
SPECTRE_CALIBRATION_API int spectre_getCalibrationSize (const uint8_t *calibBlob, size_t size);

/**
 * @brief Gets the amount of dynamic memory which will be allocated during parsing and
 * uncompressing the given calibration blob.
 *
 * It is not guaranteed that this function is supported for all calibration types.
 * If the return value is < 0 an error occurred. Use the function spectre_spectre_getStatusFromCode
 * to convert the error code to a spectre_CalibrationStatus.
 *
 *
 * @param calibBlob pointer to calibration blob
 * @param size size of blob
 *
 * @return number of bytes to be allocated (>= 0), or an error code (< 0)
 */
SPECTRE_CALIBRATION_API int spectre_getTemporaryMemorySize (const uint8_t *calibBlob, size_t size);

#ifdef __cplusplus
}
#endif

/// @}

#endif /*__CALIBRATION_H__*/
