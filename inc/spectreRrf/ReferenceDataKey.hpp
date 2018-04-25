/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __REFERENCEDATAKEY_HPP__
#define __REFERENCEDATAKEY_HPP__

#include <string>

namespace spectre
{
    namespace rrfLib
    {

        /// Supported reference data types
        enum class ReferenceDataKey
        {
            DISTANCE, DISTANCE_NOISE, XYZC, AMPLITUDE, FLAGS
        };

        /**
         * Converts a ReferenceDataKey to the string used in the RRF additional data section
         *
         * @param key key to convert
         *
         * @return string representation
         */
        std::string keyToString (ReferenceDataKey key);
    }
}

#endif /*__REFERENCEDATAKEY_HPP__*/
