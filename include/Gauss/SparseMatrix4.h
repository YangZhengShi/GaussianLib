/*
 * SparseMatrix4.h
 * 
 * This file is part of the "GaussianLib" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __GS_SPARSE_MATRIX4_H__
#define __GS_SPARSE_MATRIX4_H__


#include "Real.h"
#include "Assert.h"
#include "Macros.h"
#include "Matrix.h"

#include <cmath>
#include <cstring>
#include <algorithm>


namespace Gs
{


#ifdef GS_MATRIX_COLUMN_MAJOR
#   define __GS_FOREACH_ROW_COL__(r, c)                                     \
        for (std::size_t r = 0; r < SparseMatrix4T<T>::rowsSparse; ++r)      \
        for (std::size_t c = 0; c < SparseMatrix4T<T>::columnsSparse; ++c)
#else
#   define __GS_FOREACH_ROW_COL__(r, c)                                     \
        for (std::size_t c = 0; c < SparseMatrix4T<T>::columnsSparse; ++c)   \
        for (std::size_t r = 0; r < SparseMatrix4T<T>::rowsSparse; ++r)
#endif

/**
\brief This is a 'sparse' 4x4 matrix, i.e. it only stores
a 3x4 matrix where the 4th row is always implicitly (0, 0, 0, 1).
\tparam T Specifies the data type of the matrix components.
This should be a primitive data type such as float, double, int etc.
\remarks The macro GS_MATRIX_COLUMN_MAJOR can be defined, to use column-major matrices.
By default row-major matrices are used.
*/
template <typename T> class SparseMatrix4T
{
    
    public:
        
        static const std::size_t rows           = 4;
        static const std::size_t columns        = 4;
        static const std::size_t elements       = SparseMatrix4T<T>::rows*SparseMatrix4T<T>::columns;

        static const std::size_t rowsSparse     = 3;
        static const std::size_t columnsSparse  = 4;
        static const std::size_t elementsSparse = SparseMatrix4T<T>::rowsSparse*SparseMatrix4T<T>::columnsSparse;

        using ThisType = SparseMatrix4T<T>;

        //! Transposed matrix type, i.e. SparseMatrix4T<T> becomes Matrix<T, 4, 4>.
        using TransposedType = Matrix<T, 4, 4>;

        class Initializer
        {
            
            public:
                
                Initializer(ThisType& matrix) :
                    matrix_ ( matrix ),
                    element_( 0      )
                {
                }

                Initializer& operator , (const T& nextValue)
                {
                    matrix_(element_ / Cols, element_ % Cols) = nextValue;
                    ++element_;
                    return *this;
                }

            private:

                ThisType&   matrix_;
                std::size_t element_;

        };

        SparseMatrix4T()
        {
            Reset();
        }

        SparseMatrix4T(const ThisType& rhs)
        {
            *this = rhs;
        }

        /**
        \brief Returns a reference to the element at the specified entry.
        \param[in] row Specifies the row index. This must be in the range [0, 2].
        The 4th row (index 3) is not allowed, since this is a sparaw matrix, where the 4th row is always implicitly (0, 0, 0, 1).
        \param[in] col Specifies the column index. This must be in the range [0, 3].
        */
        T& operator () (std::size_t row, std::size_t col)
        {
            GS_ASSERT(row < SparseMatrix4T<T>::rowsSparse);
            GS_ASSERT(col < SparseMatrix4T<T>::columnsSparse);
            #ifdef GS_MATRIX_COLUMN_MAJOR
            return m_[col*Rows + row];
            #else
            return m_[row*Cols + col];
            #endif
        }

        /**
        \brief Returns a constant reference to the element at the specified entry.
        \param[in] row Specifies the row index. This must be in the range [0, 2].
        The 4th row (index 3) is not allowed, since this is a sparaw matrix, where the 4th row is always implicitly (0, 0, 0, 1).
        \param[in] col Specifies the column index. This must be in the range [0, 3].
        */
        const T& operator () (std::size_t row, std::size_t col) const
        {
            GS_ASSERT(row < SparseMatrix4T<T>::rowsSparse);
            GS_ASSERT(col < SparseMatrix4T<T>::columnsSparse);
            #ifdef GS_MATRIX_COLUMN_MAJOR
            return m_[col*Rows + row];
            #else
            return m_[row*Cols + col];
            #endif
        }

        T& operator [] (std::size_t element)
        {
            GS_ASSERT(element < SparseMatrix4T<T>::elementsSparse);
            return m_[element];
        }

        const T& operator [] (std::size_t element) const
        {
            GS_ASSERT(element < SparseMatrix4T<T>::elementsSparse);
            return m_[element];
        }

        ThisType operator *= (const ThisType& rhs)
        {
            *this = (*this * rhs);
            return *this;
        }

        ThisType& operator = (const ThisType& rhs)
        {
            for (std::size_t i = 0; i < SparseMatrix4T<T>::elementsSparse; ++i)
                m_[i] = rhs.m_[i];
            return *this;
        }

        void Reset()
        {
            for (std::size_t i = 0; i < SparseMatrix4T<T>::elementsSparse; ++i)
                m_[i] = T(0);
        }

        void LoadIdentity()
        {
            __GS_FOREACH_ROW_COL__(r, c)
            {
                (*this)(r, c) = (r == c ? T(1) : T(0));
            }
        }

        static ThisType Identity()
        {
            ThisType result;
            result.LoadIdentity();
            return result;
        }

        TransposedType Transposed() const
        {
            TransposedType result;

            __GS_FOREACH_ROW_COL__(r, c)
            {
                result(c, r) = (*this)(r, c);
            }

            for (std::size_t i = 0; i < SparseMatrix4T<T>::columnsSparse; ++i)
                result(i, SparseMatrix4T<T>::rowsSparse);

            return result;
        }

        //! Returns a pointer to the first element of this matrix.
        T* Ptr()
        {
            return &(m_[0]);
        }

        //! Returns a constant pointer to the first element of this matrix.
        const T* Ptr() const
        {
            return &(m_[0]);
        }

    private:
        
        T m_[SparseMatrix4T<T>::elementsSparse];

};

#undef __GS_FOREACH_ROW_COL__


/* --- Global Operators --- */

/*template <typename T, std::size_t Rows, std::size_t ColsRows, std::size_t Cols>
Matrix<T, Rows, Cols> operator * (const Matrix<T, Rows, ColsRows>& lhs, const Matrix<T, ColsRows, Cols>& rhs)
{
    Matrix<T, Rows, Cols> result;

    for (std::size_t r = 0; r < Rows; ++r)
    {
        for (std::size_t c = 0; c < Cols; ++c)
        {
            result(r, c) = T(0);
            for (std::size_t i = 0; i < ColsRows; ++i)
                result(r, c) += lhs(r, i)*rhs(i, c);
        }
    }

    return result;
}

template <typename T, typename I, std::size_t Rows, std::size_t Cols>
typename Matrix<T, Rows, Cols>::Initializer operator << (Matrix<T, Rows, Cols>& matrix, const I& firstValue)
{
    typename Matrix<T, Rows, Cols>::Initializer initializer(matrix);
    initializer , static_cast<T>(firstValue);
    return initializer;
}*/


/* --- Type Alias --- */

using SparseMatrix4 = SparseMatrix4T<Real>;
using SparseMatrix4f = SparseMatrix4T<float>;
using SparseMatrix4d = SparseMatrix4T<double>;
using SparseMatrix4i = SparseMatrix4T<int>;


} // /namespace Gs


#endif



// ================================================================================