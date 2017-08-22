#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <stdexcept>

template<class T>
class Matrix;

template<class T>
class Matrix { 
    
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

        static Matrix<T> init_matrix(int r, int c, T n) {
            if (r <= 0 || c <= 0) throw std::invalid_argument("Dimensions must be > 0");
            std::vector<std::vector<T> > els;
            els.reserve(r);

            for (int i = 0; i < r; ++i) {
                std::vector<T> cur_r;
                cur_r.reserve(c);
                for (int j = 0; j < c; ++j) {
                    cur_r.push_back(n);
                }
                els.push_back(cur_r);
            }

            return Matrix<T>(els);
        }

        static Matrix<T> zeros(int r, int c) {
            return init_matrix(r, c, 0.0);
        }

        static Matrix<T> ones(int r, int c) {
            return init_matrix(r, c, 1.0);
        }
        
        const std::vector<std::vector<T> > get_elements() const { return this->elements; }
        
        int num_rows() { return this->rows; }
        int num_cols() { return this->cols; }
};

#endif
