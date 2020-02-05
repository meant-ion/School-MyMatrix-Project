#include <iostream>
#include <string>
#include "mymatrix.h"

//adds data to the matrix when called by a very complex algorithm that no one but me can figure out how it works
void FillMatrix(mymatrix<int>& MFiller) {
   for (int r = 0; r < MFiller.numrows(); ++r) {
        for (int c = 0; c < MFiller.numcols(r); ++c) {
            MFiller(r,c) = (r * 1) + ((c * 1) + 1);
        }
    }
}

//Shows that copy constructor works
void MatrixCopy(mymatrix<int> MCopy) {
    cout << "Displaying Copy" << endl;
    MCopy._output();
    cout << "Adding values to copy" << endl;
    MCopy(2,2) = 4;
    MCopy(0,3) = -6;
    cout << "Redisplaying copy" << endl;
    MCopy._output();
}
void CopyConstructorDemo() {
    cout << "Creating matrix of type int and its copy" << endl;
    mymatrix<int> M8(4,4);
    cout << "Displaying original" << endl;
    M8._output();
    MatrixCopy(M8);
    cout << "Adding value to original " << endl;
    M8(2,3) = 66;
    M8(0,0) = 69;
    cout << "Redisplaying original" << endl;
    M8._output();
}

void Make4AndDelete4() {
    cout << "Creating deault Matrix of type int:" << endl;
    mymatrix<int>* M1 = new mymatrix<int>;
    
    cout << "Creating default matrix of type float:" << endl;
    mymatrix<float>* M2 = new mymatrix<float>;
    
    cout << "Creating default matrix of type double:" << endl;
    mymatrix<double>* M3 = new mymatrix<double>;
    
    cout << "Creating default matrix of type long:" << endl;
    mymatrix<long>* M4 = new mymatrix<long>;
    
    cout << "Displaying default int matrix:" << endl;
    M1->_output();
    
    cout << "Displaying default float matrix:" << endl;
    M2->_output();
    
    cout << "Displaying default double matrix:" << endl;
    M3->_output();
    
    cout << "Displaying default long matrix:" << endl;
    M4->_output();
    
    cout << "Deleting created matricies" << endl;
    delete M1;
    delete M2;
    delete M3;
    delete M4;
}

void MessingWithMatrix5() {
    cout << "Creating matrix of type int of size 6, 4" << endl;
    mymatrix<int> M5(6,4);
    //Parameterized constructors gone wrong, uncomment to see that throw works
    //mymatrix<int>* M6 = new mymatrix<int>(-1,6);
    
    //Same as above, but with columns
    //mymatrix<int>* M7 = new mymatrix<int>(4, -1);
    
    //Messing with specific elements within Matrix 5
    cout << "Displaying parameterized int matrix" << endl;
    M5._output();
    
    cout << "Adding values to (1,1), (5,3), (4,2)" << endl;
    cout << "to 1,1" << endl;
    M5(1,1) = 4;
    cout << "to 5,3" << endl;
    M5(5,3) = 3;
    cout << "to 4,2" << endl;
    M5(4,2) = 8;
    
    //attempts to add a value outside the bounds of the program, will throw if uncommented
    //M5(6,6) = 33;
    
    M5._output();
    
    //stats for uber nerds
    cout << "Number of columns in row 1 of Matrix 5: " << M5.numcols(0) << endl;
    cout << "Number of rows in Matrix 5: " << M5.numrows() << endl;
    cout << "Value of element in (1,1): " << M5.at(1,1) << endl;
    cout << "Size of Matrix 5: " << M5.size() << endl;
}

//grows one row of a matrix and then resizes it to be square again
void GrowingRowsAndMatrix() {
     cout << "Creating matrix to be grown: " << endl;
     mymatrix<int>* growMatrix = new mymatrix<int>;
    
     cout << "Displaying matrix before growing: " << endl;
     growMatrix->_output();
    
     cout << "Growing row 1 of the matrix to 6:" << endl;
     growMatrix->growcols(0, 6);
    
     cout << "Displaying grown jagged matrix: " << endl;
     growMatrix->_output();
    
     cout << "Growing whole matrix to be (6,6): " << endl;
     growMatrix->grow(6,6);
    
     cout << "Displaying grown matrix: " << endl;
     growMatrix->_output();
    
     delete growMatrix;
}

//multiplies a matrix by a scalar value
void ScalarMultiplication() {
    cout << "Creating two default matricies of type int:" << endl;
    mymatrix<int> M9;
    mymatrix<int> M10;
    
    cout << "Adding values to one matrix:" << endl;
    FillMatrix(M9);
    
    cout << "Making second matrix equal to the first times scalar value: " << endl;
    M10 = M9 * 3;
    
    cout << "Displaying first matrix (unchanged from scalar multiplication:)" << endl;
    M9._output();
    cout << "Displaying second matrix: " << endl;
    M10._output();
}



//Multiplies one matrix to another and puts that product into another matrix
void MatrixMultiplication() {
    cout << "Creating three matricies for matrix multiplication: " << endl;
    mymatrix<int> M11(6,4);
    mymatrix<int> M12(4,6);
    mymatrix<int> M13;
    
    cout << "Adding values to first two matricies created: " << endl;
    FillMatrix(M11);
    FillMatrix(M12);
    
    cout << "Displaying first created matrix: " << endl;
    M11._output();
    
    cout << "Displaying second created matrix: " << endl;
    M12._output();
    
    cout << "Multiplying first matrix by second: " << endl;
    M13 = M11 * M12;
    
    cout << "Displaying new matrix created from matrix multiplication: " << endl;
    M13._output();
}

//pauses the demo to allow the user to look at the results and then moves it back to the mainline
void MoveDemoAlong(char userInput) {//no & because it isnt important what the user puts in as command
    cout << "Press any key and then enter to continue with the demo: ";
    cin >> userInput;
    cout << endl;
}

int main() {
    char input = 'c';//to make it so that it doesnt all come out at once
    //default constructor call(int, float, double, long) while also deleting them to get rid of memory issues
    Make4AndDelete4();
    MoveDemoAlong(input);
    
    
    //Parameterized constructor and putting some things into the matrix, first element in matrix has index (0,0)
    MessingWithMatrix5();
    MoveDemoAlong(input);
    
    //Copy constructor for matrix of type int, and also stuffing values into it to ensure that it copied correctly
    CopyConstructorDemo();
    MoveDemoAlong(input);
    
    //Growing a row within a matrix and then growing the whole matrix
    GrowingRowsAndMatrix();
    MoveDemoAlong(input);
    
    //Demonstrating that scalar multiplication works as intended
    ScalarMultiplication();
    MoveDemoAlong(input);
    
    //Demonstrating that matrix multiplication works
    MatrixMultiplication();
    MoveDemoAlong(input);
    

    return 0;
}