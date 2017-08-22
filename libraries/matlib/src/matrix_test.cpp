#include <iostream>
#include "matrix.h"
#include "matrix_ops.h"
#include <vector>
#include <initializer_list>

using namespace std;

template<typename T>
ostream& operator<<(ostream &o, const Matrix<T> &a) {
    return a.print(o);
}

int main() {
    Matrix<double> a = Matrix<double>::ones(3, 3);
    Matrix<double> b = Matrix<double>::zeros(3, 3);
    Matrix<double> c = Matrix<double>::init_matrix(2, 7, 3.2);

    cout << a << endl;
    cout << b << endl;
    cout << append(a, b, 0) << endl;
    cout << append(a, b, 1) << endl;
    cout << c << endl;
    return 0;
}
