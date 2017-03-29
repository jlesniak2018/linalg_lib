#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

template<class T>
class Matrix;

template<typename T>
struct expon : public std::binary_function<T, T, T> {
    T operator() (const T& a, const T& b) const {return pow(a, b);}
};

// Generic function to perform element wise matrix operations with a scalar
template<typename T, typename F>
Matrix<T> scalar_operation(const Matrix<T> &a, const T b, F f) { 
    std::vector<std::vector<T> > new_els = a.elements;
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
    if (a.elements.size() != b.elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (a.elements[0].size() != b.elements[0].size()) throw std::invalid_argument("Dimensions aren't correct");

    std::vector<std::vector<T> > new_els = a.elements;
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] = f(new_els[i][j], b.elements[i][j]);
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

template<class T>
class Matrix {
    template<typename M, typename F>
    friend Matrix<M> scalar_operation(const Matrix<M> &a, const M b, F f);
    
    template<typename M, typename F>
    friend Matrix<M> matrix_operation(const Matrix<M> &a, const Matrix<M> &b, F f);
    
    friend Matrix<T> operator+<>(const Matrix<T> &a, const T b);
    friend Matrix<T> operator-<>(const Matrix<T> &a, const T b);
    friend Matrix<T> operator*<>(const Matrix<T> &a, const T b);
    friend Matrix<T> operator/<>(const Matrix<T> &a, const T b);
    friend Matrix<T> operator^<>(const Matrix<T> &a, const T b);
    
    friend Matrix<T> operator+<>(const Matrix<T> &a, const Matrix<T> &b);
    friend Matrix<T> operator-<>(const Matrix<T> &a, const Matrix<T> &b);
    friend Matrix<T> operator*<>(const Matrix<T> &a, const Matrix<T> &b);
    friend Matrix<T> operator/<>(const Matrix<T> &a, const Matrix<T> &b);
    
    private:
        std::vector<std::vector<T> > elements;
        int rows;
        int cols;

    public:
        Matrix(const std::vector<std::vector<T> > elements) {
            if (elements.size() == 0) throw std::invalid_argument("Dimensions aren't correct");

            typename std::vector<std::vector<T> >::const_iterator it = elements.begin();
            this->cols = it->size();
            this->rows = 1;
            ++it;
            for (; it != elements.end(); ++it) {
                this->rows++;
                if (it->size() != this->cols) throw std::invalid_argument("Dimensions aren't correct");
            }

            this->elements = elements;
        }

        void transpose() {
            int r = elements.size();
            int c = elements[0].size();
            std::vector<std::vector<T> > trans_vect = std::vector<std::vector<T> >(c);
            for (int i = 0; i < c; ++i) {
                std::vector<T> cur_row = std::vector<T>(r);
                for (int j = 0; j < r; ++j) {
                    cur_row[j] = elements[j][i];
                }
                trans_vect[i] = cur_row;
            }
            elements = trans_vect;
        }

        std::ostream& print(std::ostream &o) const {
            int r = elements.size();
            int c = elements[0].size();
            for (int i = 0; i < r; ++i) {
                o << "| ";
                for (int j = 0; j < c; ++j) 
                    o << elements[i][j] << ((j==c-1) ? " " : ", ");
                o << "|" << std::endl;
            }
            return o;
        }
        
        int num_rows() { return this->rows; }
        int num_cols() { return this->cols; }
};

#endif
