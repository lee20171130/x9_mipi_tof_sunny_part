/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __WRITER_H__
#define __WRITER_H__

#include <calibration/calibration.h>
#include <common/defines.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <calibration/jg/Header.h>
#include <calibration/jg/IdTable.h>

    /// Result of the calibration writer
    struct spectre_JGWriterResult
    {
        /// Validation information
        struct spectre_JGValidationError validationInfo;
        /// Pointer to the calibration data
        /**
         * Ownership of the pointer is transferred to the caller.
         *
         * If validationInfo.status is != SPECTRE_STATUS_SUCCESS
         * the field is NULL.
         */
        uint8_t *data;
        /// Size of the calibration data
        size_t size;
    };

    struct spectre_JGWriterHandle;

    /**
     * Creates a new handle for writting Junge Grimme calibration files
     *
     * Ownership of writer handle is transferred to caller.
     *
     * @param config configuration to write
     * @param width width of calibrated area
     * @param height height of calibrated area
     *
     * @return writer handle
     */
    SPECTRE_CALIBRATION_API struct spectre_JGWriterHandle* spectre_createJGWriterHandle(enum spectre_JGConfiguration config, uint16_t width,
                                                                           uint16_t height);

    /**
     * Adds an unsigned 8-bit field to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements in data
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGU8(uint8_t id, const uint8_t *data, uint32_t numElements, struct spectre_JGWriterHandle* handle);


    /**
     * Adds an unsigned 16-bit field to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements in data
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGU16(uint8_t id, const uint16_t *data, uint32_t numElements, struct spectre_JGWriterHandle* handle);


    /**
     * Adds an unsigned 32-bit field to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements in data
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGU32(uint8_t id, const uint32_t *data, uint32_t numElements, struct spectre_JGWriterHandle* handle);


    /**
     * Adds an signed 32-bit field to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements in data
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGS32(uint8_t id, const int32_t *data, uint32_t numElements, struct spectre_JGWriterHandle* handle);


    /**
     * Adds a float field to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements in data
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGFloat(uint8_t id, const float *data, uint32_t numElements, struct spectre_JGWriterHandle* handle);

    /**
     * Adds a packed field of 32-bit unsigned values to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements
     * @param bits bits per element in the packed format
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGPackedU32(uint8_t id, const uint32_t *data, uint32_t numElements, uint8_t bits, struct spectre_JGWriterHandle* handle);

    /**
     * Adds a packed field of fixed-point values to the calibration
     *
     * @param id id of field
     * @param data data to add
     * @param numElements number of elements
     * @param bits bits per element in the packed format
     * @param desc descriptor of fixed-point system
     * @param handle handle of writer
     *
     * @return status of operation
     */
    SPECTRE_CALIBRATION_API enum spectre_CalibrationStatus spectre_addJGPackedFixed(uint8_t id, const float *data, uint32_t numElements, uint8_t bits,
                                                            struct spectre_JGFixedPointDescriptor desc, struct spectre_JGWriterHandle* handle);

    /**
     * Creates a new calibration from the handle, and validates it on basis of the given configuration
     *
     * @param handle handle of writer
     *
     * @return result
     */
    SPECTRE_CALIBRATION_API struct spectre_JGWriterResult spectre_createJGCalibration(struct spectre_JGWriterHandle *handle);

    /**
     * Frees a writer handle
     *
     * @param handle handle of writer
     */
    SPECTRE_CALIBRATION_API void spectre_freeJGWriterHandle (struct spectre_JGWriterHandle *handle);
#ifdef __cplusplus
}
#endif

#endif /*__WRITER_H__*/
