/****************************************************************************\
 * Copyright (C) 2017 pmdtechnologies ag
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
\****************************************************************************/

#ifndef __CUBICINTERPOL_H__
#define __CUBICINTERPOL_H__

/**
 * @addtogroup libcalibration_internal
 * @{
 */

/// Handle to an interpolation polynomial
typedef void* spectre_polyHandle;

/**
 * @brief Precomputes data for the polynomial interpolation of a function f described by f(x_i) = y_i, for i = 0,...,numNodes - 1
 *
 * NOTE: This function assumes that x_i < x_{i+1} for i = 0,...,numNodes - 2
 *
 *
 * @param xk interpolation points
 * @param yk function values
 * @param numNodes number of nodes
 *
 * @return handle to polynomial
 */
spectre_polyHandle spectre_createPolyHandle(const float *xk, const float *yk, unsigned numNodes);

/**
 * @brief Frees a polynomial aquired by spectre_createPolyHandle
 *
 * @param polyHandle handle to polyHandle, if NULL the function returns gracefully
 */
void spectre_freePoly (spectre_polyHandle polyHandle);


/**
 * @brief Computes the interpolated function value for x
 *
 * @param polyHandle handle to polynomial
 * @param x point x
 *
 * @return interpolated value, NAN if x lies outside of the convex hull of the interpolation nodes
 */
float spectre_cinterpol(const spectre_polyHandle polyHandle,
                        float x);

/**
 * @brief Computes the interpolated function value for x
 *
 *
 * @param polyHandle handle to polynomial
 * @param x point x
 * @param def default value to return
 *
 * @return interpolated value, or def if x lies outside the convex hull of the interpolation nodes
 */
float spectre_cinterpol_def(const spectre_polyHandle polyHandle,
                            float x, float def);

/// @}

#endif /*__CUBICINTERPOL_H__*/
