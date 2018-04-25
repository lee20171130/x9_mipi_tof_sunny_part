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

namespace spectre
{
    namespace access
    {

        enum class AccessLevel
        {
            UNDEFINED = 0,      //!< Undefined user access, will be determined by registry
            LEVEL1 = 1,         //!< General restricted user access
            LEVEL2 = 2,         //!< Extended user access
            LEVEL3 = 3          //!< Internal use only
        };

    }
}
