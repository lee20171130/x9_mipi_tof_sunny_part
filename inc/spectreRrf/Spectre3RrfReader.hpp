/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __SPECTRE3RRFREADER_HPP__
#define __SPECTRE3RRFREADER_HPP__

#include <string>
#include <memory>

#include "RrfHandleHolder.hpp"
#include <spectre3/ISpectre.hpp>

namespace spectre
{
    namespace rrfLib
    {
        class Spectre3RrfReader
        {
        public:
            explicit Spectre3RrfReader (const std::string &filename);

            ISpectre &spectre()
            {
                return *m_spectre;
            }

            inline const ISpectre &spectre() const
            {
                return *m_spectre;
            }

            ~Spectre3RrfReader();

            /**
             * @brief Gets an Input instance for the given frame from the RRF
             *
             * This function does not apply the configuration, but only the raw data to the underlying ISpectre instance.
             *
             * Note: The returned Input is invalidated if the state of the underlying Spectre3RrfReader is modified
             * (e.g., by getting another frame).
             *
             * @param loop if true the RRF will be played from the beginning if called on the last frame
             *
             *
             * @return input object
             */
            Input<ArrayReference> &inputForNextFrame (bool loop = false);

            /**
             * @brief Gets an Input instance for the given frame from the RRF
             *
             * Note: The returned Input is invalidated if the state of the underlying Spectre3RrfReader is modified
             * (e.g., by getting another frame).
             *
             * @param frameNumber number of frame
             *
             * @return input object
             */
            Input<ArrayReference> &inputForFrame (uint32_t frameNumber);


            /**
             * @brief Applies the configuration of the current RRF frame to the ISpectre instance
             */
            void applyConfiguration();

            /**
             * @brief Gets the number of frames in the RRF
             *
             *
             * @return number of frames
             */
            uint32_t getNumFrames() const;

        private:
            std::unique_ptr<spectre::ISpectre> m_spectre;
            rrfLib::RrfHandleHolder m_rrf;
            royale_frame_v3 *m_frame;
            uint32_t m_frameNumber;
            Input<ArrayReference> m_input;
        };
    }  // rrfLib
}


#endif /*__SPECTRE3RRFREADER_HPP__*/
