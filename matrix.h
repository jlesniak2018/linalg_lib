#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <cmath>
#include <stdexcept>

template<class T>
class Matrix;

// Add scalar to all values in Matrix
template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const T b) {
    std::vector<std::vector<T> > new_els = a.elements;
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in += b;
        }
    }
    return Matrix<T>(new_els);
}

// Subtract scalar from all values in Matrix
template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const T b) {
    std::vector<std::vector<T> > new_els = a.elements;
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in -= b;
        }
    }
    return Matrix<T>(new_els);
}

// Multiply all values in matrix by scalar value
template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const T b) {
    std::vector<std::vector<T> > new_els = a.elements;
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in *= b;
        }
    }
    return Matrix<T>(new_els);
}

// Divide all values in matrix by scalar value
template<typename T>
Matrix<T> operator/(const Matrix<T> &a, const T b) {
    std::vector<std::vector<T> > new_els = a.elements;
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in /= b;
        }
    }
    return Matrix<T>(new_els);
}

// Raise all values in matrix to a scalar value
template<typename T>
Matrix<T> operator^(const Matrix<T> &a, const T b) {
    std::vector<std::vector<T> > new_els = a.elements;
    typename std::vector<std::vector<T> >::iterator it = new_els.begin();
    typename std::vector<T>::iterator it_in;

    for (; it != new_els.end(); ++it) {
        it_in = it->begin();
        for (; it_in != it->end(); ++it_in) {
            *it_in = pow(*it_in, b);
        }
    }
    return Matrix<T>(new_els);
}

template<typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.elements.size() != b.elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (a.elements[0].size() != b.elements[0].size()) throw std::invalid_argument("Dimensions aren't correct");

    std::vector<std::vector<T> > new_els = a.elements;
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] += b.elements[i][j];
        }
    }
    return Matrix<T>(new_els);
}

template<typename T>
Matrix<T> operator-(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.elements.size() != b.elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (a.elements[0].size() != b.elements[0].size()) throw std::invalid_argument("Dimensions aren't correct");

    std::vector<std::vector<T> > new_els = a.elements;
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] -= b.elements[i][j];
        }
    }
    return Matrix<T>(new_els);
}

template<typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.elements.size() != b.elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (a[0].elements.size() != b[0].elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    std::vector<std::vector<T> > new_els = a.elements;
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] *= b.elements[i][j];
        }
    }
    return Matrix<T>(new_els);
}

template<typename T>
Matrix<T> operator/(const Matrix<T> &a, const Matrix<T> &b) {
    if (a.elements.size() != b.elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    if (a[0].elements.size() != b[0].elements.size()) throw std::invalid_argument("Dimensions aren't correct");

    std::vector<std::vector<T> > new_els = a.elements;
    for (int i = 0; i < new_els.size(); ++i) {
        for (int j = 0; j < new_els[i].size(); ++j) {
            new_els[i][j] /= b.elements[i][j];
        }
    }
    return Matrix<T>(new_els);
}

template<class T>
class Matrix {
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

    public:
        Matrix(const std::vector<std::vector<T> > elements) {
            if (elements.size() == 0) throw std::invalid_argument("Dimensions aren't correct");

            typename std::vector<std::vector<T> >::const_iterator it = elements.begin();
            int row_len = it->size();
            ++it;
            for (; it != elements.end(); ++it) {
                if (it->size() != row_len) throw std::invalid_argument("Dimensions aren't correct");
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
                    o << elements[i][j] << " ";
                o << "|" << std::endl;
            }
            return o;
        }
};

#endif
