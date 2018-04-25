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


#include <fstream>
#include <memory>

#include <string>
#include <map>
#include <system/toolsTimer.hpp>

using TimerMap = std::map <std::string, Timer> ;

extern TimerMap timerMap;
extern std::string workingDir_e;