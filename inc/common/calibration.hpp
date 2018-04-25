/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#pragma once

#include <stdint.h>
#include <common/allocationLimits.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Straylight specific calibration
struct SpectreCalibrationStraylight
{
    // pre-factor for the values of the PSF.
    /**
     * Doubling this value would double all values of the resultant PSF (except its central pixel).
     */
    float strayAmplitude;
    /// X-values of the (1D) spline parametrization of the PSF
    float strayNodesX[MAX_NUM_STRAY_LIGHT_NODES];
    /// Y-values of the (1D) spline parametrization of the PSF
    float strayNodesY[MAX_NUM_STRAY_LIGHT_NODES];
    /// L_p norm to compute the distance (in pixels) from the PSF's center
    float pNorm;
    // Constant background which is added to all pixels of the PSF
    float background;
    /// The pixel in the center of the PSF (central beam) will obtain this value, regardless of all other parameters (stray_*, background).
    float psfCenterValue;
    /// The array size (x and y) of the created PSF.
    unsigned psfSize[2];
    /// Number of straylight interpolation nodes
    uint8_t numStrayNodes;
};


/**
*   Probe specific calibration data
*/
struct SpectreCalibrationWiggling
{
    uint8_t size;                   ///< Total number of wiggling correction terms.
    float *pv_amplitude;            ///< Wiggling correction amplitude value of a specific harmonic ( d0:size )
    uint32_t *pv_harmonic;          ///< Wiggling correction order values of the harmonics ( d0:size )
    float *pv_phase;                ///< Wiggling correction amplitude value of a specific harmonic ( d0:size )
    float offset;                   ///< Wiggling correction offset value used for data adaptation
};


/**
*   Probe specific calibration data
*/
struct SpectreCalibrationProbeData
{
    // fppn correction
    uint32_t frequency;             ///< Specific frequency the calibration data is intended for.
    float *pm_fppn;                 ///< calibration values used for "Fixed-Pattern-Phase-Noise" suppression ( d0:numColumns*numRows )

    // TemperatureCompensation
    uint8_t sizeTempCompensation;   ///< number of entry values for temperature compensation
    float *pv_tempCompensation;     ///< Container for temperature compensation values ( d0:sizeTempCompensation )

    // Noise cancellation
    uint8_t sizeNoiseParamter;      ///< number of entry values for noise parametrization
    float *pv_noiseParameter;       ///< Noise parameter used for the noise calcultaion

    /// Mean efficiency factor (value can be undefined)
    float meanEfficiency;

    // Wiggling correction
    struct SpectreCalibrationWiggling ps_phaseWiggling;           // Wiggling corretion information for phase wiggling compensation.
    struct SpectreCalibrationWiggling ps_amplitudeWiggling;       // Wiggling corretion information for amplitude wiggling compensation.
};


/**
 *   Costum data, not interpreted by spectre
 */
struct SpectreCalibrationCustomData
{
    uint8_t *data;
    uint8_t size;
};

/**
*   Hardware and calibration related sensor information
*/
struct SpectreCalibration
{
    /// Version of the calibration structure
    // 1: ASTON
    uint16_t version;
    /// Type of the underlying calibration data (corresponds to the enum spectre_CalibrationType)
    uint16_t type;                          ///< Calibration data type, value corresponds to SpectreTypeCalibration definition

    char *pc_date;                          ///< Date of generation ( d0:19 )
    char *pc_serial;                        ///< Serial number of the device ( d0:9 )
    char *pc_sensorSerial;                  ///< Serial number of the specific sensor ( d0:19 )

    uint8_t *pv_productCode;                ///< Product Code (d0: lengthProductCode)
    uint8_t lengthProductCode;              ///< length of product code

    uint32_t *pv_calibrationROI;            ///< Storage location of the calibration data absolute sensor coordinates [startColum startRow ColumWidth ColumnHeight]

    float *pm3d_directions;                 ///< Array of vectorinformation used for depth data transformation  ( d0:calibrationROI[2]*calibrationROI[3]*3 )

    uint8_t sizeLensParam;                  ///< total number of lensparameter entry values.
    float *pv_lensparam;                    ///< Parameters of the lensdata ( d0:sizeLensParam )

    uint16_t *pv_lenscenter;                ///< Storage location of the lenscenter [x-coordinate y-coordinate]

    /// Parametrization of the PSF
    struct SpectreCalibrationStraylight straylight;

    /// Inverse value of point-spread function for straylight correction in Fourier space (1.0 + psf[x])^(-1)
    float *ipsf;

    /// Type of LensModel
    /**
     * 1: Polynomial (OpenCV) LensModel
     */
    uint_fast8_t lensModel;
    uint8_t *pm_mask;                       ///< Mask of invalid image areas ( d0:calibrationROI[2]*calibrationROI[3] )
    float *pm_fpn;                          ///< ps_calib->ation values used for "Fixed-Pattern-Noise" suppression ( d0:calibrationROI[2]*calibrationROI[3] )

    /**
     *  Size of the per frequency data
     *
     *  At the moment this should correspondend to the values of the SpectreTypeCalibration enum
     */
    uint8_t sizeProbeData;
    struct SpectreCalibrationProbeData *pns_probeData;      ///< Container for frequency specific ps_calib->ation data ( d0:sizeProbeData )
    uint8_t sizeCustomData;
    struct SpectreCalibrationCustomData *pns_customData;    ///< Container for costum data ( d0:sizeCostumData )
    uint8_t customDataStartId;                              ///< start id for custom data access ( or UNINITIALIZED_UINT_FIELD if not supported by the current format )
};

#ifdef __cplusplus
}
#endif
