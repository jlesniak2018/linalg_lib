#include <iostream>
#include "matrix.h"
#include <vector>
#include <initializer_list>

using namespace std;

template<typename T>
ostream& operator<<(ostream &o, const Matrix<T> &a) {
    return a.print(o);
}

int main() {
    vector<float> a1 = {0, 1};
    vector<float> a2 = {2, 3};
    vector<float> a3 = {4, 5};
    vector<vector<float> > av = {a1, a2, a3};
    Matrix<float> a = Matrix<float>(av);

    vector<float> b1 = {6, 7, 8};
    vector<float> b2 = {9, 10, 11};
    vector<vector<float> > bv = {b1, b2};
    Matrix<float> b = Matrix<float>(bv);

    vector<vector<float> > cv = {{6, 7, 8}, {12, 11, 10}};
    Matrix<float> c = Matrix<float>(cv);

    cout << b << endl;
    b.transpose();
    cout << a << endl;
    cout << b << endl;
    cout << a+5.0f << endl;
    cout << (a+b);
    cout << endl;
    cout << (a^2.0f);
    cout << endl;
    cout << c;
    cout << endl;
    cout << c.num_rows() << " " << c.num_cols() << endl;
    return 0;
}
