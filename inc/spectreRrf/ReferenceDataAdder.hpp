/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __REFERENCEDATAADDER_HPP__
#define __REFERENCEDATAADDER_HPP__

#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <spectreRrf/ReferenceDataKey.hpp>

namespace spectre
{
    namespace rrfLib
    {
        /// Utility class to write reference data to a RRF
        class ReferenceDataAdder
        {
        public:
            /**
             * Ctor
             *
             * @param aNumPixel number of pixels in the RRF
             */
            explicit ReferenceDataAdder (unsigned aNumPixel);
            ~ReferenceDataAdder();

            /**
             * Adds reference data to a given frame
             * This function must not be used for ReferenceDataKey::FLAGS
             *
             * @param frameNr frame number
             * @param key kind of data
             * @param data reference
             *
             * @return *this
             */
            ReferenceDataAdder &addDataToFrame (unsigned frameNr, ReferenceDataKey key, const std::vector<float> &data);

            /**
             * Adds reference data for flags to a given frame
             *
             * @param frameNr frame number
             * @param data reference data
             *
             * @return *this
             */
            ReferenceDataAdder &addFlagsToFrame (unsigned frameNr, const std::vector<uint32_t> &data);

            /**
             * Writes a new RRF with the reference data specified previously.
             * Note: This discards any reference data already present in the input RRF. Also inFile, and outFile
             * *must not* be the same file.
             *
             * @param inFile original RRF
             * @param outFile new RRF
             * @param skip if true all frames for which no reference data was added are skipped and not written to the outFile
             *
             * @return true if operation was successful
             */
            bool writeRrfWithReferenceData (const std::string &inFile, const std::string &outFile, bool skip) const;

        private:
            bool hasData (unsigned frameNr) const;

        private:
            unsigned m_numPixel;
            typedef std::map<ReferenceDataKey, void * > FrameRefData;
            std::map<unsigned, FrameRefData> m_refData;
        };
    }
}

#endif /*__REFERENCEDATAADDER_HPP__*/
