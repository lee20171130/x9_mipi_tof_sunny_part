/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#pragma once

#include <record/RRFReader.h>
#include <cstring>

/** \brief returns the size of a specified additional data from the rrfv2 format.
 * The required additional data struct is determined by a given string code.
 *
 * \param handle initialized royale handle
 * \param frameNumber specifies a frame number
 * \param dataName specifies an additional data struct by its related string code
 * \return size of the given additional data struct or an error code
 */
size_t getAddDataSize (royale_rrf_handle handle, const uint32_t frameNumber, const char *dataName);


/** \brief reads specifed additional data from the rrfv2 format.
 * The required additional data struct is determined by a given string code.
 *
 * \param handle royale handle
 * \param frameNumber specifies a frame number
 * \param dataName specifies an additional data struct by its related string code
 * \param outData data content
 */
template<typename T>
void readAdditionalData (royale_rrf_handle handle, const uint32_t frameNumber, const char *dataName, T *outData)
{
    royale_frame_v3 *frame;
    if (royale_seek (handle, frameNumber) == RRF_NO_ERROR &&
            royale_get_frame (handle, &frame) == RRF_NO_ERROR)
    {
        for (size_t idx = 0; idx < frame->frameHeader.numAdditionalData; idx++)
        {
            auto addData = frame->additionalData[idx];
            if (strcmp (addData.dataName, dataName) == 0)
            {
                memcpy (outData, addData.data, static_cast<size_t> (addData.dataSize));
            }
        }
        royale_free_frame (&frame);
    }
    else
    {
        throw "Could not get frame for additional data.";
    }
}
