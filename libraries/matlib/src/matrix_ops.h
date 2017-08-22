#ifndef _MATRIX_OPS_H_
#define _MATRIX_OPS_H_

#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
#include "matrix.h"

template<typename T>
struct expon : public std::binary_function<T, T, T> {
    T operator() (const T& a, const T& b) const {return pow(a, b);}
};

// Generic function to perform element wise matrix operations with a scalar
template<typename T, typename F>
Matrix<T> scalar_operation(const Matrix<T> &a, const T b, F f) { 
    std::vector<std::vector<T> > new_els = a.get_elements();
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in = f(*it_in, b);
        }
    }
    return Matrix<T>(new_els);
}

// Generic function to perform element wise matrix operations with another matrix
template<typename T, typename F>
Matrix<T> matrix_operation(const Matrix<T> &a, const Matrix<T> &b, F f) {
    std::vector<std::vector<T> > new_els = a.get_elements();
    std::vector<std::vector<T> > other_els = b.get_elements();

    if (new_els.size() != other_els.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (new_els[0].size() != other_els[0].size()) throw std::invalid_argument("Dimensions aren't correct");
 
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] = f(new_els[i][j], other_els[i][j]);
        }
    }
    return Matrix<T>(new_els);
}

// Add scalar to all values in Matrix
template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const T b) {
    return scalar_operation(a, b, std::plus<T>()); 
}

// Subtract scalar from all values in Matrix
template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const T b) {
    return scalar_operation(a, b, std::minus<T>()); 
}

// Multiply all values in matrix by scalar value
template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const T b) {
    return scalar_operation(a, b, std::multiplies<T>()); 
}

// Divide all values in matrix by scalar value
template<typename T>
Matrix<T> operator/(const Matrix<T> &a, const T b) {
    return scalar_operation(a, b, std::divides<T>()); 
}

// Raise all values in matrix to a scalar value
template<typename T>
Matrix<T> operator^(const Matrix<T> &a, const T b) {
    return scalar_operation(a, b, expon<T>());
}

template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
    return matrix_operation(a, b, std::plus<T>()); 
}

template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b) {
    return matrix_operation(a, b, std::minus<T>());
}

template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b) {
    return matrix_operation(a, b, std::multiplies<T>());
}

template<typename T>
Matrix<T> operator/(const Matrix<T> &a, const Matrix<T> &b) {
    return matrix_operation(a, b, std::divides<T>());
}

template<typename T>
Matrix<T> append(const Matrix<T> &a, const Matrix<T> &b, int axis=0) {
    std::vector<std::vector<T> > cur_els = a.get_elements();
    std::vector<std::vector<T> > new_els = b.get_elements();

    std::vector<std::vector<T> > new_mat;

    if (axis==0) {
        if (cur_els[0].size() != new_els[0].size()) {
            throw std::invalid_argument("Row lengths do not match");
        }

        int r = cur_els.size()+new_els.size();
        int c = cur_els[0].size();

        new_mat.reserve(r);

        for (int i = 0; i < r; ++i) {
            std::vector<T> cur_r;
            cur_r.reserve(c);

            std::vector<T> row_to_cpy;
            if (i < cur_els.size()) {
                row_to_cpy = cur_els[i];
            } else {
                row_to_cpy = new_els[i-cur_els.size()];
            }

            for (int j = 0; j < c; ++j) {
                cur_r.push_back(row_to_cpy[j]);
            }

            new_mat.push_back(cur_r);
        }
    } else {
        if (cur_els.size() != new_els.size()) {
            throw std::invalid_argument("Column lengths do not match");
        }

        int r = cur_els.size();
        int c = cur_els[0].size() + new_els[0].size();

        new_mat.reserve(r);

        for (int i = 0; i < r; ++i) {
            std::vector<T> cur_r;
            cur_r.reserve(c);

            for (int j = 0; j < c; ++j) {
                if (j < cur_els[0].size()) {
                    cur_r.push_back(cur_els[i][j]);
                } else {
                    cur_r.push_back(new_els[i][j-cur_els[0].size()]);
                }
            }
            
            new_mat.push_back(cur_r);
        }
    }

    return new_mat;
}

#endif
