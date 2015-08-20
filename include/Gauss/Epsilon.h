/*
 * Epsilon.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_EPSILON_H__
#define __GS_EPSILON_H__


#include "Real.h"


namespace Gs
{


/**
Structure with a value which is very small (~0.000001)
which can be used for zero comparision with floating-point values.
\code
bool IsNearlyZero(float x)
{
    return std::abs(x) <= Gs::Epsilon<float>::value;
}
\endcode
\tparam T Specifies the data type. This structure is only defined for float and double!
*/
template <typename T>
struct Epsilon
{
    static const T value;
};

template <>
const float Epsilon<float>::value = 1.0e-6f;//0.000001f;

template <>
const double Epsilon<double>::value = 1.0e-8;//0.00000001;


} // /namespace Gs


#endif



// ================================================================================
