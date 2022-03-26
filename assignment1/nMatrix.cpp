#include "nMatrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

//Task: 	constructor with size
//Input:    int k     - the new size
//Output:   Diag this - default matrix
//Activity: creates the array of the diagonal of size k
Matrix::Matrix(int k)
{
    if (k < 0) throw INVALID;
    _v.clear();
    vector<int> _tmp ;
    _tmp.resize(k,0);
    _v.resize(k, _tmp);

}

//Task: 	constructor the elements of the diagonal
//Input:    vector<int> v     - the new diagonal
//Output:   Diag this         - default matrix
//Activity: creates the array of the diagonal and fills in its elements based on vector v
Matrix::Matrix(const vector<vector<int>> &v)
{
    _v = v;
}

//Task: 	copy constructor
//Input:    Diag a    - matrix
//Output:   Diag this - default matrix
//Activity: creates the array of the diagonal and fills in its elements based on matrix a
Matrix::Matrix(const Matrix& a)
{
    int s = a.getSize();
    _v.resize(s);
    for(int i = 0; i < s; ++i) _v[i] = a._v[i];
}

//Task: 	assignment operator
//Input:    Diag a    - matrix
//Output:   Diag this - default matrix
//Activity: fills in the elements of the diagonal based on matrix a
Matrix& Matrix::operator=(const Matrix& a)
{
    int s = a.getSize();
    reSize(s);
    for(int i = 0; i < s; ++i) _v[i] = a._v[i];
    return *this;
}

//Task: 	resizing a matrix
//Input:    int k     - the new size
//Output:   Diag this - default matrix
//Activity: resizes the matrix to k
void Matrix::reSize(int k)
{
    if(k < 0) throw INVALID;
    std::vector<int> _tmp ;
    _tmp.resize(k,0);
    _v.resize(k, _tmp);
}

//Task: 	adding
//Input:    Diag a    - matrix
//          Diag b    - matrix
//Output:   Diag      - result matrix
//Activity: adds the elements of the diagonals of the matrices
Matrix operator+(const Matrix& a ,const Matrix& b)
{
    int s = a.getSize();
    if(s != b.getSize()) throw Matrix::DIFFERENT;

    Matrix c(s);

    for(int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j)
            c._v[i][j] = a._v[i][j] + b._v[i][j];

    return c;
}

//Task: 	multiplying
//Input:    Diag a    - matrix
//          Diag b    - matrix
//Output:   Diag      - result matrix
//Activity: multiplies the elements of the diagonals of the matrices
Matrix operator*(const Matrix& a ,const Matrix& b)
{
    int s = a.getSize();
    if(s != b.getSize()) throw Matrix::DIFFERENT;

    Matrix c(s);

    for(int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j)
            for (int k = 0; k < s ; ++k) {
                c._v[i][j] += a._v[i][k] * b._v[k][j];
            }


    return c;
}

//Task: 	writing
//Input:    ostream os - target of writing
//          Diag a     - matrix
//Output:   ostream os - target of writing
//Activity: writes the elements of the matrix
ostream& operator<<(ostream& os, const Matrix& a)
{
    int s = a.getSize();
    for(int i = 0; i < s; ++i){
        for(int j = 0; j < s; ++j)
            os << setw(5) << a(i,j);
        os << endl;
    }
    return os;
}

//Task: 	reading
//Input:    istream is - source of writing
//          Diag a     - matrix
//Output:   istream is - source of writing
//Activity: reads the elements of the diagonal of the matrix
istream& operator>>(istream& is, Matrix& a)
{
    int s;
    is >> s;
    a.reSize(s);
    for(int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            if ((i == j) || (j==0) || (j == s-1)){
                cout << "[" << i << "," << j << "]=";
                is >> a(i,j);
            }
        }
    }
    return is;
}

//Task: 	getting
//Input:    int i,j - indexes of the element
//Output:   int     - the element of the matrix in the ith row and jth column
//Activity: gets the given element of the diagonal matrix
int Matrix::operator()(int i, int j) const
{
    int s = getSize();
    if ((i >= s || i < 0 ) || (j >= s || j < 0 )) throw OVERINDEXED;
    if ((i != j) && (j!=0) && (j != s-1))  return 0;
    return _v[i][j];
}

//Task: 	setting
//Input:    int i,j - indexes of the element
//Output:   int     - the element of the matrix in ith row and jth column
//Activity: gives a reference to the given elements of the diagonal matrix
int& Matrix::operator()(int i, int j)
{
    int s = getSize();
    if ((i >= s || i < 0 ) || (j >= s || j < 0 )) throw OVERINDEXED;
    if ((i != j) && (j!=0) && (j != s-1))
        throw NULLPART;

    return _v[i][j];
}
