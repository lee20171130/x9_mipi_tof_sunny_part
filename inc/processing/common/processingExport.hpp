/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __PROCESSINGEXPORT_HPP__
#define __PROCESSINGEXPORT_HPP__

// Export Definition
#ifdef SPECTRE_PROCESSING_SHARED
#if defined(_WIN32) && !defined(SPECTRE_PROCESSING_EXPORT)
#define SPECTRE_PROCESSING_API __declspec( dllimport  )
#elif defined(_WIN32)
#define SPECTRE_PROCESSING_API __declspec( dllexport )
#elif defined(SPECTRE_PROCESSING_EXPORT)
#define SPECTRE_PROCESSING_API __attribute__ ((visibility ("default")))
#else
#define SPECTRE_PROCESSING_API
#endif
#else
#define SPECTRE_PROCESSING_API
#endif

#endif /*__PROCESSINGEXPORT_HPP__*/
