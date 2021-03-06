#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>

#include "../@chabaniuk_m/complex.cpp"
#include "../@theblacl1ght/basic_matrix.cpp"
#include "matrix.hpp"
#include "timer.hpp"

using namespace std;

// порівнює матриці
template<class T>
bool cmp_matrixes(Matrix<T> a, Matrix<T> b) {
    if (a.size() != b.size()) {
        return false;
    }
    int n = a.size();
    for (int i = 0; i < n; i += 1) {
        for (int k = 0; k < n; k += 1) {
            if (a[i][k] != b[i][k]) {
                return false;
            }
        }
    }
    return true;
}

void test_sub_matrix() {
    Matrix<int> m = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16},
    };
    Matrix<int> r = matrix::sub_matrix(m, 2, 2);
    Matrix<int> c = {
        {1, 2, 4},
        {5, 6, 8},
        {13, 14, 16},
    };
    assert(cmp_matrixes(r, c));
}

void test_determinant() {
    Matrix<Complex> m1 = {
        {{1, 0}, {2, 0}},
        {{3, 0}, {4, 0}}
    };
    Complex d1 = matrix::determinant(m1);
    assert(d1 == Complex(-2, 0));

    Matrix<Complex> m2 = {
        {{5, -2}, {0, 0}, {-5, 0}},
        {{0, 0}, {0, -2}, {0, -4}},
        {{-5, 0}, {0, -4}, {5, -2}}
    };
    Complex d2 = matrix::determinant(m2);
    assert(d2 == Complex(40, -24));
}

void test_transpose() {
    Matrix<int> m = {
        {1, 2},
        {3, 4}
    };
    auto r = matrix::transpose(m);
    Matrix<int> c = {
        {1, 3},
        {2, 4}
    };
    assert(cmp_matrixes(r, c));
}

void test_measure_duration() {
    auto ns_duration = measure_duration([&](){
        this_thread::sleep_for(milliseconds(5));
    });
    auto duration = duration_cast<milliseconds>(ns_duration).count();
    cout << "Timer test duration: " << duration << "ms" << '\n';
}

void test_inverse_by_minors() {
    Matrix<Complex> m;
    Matrix<Complex> r;
    const int repeat_time = 1000;
    nanoseconds ns_duration;
    double op_duration;

    m = {
        {{1, 0}, {0, 0}, {3, 0}},
        {{4, 0}, {5, 0}, {6, 0}},
        {{7, 0}, {8, 0}, {9, 0}}
    };
    ns_duration = measure_duration([&](){
        for (int i = 0; i < repeat_time; i += 1) {
            r = matrix::inverse_by_minors(m);
        }
    });
    op_duration = static_cast<double>(duration_cast<milliseconds>(ns_duration).count()) / repeat_time;
    Matrix<Complex> c = {
        {{1./4, 0}, {-2, 0}, {5./4, 0}},
        {{-1./2, 0}, {1, 0}, {-1./2, 0}},
        {{1./4, 0}, {2./3, 0}, {-5./12, 0}}
    };
    assert(cmp_matrixes(r, c));
    cout << "Inverse by minors 1 duration:  " << op_duration << "ms" << '\n';

    m = {
        {{2, 3}, {-5, 0}},
        {{14, 0}, {0, 1}},
    };
    ns_duration = measure_duration([&](){
        for (int i = 0; i < repeat_time; i += 1) {
            r = matrix::inverse_by_minors(m);
        }
    });
    op_duration = static_cast<double>(duration_cast<milliseconds>(ns_duration).count()) / repeat_time;
    c = {
        {{0.000445137, 0.0149121}, {0.0745604, -0.00222568}},
        {{-0.208769, 0.00623192}, {0.0311596, 0.043846}}
    };
    assert(cmp_matrixes(r, c));
    cout << "Inverse by minors 2 duration:  " << op_duration << "ms" << '\n';
}