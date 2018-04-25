/****************************************************************************\
 * Copyright (C) 2016 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/
#ifndef __TRACER_H__
#define __TRACER_H__

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SPECTRE_ENABLE_TRACER
#define SPECTRE_ENABLE_TRACER 0
#endif

#ifdef _MSC_VER
#define SPECTRE_TRACE_FUNCTION __FUNCTION__
#else
#define SPECTRE_TRACE_FUNCTION __func__
#endif

#define SPECTRE_NULLPTR (void*)0;
#define SPECTRE_TRACE(...) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTrace (SPECTRE_TRACE_FUNCTION, __VA_ARGS__); } while (0)
#define SPECTRE_TRACE_UINT32_BITS(MSG, UINT) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTraceUint32Bits(MSG, UINT); } while(0)
#define SPECTRE_TRACE_UINT32S(MSG, ARRAY, SIZE) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTraceUint32s(MSG, ARRAY, SIZE); } while(0)
#define SPECTRE_TRACE_UINT8S(MSG, ARRAY, SIZE) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTraceUint8s(MSG, ARRAY, SIZE); } while(0)
#define SPECTRE_TRACE_FLOATS(MSG, ARRAY, SIZE) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTraceFloats(MSG, ARRAY, SIZE); } while(0)
#define SPECTRE_TRACE_INTS(MSG, ARRAY, SIZE) do { if (SPECTRE_ENABLE_TRACER) spectre_printfTraceInts(MSG, ARRAY, SIZE); } while(0)
/// Number of array values to print during trace
#define SPECTRE_TRACE_MAX_VALUES 32

/**
 * Prints a message to the stderr
 *
 * @param fmt format string
 */
void spectre_printfTrace (const char *func, const char *fmt, ...);

/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfTraceUint32s (const char *str, const uint32_t *array, long size);


/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfTraceInts (const char *str, const int *array, long size);

/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfTraceUint8s (const char *str, const uint8_t *array, long size);

/**
 * Prints an array to stderr
 *
 * @param str message to print before array
 * @param array array
 * @param size size of array
 */
void spectre_printfTraceFloats (const char *str, const float *array, long size);

void spectre_printfTraceUint32Bits (const char *str, uint32_t bits);

#ifdef __cplusplus
}
#endif

#endif /*__TRACER_H__*/
