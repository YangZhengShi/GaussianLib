/*
 * Conversions.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_CONVERSIONS_H__
#define __GS_CONVERSIONS_H__


#include <cmath>


namespace Gs
{


/**
\brief Converts the matrix 'in' to the quaternion 'out'.
\tparam M Specifies the matrix type. This should be Matrix3, Matrix4 or SparseMatrix4.
\tparam Q Specifies the quaternion type. This should be Quaternion.
\tparam T Specifies the data type. This must be float or double.
\param[out] out Specifies the resulting quaternion.
\param[in] in Specifies the input matrix. This matrix must not be scaled!
*/
template <class M, template <typename> class Q, typename T>
void MatrixToQuaternion(Q<T>& out, const M& in)
{
    static_assert(
        M::rows >= 3 && M::columns >= 3,
        "matrix can only be converted to quaternion, if the matrix has at least 3 rows and 3 column"
    );

    /* Only get the trace of the 3x3 upper left matrix */
    const T trace = in(0, 0) + in(1, 1) + in(2, 2) + T(1);
    
    if (trace > T(0))
    {
        const T s = T(2) * std::sqrt(trace);
        out.x = (in(1, 2) - in(2, 1)) / s;
        out.y = (in(2, 0) - in(0, 2)) / s;
        out.z = (in(0, 1) - in(1, 0)) / s;
        out.w = T(0.25) * s;
    }
    else
    {
        if (in(0, 0) > in(1, 1) && in(0, 0) > in(2, 2))
        {
            const T s = T(2) * std::sqrt(T(1) + in(0, 0) - in(1, 1) - in(2, 2));
            out.x = T(0.25) * s;
            out.y = (in(1, 0) + in(0, 1) ) / s;
            out.z = (in(0, 2) + in(2, 0) ) / s;
            out.w = (in(1, 2) - in(2, 1) ) / s;
        }
        else if (in(1, 1) > in(2, 2))
        {
            const T s = T(2) * std::sqrt(T(1) + in(1, 1) - in(0, 0) - in(2, 2));
            out.x = (in(1, 0) + in(0, 1) ) / s;
            out.y = T(0.25) * s;
            out.z = (in(2, 1) + in(1, 2) ) / s;
            out.w = (in(2, 0) - in(0, 2) ) / s;
        }
        else
        {
            const T s = T(2) * std::sqrt(T(1) + in(2, 2) - in(0, 0) - in(1, 1));
            out.x = (in(2, 0) + in(0, 2) ) / s;
            out.y = (in(2, 1) + in(1, 2) ) / s;
            out.z = T(0.25) * s;
            out.w = (in(0, 1) - in(1, 0) ) / s;
        }
    }

    Normalize(out);
}

template <class M, template <typename> class Q, typename T>
void QuaternionToMatrix(M& out, const Q<T>& in)
{
    static_assert(
        M::rows >= 3 && M::columns >= 3,
        "quaternion can only be converted to matrix, if the matrix has at least 3 rows and 3 column"
    );

    const auto& x = in.x;
    const auto& y = in.y;
    const auto& z = in.z;
    const auto& w = in.w;

    out(0, 0) = T(1) - T(2)*y*y - T(2)*z*z;
    out(0, 1) =        T(2)*x*y + T(2)*z*w;
    out(0, 2) =        T(2)*x*z - T(2)*y*w;

    out(1, 0) =        T(2)*x*y - T(2)*z*w;
    out(1, 1) = T(1) - T(2)*x*x - T(2)*z*z;
    out(1, 2) =        T(2)*z*y + T(2)*x*w;

    out(2, 0) =        T(2)*x*z + T(2)*y*w;
    out(2, 1) =        T(2)*z*y - T(2)*x*w;
    out(2, 2) = T(1) - T(2)*x*x - T(2)*y*y;
}

template <class M, template <typename> class Q, typename T>
void QuaternionToMatrixTransposed(M& out, const Q<T>& in)
{
    static_assert(
        M::rows >= 3 && M::columns >= 3,
        "quaternion can only be converted to matrix, if the matrix has at least 3 rows and 3 column"
    );

    const auto& x = in.x;
    const auto& y = in.y;
    const auto& z = in.z;
    const auto& w = in.w;

    out(0, 0) = T(1) - T(2)*y*y - T(2)*z*z;
    out(0, 1) =        T(2)*x*y - T(2)*z*w;
    out(0, 2) =        T(2)*x*z + T(2)*y*w;

    out(1, 0) =        T(2)*x*y + T(2)*z*w;
    out(1, 1) = T(1) - T(2)*x*x - T(2)*z*z;
    out(1, 2) =        T(2)*z*y - T(2)*x*w;

    out(2, 0) =        T(2)*x*z - T(2)*y*w;
    out(2, 1) =        T(2)*z*y + T(2)*x*w;
    out(2, 2) = T(1) - T(2)*x*x - T(2)*y*y;
}


} // /namespace Gs


#endif



// ================================================================================
