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
#define _CRT_SECURE_NO_WARNINGS

#include <sample/spectreSample.hpp>

#include <sstream>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <thread>
#ifndef SPECTRESAMPLECALC_H
#define SPECTRESAMPLECALC_H


#include <system/toolsTimer.hpp>
#include <system/toolsIO.hpp>
#include <system/BoundaryConditionsManager.hpp>
#include <system/SystemIOReal.hpp>
#include <common/version.hpp>

#ifdef __cplusplus
extern "C" {
#include <processing/processingInternal.hpp>
}
#endif

#define char_CAST( param ) reinterpret_cast<char *> ( param )

namespace spectre
{
    namespace sample
    {

        std::string getDefaultDataPath();

        /** \brief data structure containing general data
         */
        struct Data
        {
            struct SpectreCalibration *ps_calib; ///< spectre calibration struct
            struct SpectreParameter *ps_param; ///< spectre parameter struct
            struct SpectreInput *ps_input; ///< spectre input struct
            struct SpectreOutput *ps_output; ///< spectre output struct
            struct SpectreIntermediate *ps_inter; ///< spectre intermediate struct

            std::string workingDir = getDefaultDataPath(); ///< path to binary sample files
            uint32_t numFrames = 1; ///< number of frames
        };

        /** \brief data structure containing calculation results
         */
        struct Calculation
        {
            float meanDistance = 0.0f; ///< mean distance
            float minDistance = 0.0f; ///< minimal distance
            float maxDistance = 0.0f; ///< maximal distance
            int numValidPixels = 0; ///< number of valid pixels
        };

        /** \brief initializes spectre
         *
         * \param data initialized data structure
         */

        void initSpectre (struct Data &data);

        /** \brief frees allocated memory for data
         *
         * \param data preallocated data structure
         */

        void freeMemory (struct Data &data);

        /** \brief calculates mean distance and valid pixels
         *
         * \param numPixels number of pixels
         * \param distances distance results after processing spectre
         * \param flags activated flags after processing spectre
         * \param calcData structure where calculated mean distance and valid pixels will be stored at
         */

        void calcMeanDistanceAndValidPixels (uint32_t numPixels, float *distances, uint32_t *flags, struct Calculation &calcData);

        /** \brief calculates minimum and maximum distance
         *
         * \param numPixels number of pixels
         * \param calcData structure where calculated minimum and maximum distance will be stored at
         * \param coords activated flags after processing spectre
         */

        void calcMinAndMaxDistance (uint32_t numPixels, struct Calculation &calcData, float *coords);

        /** \brief prints mean distance and valid pixels
         *
         * \param calcData structure that containes calculated mean distance and valid pixels
         *
         * \sa calcMeanDistanceAndValidPixels (uint32_t numPixels, float *distances, uint32_t *flags, struct Calculation &calcData)
         */

        void printMeanDistanceAndValidPixels (struct Calculation &calcData);

        /** \brief prints minimum and maximum distance
         *
         * \param calcData structure that containes calculated minimum and maximum distance
         *
         * \sa calcMinAndMaxDistance (uint32_t numPixels, struct Calculation &calcData, float * coords)
         */

        void printMinAndMaxDistance (struct Calculation &calcData);
    }
}

#endif
