#pragma once
#include <iostream>
#include <vector>


class Matrix {
public:
    enum Exceptions{OVERINDEXED, NULLPART, DIFFERENT, INVALID};

    Matrix(){ _v.clear(); }
    Matrix(int k);
    ~Matrix() { }
    Matrix(const std::vector<std::vector<int>> &v);
    Matrix(const Matrix& a);
    Matrix& operator=(const Matrix& a);
    int getSize() const {return _v.size();}

    int operator()(int i, int j) const;
    int& operator()(int i, int j);

    friend Matrix operator+ (const Matrix& a, const Matrix& b);
    friend Matrix operator* (const Matrix& a, const Matrix& b);
    friend std::istream& operator>> (std::istream& s, Matrix& a);
    friend std::ostream& operator<< (std::ostream& s, const Matrix& a);
private:
    std::vector<std::vector<int>> _v;

    void reSize(int k);
};
