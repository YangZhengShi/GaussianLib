/*
 * Vector2.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_VECTOR2_H__
#define __GS_VECTOR2_H__


#include "Real.h"
#include "Assert.h"

#include <cmath>


namespace Gs
{


/**
Base 2D vector class with components: x, and y.
\tparam T Specifies the data type of the vector components.
This should be a primitive data type such as float, double, int etc.
*/
template <typename T> class Vector2T
{
    
    public:
        
        //! Specifies the number of vector components.
        static const size_t components = 2;

        Vector2T() :
            x{ T(0) },
            y{ T(0) }
        {
        }
        Vector2T(const Vector2T<T>& rhs) :
            x{ rhs.x },
            y{ rhs.y }
        {
        }
        explicit Vector2T(const T& scalar) :
            x{ scalar },
            y{ scalar }
        {
        }
        Vector2T(const T& x, const T& y) :
            x{ x },
            y{ y }
        {
        }

        Vector2T<T>& operator += (const Vector2T<T>& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Vector2T<T>& operator -= (const Vector2T<T>& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Vector2T<T>& operator *= (const Vector2T<T>& rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }

        Vector2T<T>& operator /= (const Vector2T<T>& rhs)
        {
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }

        Vector2T<T>& operator *= (const T& rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        Vector2T<T>& operator /= (const T& rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        /**
        \brief Returns the specified vector component.
        \param[in] component Specifies the vector component index. This must be 0, or 1.
        */
        T& operator [] (size_t component)
        {
            GS_ASSERT(component < Vector2T<T>::components);
            return *((&x) + component);
        }

        /**
        \brief Returns the specified vector component.
        \param[in] component Specifies the vector component index. This must be 0, or 1.
        */
        const T& operator [] (size_t component) const
        {
            GS_ASSERT(component < Vector2T<T>::components);
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
        Vector2T<T> Normalized() const
        {
            auto vec = *this;
            vec.Normalize();
            return vec;
        }

        /**
        Returns a type casted instance of this vector.
        \tparam C Specifies the static cast type.
        */
        template <typename C> Vector2T<C> Cast() const
        {
            return Vector2T<C>(
                static_cast<C>(x),
                static_cast<C>(y)
            );
        }

        T x, y;

};


/* --- Global Operators --- */

template <typename T> Vector2T<T> operator + (const Vector2T<T>& lhs, const Vector2T<T>& rhs)
{
    auto result = lhs;
    result += rhs;
    return result;
}

template <typename T> Vector2T<T> operator - (const Vector2T<T>& lhs, const Vector2T<T>& rhs)
{
    auto result = lhs;
    result -= rhs;
    return result;
}

template <typename T> Vector2T<T> operator * (const Vector2T<T>& lhs, const Vector2T<T>& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector2T<T> operator / (const Vector2T<T>& lhs, const Vector2T<T>& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector2T<T> operator * (const Vector2T<T>& lhs, const T& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T> Vector2T<T> operator * (const T& lhs, const Vector2T<T>& rhs)
{
    auto result = rhs;
    result *= lhs;
    return result;
}

template <typename T> Vector2T<T> operator / (const Vector2T<T>& lhs, const T& rhs)
{
    auto result = lhs;
    result /= rhs;
    return result;
}


/* --- Type Alias --- */

using Vector2 = Vector2T<Real>;
using Vector2f = Vector2T<float>;
using Vector2d = Vector2T<double>;
using Vector2i = Vector2T<int>;


} // /namespace Gs


#endif



// ================================================================================