/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __IDTABLE_H__
#define __IDTABLE_H__

#include <stdint.h>
#include <stddef.h>

#include <calibration/calibration.h>
#include <calibration/jg/Header.h>

static const int SPECTRE_NO_MINIMUM_ENTRIES = -1;

/// Holds information about validation errors occured during parsing
struct spectre_JGValidationError
{
    /// Status of operation
    enum spectre_CalibrationStatus status;
    /// Id of the field where the validation error occurred
    /**
     * The value SPECTRE_GRIMME_END_ID indicates that the field could not be determined,
     * or the error occurred outside of a field (e.g., during reading the file header)
     *
     * If status is success, the value of this field is undefined.
     */
    uint8_t id;
};

struct spectre_JGTableRoot;

/// Function which determines if a given block points to a unique frequency block
typedef int(*spectre_isFrequency)(struct spectre_JGBlockHeader*);

typedef enum spectre_CalibrationStatus (*spectre_validateBlock)(const struct spectre_JGBlockHeader*, void *);

typedef enum spectre_CalibrationStatus (*spectre_validateCalibration)(const struct spectre_JGTableRoot*, struct spectre_JGValidationError*);

/// Root entry of the dispatch table for the calibration structure
struct spectre_JGTableRoot
{
    /// Determines if a given data block identifies a unique frequency block
    spectre_isFrequency isFreq;
    /// Pointer to calibration structure which is filled by the dispatch table
    struct SpectreCalibration *calib;
    /// Contains all entries
    struct spectre_JGTableEntry *entries;
    /// Number of entries
    size_t numEntries;
    /// Maximum number of entries
    size_t maxEntries;
    /// Validation function
    spectre_validateBlock validateBlock;
    /// Validation data memory block
    void *validationData;
    /// Size of an validationData entry
    size_t sizeValidationEntry;
    /// start id of custom data blocks
    uint8_t customStartId;
    /// Validation function for the whole file
    /**
     * This function should be called after the parsing is completed.
     * And all relevant block wise validation functions were run.
     */
    spectre_validateCalibration validateWhole;
};

/// Table entry for mapping a "Junge Grimme" file to the calibration structure
/**
 * Each entry represents a 1<-->n mapping between a member in the SpectreCalibration
 * struct, and a field in a specific calibration configuration (identified by its id).
 */
struct spectre_JGTableEntry
{
    /// Identifier of field in calibration file
    uint8_t id;
    /// Pointer to destination
    /**
     * The pointer must be properly aligned for the type of id.
     */
    void *dst;
    /// Size of the dst
    /**
     * The size of dst in bytes if apply is NULL,
     * otherwise the value is interpreted by apply.
     */
    size_t dstSize;
    /// Adjusted size of dst
    /**
     * If not NULL the number of elements read are copied to this location.
     */
    uint8_t *adjustedDstSize;
    /// Minimum number of entries
    /**
     * If the field is in the calibration file, the number of elements written to dst is checked
     * against this value.
     * The value is decoded similar to the "Data block length" decoding scheme (the function c(l)),
     * that is:
     * c(0) = numPixel
     * c(i) = i, for i = 1,...,249
     * c(i) = (i - 249) * numPixel, for i = 250,...,255
     * c(i) = i, for i > 255
     *
     * A value of SPECTRE_NO_MINIMUM_ENTRIES means that no restriction applies.
     */
    int minimumEntries;
    /// Function apply(src, srcSize, dst, dstSize, adjustedDstSize)
    /**
     * If not NULL, the function is responsible to copy the values from src to dst,
     * where src contains the unpacked values from id, and srcSize is the
     * number of bytes contained in src.
     *
     * If adjustedDstSize is not NULL, the number of elements read are copied to this location.
     */
    enum spectre_CalibrationStatus (*apply)(const void*, size_t, void*, size_t, uint8_t*);

    /// Pointer to optional validation data
    /**
     * This pointer is passed to the spectre_validateBlock function. The spectre_validateBlock function
     * may modify the contents of this data. Its contents depend on the actual calibration configuration.
     */
    void *validationData;
};

/**
 * Adds a new entry to the table
 *
 * If validationData is passed it is copied during creation, and needs to be of size root->sizeValidationEntry bytes,
 * set during table creation.
 *
 * @param id identifier of entry to add
 * @param dst pointer to destination
 * @param dstSize size of dst
 * @param adjustedSize pointer to size of dst which is adjusted during call (can be NULL)
 * @param minimumEntries number of minimum entries (can be SPECTRE_NO_MINIMUM_ENTRIES to indicate that no restriction applies)
 * @param apply function pointer to apply function (can be NULL)
 * @param validationData pointer to validation data (can be NULL)
 * @param root root of table
 *
 * @return status of operation
 */
enum spectre_CalibrationStatus spectre_addJGTableEntry(uint8_t id, void *dst, size_t dstSize, uint8_t *adjustedDstSize, int minimumEntries,
                                                       enum spectre_CalibrationStatus (*apply)(const void*, size_t, void*, size_t, uint8_t*),
                                                       void *validationData, struct spectre_JGTableRoot *root);


/**
 * Finds an entry
 *
 * @param id identifier to find
 * @param root root of table
 *
 * @return found entry or NULL
 */
struct spectre_JGTableEntry* spectre_findJGTableEntry(uint8_t id, struct spectre_JGTableRoot *root);

/**
 * Creates a new dispatch table
 *
 * @param numEntries maximum number of table entries
 * @param blockValidationSize size of a data block validation entry
 *
 * @return pointer to new table root
 */
struct spectre_JGTableRoot* spectre_createTable(size_t numEntries, size_t blockValidationSize);

/**
 * Frees the whole table
 *
 * @param root starting point
 */
void spectre_freeJGTable(struct spectre_JGTableRoot* root);

#endif /*__IDTABLE_H__*/
