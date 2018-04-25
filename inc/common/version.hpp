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

// Export Definition
#ifdef SPECTRE_COMMON_SHARED
#if defined(_WIN32) && !defined(SPECTRE_COMMON_EXPORT)
#define SPECTRE_COMMON_API __declspec( dllimport  )
#elif defined(_WIN32)
#define SPECTRE_COMMON_API __declspec( dllexport )
#elif defined(SPECTRE_COMMON_EXPORT)
#define SPECTRE_COMMON_API __attribute__ ((visibility ("default")))
#else
#define SPECTRE_COMMON_API
#endif
#else
#define SPECTRE_COMMON_API
#endif


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* Retrieves current version number
*/
SPECTRE_COMMON_API const char *spectre_getVersion();

/**
* Returns the git description string of
* revision that was used to build the binary
*/
SPECTRE_COMMON_API const char *spectre_getGitDescription ();

#ifdef __cplusplus
}
#endif
