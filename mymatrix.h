/*mymatrix.h*/

// 
// << Tyler J. Pearson >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // default value for type T:
      }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C)
  {
    if (R < 1){
      throw invalid_argument("mymatrix::constructor: # of rows");
    }
    if (C < 1) {
      throw invalid_argument("mymatrix::constructor: # of cols");
    }
    
    this->Rows = new ROW[R];
    this->NumRows = R;
    
    
    for (int r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[C];
        Rows[r].NumCols = C;
        
        for (int c = 0; c < Rows[r].NumCols; ++c) {
            Rows[r].Cols[c] = T{};
        }
    }

    //
    // TODO
    //
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
    this->Rows = new ROW[other.numrows()];
    this->NumRows = other.numrows(); 
    
    for (int r = 0; r < NumRows; ++r) {
        this->Rows[r].Cols = new T[other.Rows[r].NumCols];
        this->Rows[r].NumCols = other.Rows[r].NumCols;
        
        for (int c = 0; c < Rows[r].NumCols; ++c) {
            this->Rows[r].Cols[c] = T{};
            this->Rows[r].Cols[c] = other.Rows[r].Cols[c];
        }
    }
  }


  //
  // numrows
  //
  // Returns the # of rows in the matrix.  The indices for these rows
  // are 0..numrows-1.
  //
  int numrows() const
  {
    return this->NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows) {
      throw invalid_argument("mymatrix::numcols: row");
    }
    return this->Rows[r].NumCols;
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)//row out of bounds
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)//number to grow row by is less than one
      throw invalid_argument("mymatrix::growcols: columns");
    
    auto oldNumCols = Rows[r].NumCols;
    
    if (C < Rows[r].NumCols) {//C is less than the current # of columns, and we dont shrink columns, so we just have it be the same size as it was before
        C = Rows[r].NumCols;
    } else {
        Rows[r].NumCols = C;
    }
    
    T* newRow = new T[C];
    
    for (int i = 0; i < Rows[r].NumCols; ++i) {
        newRow[i] = T{};
        if (i < oldNumCols) {
            newRow[i] = Rows[r].Cols[i];
        }
        
        
    }
    
    delete[] Rows[r].Cols;
    Rows[r].Cols = newRow;
    Rows[r].NumCols = C;
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1) {
      throw invalid_argument("mymatrix::grow: # of rows");
    }
    if (C < 1) {
      throw invalid_argument("mymatrix::grow: # of cols");
    }
    //Verifies the row number and adds new rows when necessary
    
    int rowsize = 0;
    if (R <= numrows()) {//We cant shrink anything in terms of rows, so we will just keep it as is to prevent data loss
        R = this->NumRows;
    } else if (R > numrows()) {
        if (R < this->NumRows) {
            rowsize = this->NumRows;
        } else {
            rowsize = R;
        }
        //allocate a new row
        ROW* rowptr = new ROW[rowsize];
        
        //for each row, allocate memory for a new column 
        for (int i = 0; i < this->NumRows; ++i) {
            if (C <= Rows[i].NumCols) {
                rowptr[i].Cols = new T[Rows[i].NumCols];
                rowptr[i].NumCols = Rows[i].NumCols;
            } else {
                rowptr[i].Cols = new T[C];
                rowptr[i].NumCols = C;
            }
        }
        
        //add extra as needed
        for (int i = this->NumRows; i < rowsize; ++i) {
              rowptr[i].Cols = new T[C];
              rowptr[i].NumCols = C; 
        }
        
        //initialize new array 
        for (int i = 0; i < rowsize; ++i){
            for (int j = 0; j < rowptr[i].NumCols; ++j) {
                rowptr[i].Cols[j] = T{};
            }
        }
        
        //copied elements from old array to new array 
        for (int i = 0; i < this->NumRows; ++i) {
            for (int j = 0; j < this->Rows[i].NumCols; ++j) {
                rowptr[i].Cols[j] = this->Rows[i].Cols[j];
            }
        }
        
        delete[] Rows;
        this->Rows = rowptr;
        this->NumRows = rowsize;
    }
  }


  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const
  {
    int size = 0;
    for (int i = 0; i < NumRows; ++i) {
        for (int j = 0; j < Rows[i].NumCols; ++j) {
              size++;
        }
    }
  
    return size;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows) {
        throw invalid_argument("mymatrix::at: row");
    } 
    if (c < 0 || c >= Rows[r].NumCols) {
        throw invalid_argument("mymatrix::at: col");
    }
      

    //
    // TODO
    //
    return Rows[r].Cols[c];
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows) {
        throw invalid_argument("mymatrix::(): row");
    }
    if (c < 0 || c >= Rows[r].NumCols) {
        throw invalid_argument("mymatrix::(): col");
    }
      
    //
    // TODO
    //
    return Rows[r].Cols[c];
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result = *this;
    
    for (int i = 0; i < NumRows; ++i) {
        for (int j = 0; j < this->Rows[i].NumCols; ++j) {
            result.Rows[i].Cols[j] = this->Rows[i].Cols[j] * scalar;
        }
    }
    
    //
    // TODO
    //

    return result;
  }


  //
  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    //mymatrix<T> result = *this;

    //
    // both matrices must be rectangular for this to work:
    //
    
    //
    // TODO
    
    int cols_temp = other.Rows[0].NumCols;
    int rows_temp = numrows();
    
    int numcolumns = this->Rows[0].NumCols;
    
    mymatrix<T> result(rows_temp, cols_temp);
    int checker = numcols(0);
    int otherchecker = other.numcols(0);
    
    for (int i = 0; i < numrows(); ++i) {
       if (checker != numcols(i)) {
           throw runtime_error("mymatrix::*: this not rectangular");
       }
    }
    for (int i = 0; i < other.numrows(); ++i) {
       if (otherchecker != other.numcols(i)) {
           throw runtime_error("mymatrix::*: other not recatangular");
       }
    }

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    //
    // TODO
    //
    //
    if (numcols(0) != other.numrows()) {
       throw runtime_error("mymatrix::*: size mismatch");
    }
      
    //
    // Okay, we can multiply:
    //

    //
    // TODO
    //
    
    for (int r = 0; r < this->numrows(); ++r) {
        for (int c = 0; c < cols_temp; ++c) {
            for (int i = 0; i < numcolumns; ++i) {
                result.Rows[r].Cols[c] += this->Rows[r].Cols[i] * other.Rows[i].Cols[c];
            }
            
        }
    
    }

    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};
