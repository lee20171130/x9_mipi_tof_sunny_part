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

#define VNAME(x) #x

#include <gmock/gmock.h>
#include <climits>
#include <float.h>
#include <limits>
#include <system/toolsIO.hpp>

#include <processing/common/commonMethods.hpp>
#include <system/compare.hpp>

/**
 * Calculates the combined unique range
 *
 * The combined unique range is defined as min(ur1, ur2) + ur1*n2 / (2*n1*n2)
 * where n1 and n2 are the proportion between the least common multiple of the frequencies
 * and the respective frequency.
 *
 *
 * @param modulationFrequency1 first modulation frequency
 * @param modulationFrequency2 second modulation frequency
 *
 * @return const ur_c
 */
float calculateCombinedUniqueRange (int modulationFrequency1 , int modulationFrequency2);

/**
 * Calculates the maximum absolute allowed distance deviation for a given pixel
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference noise
 *
 * @return limit in m
 */
float calculateLimit (float refDist, float calDist, float refDistNoise);

/**
 * Checks if a calculated distance is within the acceptable limit to a reference distance
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param urc combined unambigious range (0.0 for one frequency)
 *
 * @return true if the distance is within the definied limits
 */
bool checkDistance (float refDist, float calDist, float refDistNoise, float urc);

/**
 * Compares an array of calculated distances to an array of reference distance
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 * @param urc combined unambigous range
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size,
                          float urc);

/**
 * Compares an array of calculated distances to an array of reference distances
 * Convenience method for two frequencies
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 * @param modulationFrequency1 first frequency
 * @param modulationFrequency2 second frequency
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size,
                          uint32_t modulationFrequency1,
                          uint32_t modulationFrequency2);
/**
 * Compares an array of calculated distances to an array of reference distances
 * Convenience method for one frequency
 *
 * @param refDist reference distance
 * @param calDist calculated distance
 * @param refDistNoise reference distance noise
 * @param size size of arrays
 *
 * @return number of mismatches
 */
uint32_t compareDistance (const float *refDist,
                          const float *calDist,
                          const float *refDistNoise,
                          uint32_t size);


/**
* Merges a set of two flag maps into a
* combined one. The flag state for the combined
* flag map is set either to 1 := flag set or
* 0:= flag unset. If the validate flag is set also
* the flag values of the input map is set
* either to 0 or 1.
*
* @param flagsMapOne first flag map used for merge
* @param flagsMapTwo second flag map used for merge
* @param flagsMapMerged resulting flag map with reduced flag state
* @param numPixel common size of the flag maps
* @param validate
*/
inline void mergeAndUnifyFlags (uint32_t *flagsMapOne,
                                uint32_t *flagsMapTwo,
                                uint32_t *flagsMapMerged,
                                size_t numPixel,
                                uint8_t validate = 0)
{
    for (uint32_t idx = 0; idx < numPixel; ++idx)
    {
        if (flagsMapOne[idx] != 0 || flagsMapTwo[idx] != 0)
        {
            flagsMapMerged[idx] = 1;
        }
        else
        {
            flagsMapMerged[idx] = 0;
        }

        if (validate != 0)
        {
            if (flagsMapOne[idx] != 0)
            {
                flagsMapOne[idx] = 1;
            }

            if (flagsMapTwo[idx] != 0)
            {
                flagsMapTwo[idx] = 1;
            }
        }
    }
}

/**
 * Splits a given coordinate array with the layout [x1,y1,z1,c1,x2,y2,z2,c2,...,xn,yn,zn,cn] into a tuple of vectors where all x_i
 * are in the first member of the tuple, all y_i in the second member, and so on.
 *
 * @param coordinates coordinate vector
 *
 * @return tuple of vectors
 */
std::tuple<std::vector<float>, std::vector<float>, std::vector<float>, std::vector<float> > splitCoordinates (std::vector<float> coordinates);
