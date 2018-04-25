/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifdef _MSC_VER
#define SPECTRE_INLINE __inline
#else
#define SPECTRE_INLINE inline
#endif

#ifdef _MSC_VER
#define SPECTRE_SNPRINTF(S,N,FMT,...) _snprintf_s(S,N,N - 1, FMT, __VA_ARGS__)
#else
#define SPECTRE_SNPRINTF(...) snprintf(__VA_ARGS__)
#endif
