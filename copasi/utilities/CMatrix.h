#include <iostream>

#ifndef COPASI_CMatrix
#define COPASI_CMatrix

using std::ostream;
using std::endl;

/**
 * Template class CMatrix < class CType >
 * This template class is a simple matrix class  allowing standard
 * C-style and fortran style access to the elements. It also supplies 
 * an ostream operator.
 */
template <class CType>
class CMatrix
  {
  public:
    typedef CType elementType;

    // Attributes
  private:
    /**
     * Number of rows in the matrix.
     */
    unsigned C_INT32 mRows;

    /**
     * Number of columns in the matrix
     */
    unsigned C_INT32 mCols;

    /**
     * The array storing the matrix elements
     */
    CType * mArray;

    // Operations
  public:
    /**
     * Default constructor
     * @param unsigned C_INT32 rows (default = 0)
     * @param unsigned C_INT32 cols (default = 0)
     */
    CMatrix(unsigned C_INT32 rows = 0, unsigned C_INT32 cols = 0) :
        mRows(rows),
        mCols(cols),
        mArray(NULL)
    {
      if (mRows && mCols)
        mArray = new CType[mRows * mCols];
    }

    /**
     * Copy constructor
     * @param const CMatrix <CType> & src
     */
    CMatrix(const CMatrix <CType> & src):
        mRows(src.mRows),
        mCols(src.mCols),
        mArray(NULL)
    {
      if (mRows && mCols)
        {
          mArray = new CType[mRows * mCols];
          memcpy(mArray, src.mArray, mRows * mCols * sizeof(CType));
        }
    }

    /**
     * Destructor.
     */
    ~CMatrix()
    {
      if (mArray)
        delete [] mArray;
    }

    /**
     * The number of elements stored in the matrix.
     * @return unsigned C_INT32 size
     */
  unsigned C_INT32 size() const {return mRows * mCols;}

    /**
     * The number of rows of the matrix.
     * @return unsigned C_INT32 rows
     */
    unsigned C_INT32 numRows() const {return mRows;}

    /**
     * The number of columns of the matrix
     * @return unsigned C_INT32 cols
     */
    unsigned C_INT32 numCols() const {return mCols;}

    /**
     * Resize the matrix. The previous content is lost
     * @param unsigned C_INT32 rows
     * @param unsigned C_INT32 cols
     */
    void resize(unsigned C_INT32 rows, unsigned C_INT32 cols)
    {
      if (mArray)
        {
          delete [] mArray;
          mArray = NULL;
        }

      mRows = rows;
      mCols = cols;

      if (mRows && mCols)
        mArray = new CType[mRows * mCols];
    }

    /**
     * Assignement operator
     * @param const CMatrix <CType> & rhs
     * @return CMatrix <CType> & lhs
     */
    CMatrix <CType> & operator = (const CMatrix <CType> & rhs)
    {
      if (mRows != rhs.mRows || mCols != rhs.mCols)
        resize(rhs.mRows, rhs.mCols);

      memcpy(mArray, rhs.mArray, mRows * mCols * sizeof(CType));

      return *this;
    }

    /**
     * Retrieve a row of the matrix using c-style indexing
     * @param unsigned C_INT32 row
     * @return CType * row
     */
    inline CType * operator[](unsigned C_INT32 row)
  {return mArray + row * mCols;}

    /**
     * Retrieve a row of the matrix using c-style indexing
     * @param unsigned C_INT32 row
     * @return const CType * row
     */
    inline const CType * operator[](unsigned C_INT32 row) const
      {return mArray + row * mCols;}

    /**
     * Retrieve a matrix element using c-style indexing.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return const elementType & element
     */
    inline elementType & operator()(const unsigned C_INT32 & row,
                                    const unsigned C_INT32 & col)
    {return *(mArray + row * mCols + col);}

    /**
     * Retrieve a matrix element using c-style indexing.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return const elementType & element
     */
    inline const elementType & operator()(const unsigned C_INT32 & row,
                                          const unsigned C_INT32 & col) const
      {return *(mArray + row * mCols + col);}

    /**
     * Retrieve the array of the matrix elements. This is suitable
     * for interfacing with clapack routines.
     * @return CType * array
     */
    CType * array() {return mArray;}

    /**
     * Retrieve the array of the matrix elements. This is suitable
     * for interfacing with clapack routines.
     * @return const CType * array
     */
    const CType * array() const {return mArray;}

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CMatrix< CType > & A
     * @retrun ostream & os
     */
    friend ostream &operator<<(ostream &os, const CMatrix< CType > & A)
    {
      os << "Matrix(" << A.mRows << "x" << A.mCols << ")" << endl;

      unsigned C_INT32 i, j;
      CType * tmp = A.mArray;

      for (i = 0; i < A.mRows; i++)
        {
          for (j = 0; j < A.mCols; j++)
            cout << "  " << * (tmp++);
          cout << endl;
        }
      return os;
    }
  };

/**
 * This creates an instantiation of 
 * the ostream operator << for CMatrix <C_FLOAT64>
 */
class CMatrixDbl : public CMatrix <C_FLOAT64> {};

/**
 * This creates an instantiation of 
 * the ostream operator << for CMatrix <C_INT32>
 */
class CMatrixInt : public CMatrix <C_INT32> {};

template <class Matrix>
class CFortranAccess
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    Matrix & mA;

  public:
    CFortranAccess(Matrix & A):
        mA(A)
    {}

    ~CFortranAccess() {}

    /**
     * Retrieve a row of the matrix using Fortran style indexing.
     * @param unsigned C_INT32 row
     * @return elementType * row
     */
    inline elementType * operator[](unsigned C_INT32 row)
    {return mA[row - 1] - 1;}

    /**
     * Retrieve a row of the matrix using Fortran style indexing.
     * @param unsigned C_INT32 row
     * @return const elementType * row
     */
    inline const elementType * operator[](unsigned C_INT32 row) const
      {return mA[row - 1] - 1;}

    /**
     * Retrieve a matrix element using Fortran style indexing.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return const elementType & element
     */
    inline elementType & operator()(const unsigned C_INT32 & row,
                                    const unsigned C_INT32 & col)
    {return mA(row - 1, col - 1);}

    /**
     * Retrieve a matrix element using Fortran style indexing.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return const elementType & element
     */
    inline const elementType & operator()(const unsigned C_INT32 & row,
                                          const unsigned C_INT32 & col) const
      {return mA(row - 1, col - 1);}
  };

template <class Matrix>
class CUpperTriangularView
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    const Matrix & mA;
    elementType mZero;

  public:
    CUpperTriangularView(const Matrix & A, const elementType zero):
        mA(A),
        mZero(zero)
    {}

    ~CUpperTriangularView() {}

    /**
     * Retrieve a matrix element using the indexing style of the matrix.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return elementType element
     */
    inline elementType operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col) const
      {
        if (row < col)
          return mA(row, col);
        else
          return mZero;
      }
  };

template <class Matrix>
class CLowerTriangularView
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    const Matrix & mA;
    elementType mZero;

  public:
    CLowerTriangularView(const Matrix & A, const elementType zero):
        mA(A),
        mZero(zero)
    {}

    ~CLowerTriangularView() {}

    /**
     * Retrieve a matrix element using the indexing style of the matrix.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return elementType element
     */
    inline elementType operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col) const
      {
        if (row > col)
          return mA(row, col);
        else
          return mZero;
      }
  };

template <class Matrix>
class CUnitUpperTriangularView
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    const Matrix & mA;
    elementType mZero;
    elementType mUnit;

  public:
    CUnitUpperTriangularView(const Matrix & A,
                             const elementType zero,
                             const elementType unit):
        mA(A),
        mZero(zero),
        mUnit(unit)
    {}

    ~CUnitUpperTriangularView() {}

    /**
     * Retrieve a matrix element  using the indexing style of the matrix.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return elementType element
     */
    inline elementType operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col) const
      {
        if (row < col)
          return mA(row, col);
        else if (row > col)
          return mZero;
        else
          return mUnit;
      }
  };

template <class Matrix>
class CUnitLowerTriangularView
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    const Matrix & mA;
    elementType mZero;
    elementType mUnit;

  public:
    CUnitLowerTriangularView(const Matrix & A,
                             const elementType zero,
                             const elementType unit):
        mA(A),
        mZero(zero),
        mUnit(unit)
    {}

    ~CUnitLowerTriangularView() {}

    /**
     * Retrieve a matrix element using the indexing style of the matrix.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return elementType element
     */
    inline elementType operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col) const
      {
        if (row > col)
          return mA(row, col);
        else if (row < col)
          return mZero;
        else
          return mUnit;
      }
  };

template <class Matrix>
class CTransposeView
  {
  public:
    typedef typename Matrix::elementType elementType;

  private:
    const Matrix & mA;

  public:
    CTransposeView(const Matrix & A): mA(A) {}

    ~CTransposeView() {}

    /**
     * Retrieve a matrix element using the indexing style of the matrix.
     * @param const unsigned C_INT32 & row
     * @param const unsigned C_INT32 & col
     * @return elementType element
     */
    inline elementType operator()(const unsigned C_INT32 & row,
                                  const unsigned C_INT32 & col) const
      {return mA(col, row);}
  };
#endif // COPASI_CMatrix
