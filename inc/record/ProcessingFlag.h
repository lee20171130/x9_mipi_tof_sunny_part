/****************************************************************************\
 * Copyright (C) 2015 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

/*!
 *  This is a list of flags which can be set/altered in access LEVEL 2 in order
 *  to control the processing pipeline. The suffix type indicates the expected Variant type.
 *  Keep in mind, that if this list is changed, the map with names has to be adapted!
 */
enum  ProcessingFlag
{
    ConsistencyTolerance_Float = 0,     ///< Consistency limit for asymmetry validation
    FlyingPixelsF0_Float,               ///< Scaling factor for lower depth value normalization
    FlyingPixelsF1_Float,               ///< Scaling factor for upper depth value normalization
    FlyingPixelsFarDist_Float,          ///< Upper normalized threshold value for flying pixel detection
    FlyingPixelsNearDist_Float,         ///< Lower normalized threshold value for flying pixel detection
    LowerSaturationThreshold_Int,       ///< Lower limit for valid raw data values
    UpperSaturationThreshold_Int,       ///< Upper limit for valid raw data values
    MPIAmpThreshold_Float,              ///< Threshold for MPI flags triggered by amplitude discrepancy
    MPIDistThreshold_Float,             ///< Threshold for MPI flags triggered by distance discrepancy
    MPINoiseDistance_Float,             ///< Threshold for MPI flags triggered by noise
    NoiseThreshold_Float,               ///< Upper threshold for final distance noise
    AdaptiveNoiseFilterType_Int,        ///< Kernel type of the adaptive noise filter
    AutoExposureRefAmplitude_Float,     ///< The reference amplitude for the new exposure estimate
    UseAdaptiveNoiseFilter_Bool,        ///< Activate spatial filter reducing the distance noise
    UseAutoExposure_Bool,               ///< Activate dynamic control of the exposure time
    UseRemoveFlyingPixel_Bool,          ///< Activate FlyingPixel flag
    UseMPIFlagAverage_Bool,             ///< Activate spatial averaging MPI value before thresholding
    UseMPIFlag_Amp_Bool,                ///< Activates MPI-amplitude flag
    UseMPIFlag_Dist_Bool,               ///< Activates MPI-distance flag
    UseValidateImage_Bool,              ///< Activates output image validation
    UseRemoveStrayLight_Bool,           ///< Activates the stray light correction
    NUM_FLAGS                           ///< Number of supported flags
};
