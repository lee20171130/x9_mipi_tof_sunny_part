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

#include <cstring>

#include <record/RRFReader.h>
#include <calibration/calibration.h>
#include <processing/processing.hpp>
#include <system/toolsIO.hpp>

/** \brief creates a SpectreInput struct from rrf data
 *
 * \param handle royale handle to rrf data
 * \param framenumber specifies a frame number
 * \return created SpectreInput struct
 */
SpectreInput *createSpectreInputFromHandle (royale_rrf_handle handle, const uint32_t frameNumber = 0);

/** \brief creates a SpectreParameter struct from rrf data
 *
 * \param handle royale handle to rrf data
 * \param framenumber specifies a frame number
 * \return created SpectreParameter struct
 */
SpectreParameter *createSpectreParamFromHandle (royale_rrf_handle handle, const uint32_t frameNumber = 0);

/** \brief creates a SpectreCalibration struct from rrf data
 *
 * \param handle royale handle to rrf data
 * \return created SpectreCalibration struct
 */
SpectreCalibration *createSpectreCalibFromHandle (royale_rrf_handle handle);

/** \brief creates a SpectreInput struct with allocated memory
 *
 * \param handle initialized royale handle
 * \return allocated SpectreInput struct
 */
SpectreInput *createSpectreInput (royale_rrf_handle handle);

/** \brief copies rrf data to preallocated SpectreInput struct
 *
 * \param handle initialized royale handle
 * \param input preallocated SpectreInput struct e.g. using createSpectreInput()
 * \param frameNumber specifies a frame number
 * \sa createSpectreInput (royale_rrf_handle &handle)
 */
void copyHandle2SpectreInput (royale_rrf_handle handle, SpectreInput &input, const uint32_t frameNumber);

/** \brief creates a SpectreInput struct from rrf data
 *
 * \param pathToFile path to an rrf file
 * \param framenumber specifies a frame number
 * \return created SpectreInput struct
 */
SpectreInput *createSpectreInputFromRrfFile (const char *pathToFile, const uint32_t frameNumber = 0);

/** \brief creates a SpectreParameter struct from rrf data
 *
 * \param pathToFile path to an rrf file
 * \param framenumber specifies a frame number
 * \return created SpectreParameter struct
 */
SpectreParameter *createSpectreParamFromRrfFile (const char *pathToFile, const uint32_t frameNumber = 0);

/** \brief creates a SpectreCalibration struct from rrf data
 *
 * \param pathToFile path to an rrf file
 * \return created SpectreCalibration struct
 */
SpectreCalibration *createSpectreCalibFromRrfFile (const char *pathToFile);

/** \brief returns the frame rate of a certain frame of the given rrf data
 *
 * \param handle royale handle to rrf data
 * \param frameNumber specifies a frame number
 * \return frame rate of the specified frame
 */
uint16_t getFrameRateFromHandle (royale_rrf_handle &handle, const uint32_t frameNumber = 0);

/** \brief returns the frame rate of a cerrtain frame of the given rrf data
 *
 * \param pathToFile path to an rrf file
 * \param frameNumber specifies a frame number
 * \return frame rate of the specified frame
 */
uint16_t getTargetFrameRate (const char *pathToFile, const uint32_t frameNumber = 0);

/** \brief returns the number of frames contained in the given rrf data
 *
 * \param handle royale handle to rrf data
 * \return number of frames
 */
uint32_t getNumFramesFromHandle (royale_rrf_handle &handle);

/** \brief returns the number of frames contained in the given rrf data
 *
 * \param pathToFile path to an rrf file
 * \return number of frames
 */
uint32_t getNumFrames (const char *pathToFile);

/** \brief Gets the maximum number of rows in the given RRF
*
* \param pathToFile path to an rrf file
* \return number of rows
*/
uint16_t getMaxHeightFromHandle (royale_rrf_handle handle);

/** \brief Gets the maximum number of columns in the given RRF
*
* \param pathToFile path to an rrf file
* \return number of columns
*/
uint16_t getMaxWidthFromHandle (royale_rrf_handle handle);
