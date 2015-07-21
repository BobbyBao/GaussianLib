/*
 * Vector4.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_VECTOR4_H__
#define __GS_VECTOR4_H__


#include "Real.h"
#include "Assert.h"
#include "Algebra.h"

#ifdef GS_ENABLE_SWIZZLE_OPERATOR
#   include "SwizzleRef4.h"
#endif

#include <cmath>


namespace Gs
{


/**
Base 4D vector class with components: x, y, z, and w.
\tparam T Specifies the data type of the vector components.
This should be a primitive data type such as float, double, int etc.
*/
template <typename T> class Vector4T
{
    
    public:
        
        //! Specifies the number of vector components.
        static const std::size_t components = 4;

        Vector4T() :
            x( T(0) ),
            y( T(0) ),
            z( T(0) ),
            w( T(1) )
        {
        }

        Vector4T(const Vector4T<T>& rhs) :
            x( rhs.x ),
            y( rhs.y ),
            z( rhs.z ),
            w( rhs.w )
        {
        }

        explicit Vector4T(const T& scalar) :
            x( scalar ),
            y( scalar ),
            z( scalar ),
            w( T(1)   )
        {
        }

        Vector4T(const T& x, const T& y, const T& z, const T& w = T(1)) :
            x( x ),
            y( y ),
            z( z ),
            w( w )
        {
        }

        Vector4T<T>& operator += (const Vector4T<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }

        Vector4T<T>& operator -= (const Vector4T<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }

        Vector4T<T>& operator *= (const Vector4T<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }

        Vector4T<T>& operator /= (const Vector4T<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            w /= rhs.w;
            return *this;
        }

        Vector4T<T>& operator *= (const T& rhs)
        {
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }

        Vector4T<T>& operator /= (const T& rhs)
        {
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        /**
        \brief Returns the specified vector component.
        \param[in] component Specifies the vector component index. This must be 0, 1, 2, or 3.
        */
        T& operator [] (std::size_t component)
        {
            GS_ASSERT(component < Vector4T<T>::components);
            return *((&x) + component);
        }

        /**
        \brief Returns the specified vector component.
        \param[in] component Specifies the vector component index. This must be 0, 1, 2, or 3.
        */
        const T& operator [] (std::size_t component) const
        {
            GS_ASSERT(component < Vector4T<T>::components);
            return *((&x) + component);
        }

        //! Returns the squared length of this vector.
        T LengthSq() const
        {
            return Gs::LengthSq(*this);
        }

        //! Returns the length of this vector.
        T Length() const
        {
            return Gs::Length(*this);
        }

        /**
        Normalizes the vector to the unit length of 1.
        \see Normalized
        \see Length
        */
        void Normalize()
        {
            Gs::Normalize(*this);
        }

        /**
        Returns a normalized instance of this vector.
        \see Normalize
        */
        Vector4T<T> Normalized() const
        {
            auto vec = *this;
            vec.Normalize();
            return vec;
        }

        /**
        Returns a type casted instance of this vector.
        \tparam C Specifies the static cast type.
        */
        template <typename C> Vector4T<C> Cast() const
        {
            return Vector4T<C>(
                static_cast<C>(x),
                static_cast<C>(y),
                static_cast<C>(z),
                static_cast<C>(w)
            );
        }

        //! Returns a pointer to the first element of this vector.
        T* Ptr()
        {
            return &x;
        }

        //! Returns a constant pointer to the first element of this vector.
        const T* Ptr() const
        {
            return &x;
        }

        #ifdef GS_ENABLE_SWIZZLE_OPERATOR
        #   include "SwizzleOp4.h"
        #endif
        
        T x, y, z, w;

};


/* --- Global Operators --- */

template <typename T> Vector4T<T> operator + (const Vector4T<T>& lhs, const Vector4T<T>& rhs)
{
    auto result = lhs;
    result += rhs;
    return result;
}

template <typename T> Vector4T<T> operator - (const Vector4T<T>& lhs, const Vector4T<T>& rhs)
{
    auto result = lhs;
    result -= rhs;
    return result;
}

template <typename T> Vector4T<T> operator * (const Vector4T<T>& lhs, const Vector4T<T>& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector4T<T> operator / (const Vector4T<T>& lhs, const Vector4T<T>& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector4T<T> operator * (const Vector4T<T>& lhs, const T& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector4T<T> operator * (const T& lhs, const Vector4T<T>& rhs)
{
    auto result = rhs;
    result *= lhs;
    return result;
}

template <typename T> Vector4T<T> operator / (const Vector4T<T>& lhs, const T& rhs)
{
    auto result = lhs;
    result /= rhs;
    return result;
}


/* --- Appendix to SwizzleRef4 class --- */

#ifdef GS_ENABLE_SWIZZLE_OPERATOR

template <typename T> SwizzleRef4<T>::operator Vector4T<T> () const
{
    return Vector4T<T>(x_, y_, z_, w_);
}

template <typename T> SwizzleRef4<T>& SwizzleRef4<T>::operator = (const Vector4T<T>& rhs)
{
    x_ = rhs.x;
    y_ = rhs.y;
    z_ = rhs.z;
    w_ = rhs.w;
    return *this;
}

__GS_SWIZZLE_VECTOR_OP_ALL__(4)

#endif


/* --- Type Alias --- */

using Vector4 = Vector4T<Real>;
using Vector4f = Vector4T<float>;
using Vector4d = Vector4T<double>;
using Vector4i = Vector4T<int>;


} // /namespace Gs


#endif



// ================================================================================
