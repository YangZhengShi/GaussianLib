/*
 * Inverse.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_INVERSE_H__
#define __GS_INVERSE_H__


#include "Details.h"
#include "Determinant.h"


namespace Gs
{


//! Computes the inverse of the specified matrix 'm'.
template <template <typename, std::size_t, std::size_t> class M, typename T, std::size_t Rows, std::size_t Cols>
bool Inverse(M<T, Rows, Cols>& inv, const M<T, Rows, Cols>& m)
{
    static_assert(Rows == Cols, "inverses can only be computed for squared matrices");
    //using Helper = Details::MatrixHelper<M, T, Rows, Cols>;
    //return Helper::OrderedInverse(inv, Helper::MatrixToArray(m), Rows);
    return false;//!!!
}

//! Computes the inverse of the specified 2x2 matrix 'm'.
template <template <typename, std::size_t, std::size_t> class M, typename T>
bool Inverse(M<T, 2, 2>& inv, const M<T, 2, 2>& m)
{
    /* Compute inverse determinant */
    T d = Determinant(m);

    if (d == T(0))
        return false;

    d = T(1) / d;

    /* Compute inverse matrix */
    inv(0, 0) = d * (  m(1, 1) );
    inv(0, 1) = d * ( -m(0, 1) );
    inv(1, 0) = d * ( -m(1, 0) );
    inv(1, 1) = d * (  m(0, 0) );

    return true;
}

//! Computes the inverse of the specified 3x3 matrix 'm'.
template <template <typename, std::size_t, std::size_t> class M, typename T>
bool Inverse(M<T, 3, 3>& inv, const M<T, 3, 3>& m)
{
    /* Compute inverse determinant */
    T d = Determinant(m);

    if (d == T(0))
        return false;

    d = T(1) / d;

    /* Compute inverse matrix */
    inv(0, 0) = d * ( m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2) );
    inv(1, 0) = d * ( m(2, 0) * m(1, 2) - m(1, 0) * m(2, 2) );
    inv(2, 0) = d * ( m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1) );
    inv(0, 1) = d * ( m(1, 1) * m(0, 2) - m(0, 1) * m(2, 2) );
    inv(1, 1) = d * ( m(0, 0) * m(2, 2) - m(2, 0) * m(0, 2) );
    inv(2, 1) = d * ( m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1) );
    inv(0, 2) = d * ( m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2) );
    inv(1, 2) = d * ( m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2) );
    inv(2, 2) = d * ( m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1) );

    return true;
}

//! Computes the inverse of the specified 4x4 matrix 'm'.
template <template <typename, std::size_t, std::size_t> class M, typename T>
bool Inverse(M<T, 4, 4>& inv, const M<T, 4, 4>& m)
{
    /* Compute inverse determinant */
    T d = Determinant(m);

    if (d == T(0))
        return false;

    d = T(1) / d;

    /* Compute inverse matrix */
    inv(0, 0) = d * ( m(1, 1) * (m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3)) + m(2, 1) * (m(3, 2) * m(1, 3) - m(1, 2) * m(3, 3)) + m(3, 1) * (m(1, 2) * m(2, 3) - m(2, 2) * m(1, 3)) );
    inv(1, 0) = d * ( m(1, 2) * (m(2, 0) * m(3, 3) - m(3, 0) * m(2, 3)) + m(2, 2) * (m(3, 0) * m(1, 3) - m(1, 0) * m(3, 3)) + m(3, 2) * (m(1, 0) * m(2, 3) - m(2, 0) * m(1, 3)) );
    inv(2, 0) = d * ( m(1, 3) * (m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1)) + m(2, 3) * (m(3, 0) * m(1, 1) - m(1, 0) * m(3, 1)) + m(3, 3) * (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) );
    inv(3, 0) = d * ( m(1, 0) * (m(3, 1) * m(2, 2) - m(2, 1) * m(3, 2)) + m(2, 0) * (m(1, 1) * m(3, 2) - m(3, 1) * m(1, 2)) + m(3, 0) * (m(2, 1) * m(1, 2) - m(1, 1) * m(2, 2)) );
    inv(0, 1) = d * ( m(2, 1) * (m(0, 2) * m(3, 3) - m(3, 2) * m(0, 3)) + m(3, 1) * (m(2, 2) * m(0, 3) - m(0, 2) * m(2, 3)) + m(0, 1) * (m(3, 2) * m(2, 3) - m(2, 2) * m(3, 3)) );
    inv(1, 1) = d * ( m(2, 2) * (m(0, 0) * m(3, 3) - m(3, 0) * m(0, 3)) + m(3, 2) * (m(2, 0) * m(0, 3) - m(0, 0) * m(2, 3)) + m(0, 2) * (m(3, 0) * m(2, 3) - m(2, 0) * m(3, 3)) );
    inv(2, 1) = d * ( m(2, 3) * (m(0, 0) * m(3, 1) - m(3, 0) * m(0, 1)) + m(3, 3) * (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) + m(0, 3) * (m(3, 0) * m(2, 1) - m(2, 0) * m(3, 1)) );
    inv(3, 1) = d * ( m(2, 0) * (m(3, 1) * m(0, 2) - m(0, 1) * m(3, 2)) + m(3, 0) * (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) + m(0, 0) * (m(2, 1) * m(3, 2) - m(3, 1) * m(2, 2)) );
    inv(0, 2) = d * ( m(3, 1) * (m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3)) + m(0, 1) * (m(1, 2) * m(3, 3) - m(3, 2) * m(1, 3)) + m(1, 1) * (m(3, 2) * m(0, 3) - m(0, 2) * m(3, 3)) );
    inv(1, 2) = d * ( m(3, 2) * (m(0, 0) * m(1, 3) - m(1, 0) * m(0, 3)) + m(0, 2) * (m(1, 0) * m(3, 3) - m(3, 0) * m(1, 3)) + m(1, 2) * (m(3, 0) * m(0, 3) - m(0, 0) * m(3, 3)) );
    inv(2, 2) = d * ( m(3, 3) * (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) + m(0, 3) * (m(1, 0) * m(3, 1) - m(3, 0) * m(1, 1)) + m(1, 3) * (m(3, 0) * m(0, 1) - m(0, 0) * m(3, 1)) );
    inv(3, 2) = d * ( m(3, 0) * (m(1, 1) * m(0, 2) - m(0, 1) * m(1, 2)) + m(0, 0) * (m(3, 1) * m(1, 2) - m(1, 1) * m(3, 2)) + m(1, 0) * (m(0, 1) * m(3, 2) - m(3, 1) * m(0, 2)) );
    inv(0, 3) = d * ( m(0, 1) * (m(2, 2) * m(1, 3) - m(1, 2) * m(2, 3)) + m(1, 1) * (m(0, 2) * m(2, 3) - m(2, 2) * m(0, 3)) + m(2, 1) * (m(1, 2) * m(0, 3) - m(0, 2) * m(1, 3)) );
    inv(1, 3) = d * ( m(0, 2) * (m(2, 0) * m(1, 3) - m(1, 0) * m(2, 3)) + m(1, 2) * (m(0, 0) * m(2, 3) - m(2, 0) * m(0, 3)) + m(2, 2) * (m(1, 0) * m(0, 3) - m(0, 0) * m(1, 3)) );
    inv(2, 3) = d * ( m(0, 3) * (m(2, 0) * m(1, 1) - m(1, 0) * m(2, 1)) + m(1, 3) * (m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) + m(2, 3) * (m(1, 0) * m(0, 1) - m(0, 0) * m(1, 1)) );
    inv(3, 3) = d * ( m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) + m(1, 0) * (m(2, 1) * m(0, 2) - m(0, 1) * m(2, 2)) + m(2, 0) * (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2)) );

    return true;
}

//! Computes the inverse of the specified sparse 4x4 matrix 'm'.
template <typename T> bool Inverse(SparseMatrix4T<T>& inv, const SparseMatrix4T<T>& m)
{
    /* Compute inverse determinant */
    T d = Determinant(m);

    if (d == T(0))
        return false;

    d = T(1) / d;

    /* Compute inverse matrix */
    inv(0, 0) = d * ( m(1, 1) * m(2, 2) + m(2, 1) * ( -m(1, 2) ) );
    inv(1, 0) = d * ( m(1, 2) * m(2, 0) + m(2, 2) * ( -m(1, 0) ) );
    inv(2, 0) = d * ( m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1) );
  /*inv(3, 0) = 0;*/
    inv(0, 1) = d * ( m(2, 1) * m(0, 2) + m(0, 1) * ( -m(2, 2) ) );
    inv(1, 1) = d * ( m(2, 2) * m(0, 0) + m(0, 2) * ( -m(2, 0) ) );
    inv(2, 1) = d * ( m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1) );
  /*inv(3, 1) = 0;*/
    inv(0, 2) = d * ( m(0, 1) * m(1, 2) + m(1, 1) * ( -m(0, 2) ) );
    inv(1, 2) = d * ( m(0, 2) * m(1, 0) + m(1, 2) * ( -m(0, 0) ) );
    inv(2, 2) = d * ( m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1) );
  /*inv(3, 2) = 0;*/
    inv(0, 3) = d * ( m(0, 1) * (m(2, 2) * m(1, 3) - m(1, 2) * m(2, 3)) + m(1, 1) * (m(0, 2) * m(2, 3) - m(2, 2) * m(0, 3)) + m(2, 1) * (m(1, 2) * m(0, 3) - m(0, 2) * m(1, 3)) );
    inv(1, 3) = d * ( m(0, 2) * (m(2, 0) * m(1, 3) - m(1, 0) * m(2, 3)) + m(1, 2) * (m(0, 0) * m(2, 3) - m(2, 0) * m(0, 3)) + m(2, 2) * (m(1, 0) * m(0, 3) - m(0, 0) * m(1, 3)) );
    inv(2, 3) = d * ( m(0, 3) * (m(2, 0) * m(1, 1) - m(1, 0) * m(2, 1)) + m(1, 3) * (m(0, 0) * m(2, 1) - m(2, 0) * m(0, 1)) + m(2, 3) * (m(1, 0) * m(0, 1) - m(0, 0) * m(1, 1)) );
  /*inv(3, 3) = 1;*/

    return true;
}


} // /namespace Gs


#endif



// ================================================================================