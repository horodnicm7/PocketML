#pragma once
#include <math.h>

#define EULER 2.7182
#define PI 3.141592

// function that splits a set of data in 2 (training and testing), depending
// on the test_ratio. The first elements are assigned to testing
template<typename T>
void split_data(T *data_x, T *data_y, int len, T **train_x, T **train_y,
        T **test_x, T **test_y, double test_ratio) {
        register int test_len = (int) ((double) len * test_ratio);

        *train_x = new T[len - test_len];
        *train_y = new T[len - test_len];
        *test_x = new T[test_len];
        *test_y = new T[test_len];

        register T *p1 = &(*test_x)[0];
        register T *p2 = &(*test_y)[0];

        for (int i = 0; i < test_len; i++) {
                *p1 = data_x[i];
                *p2 = data_y[i];
                p1++;
                p2++;
        }

        p1 = &(*train_x)[0];
        p2 = &(*train_y)[0];

        for (int i = test_len; i < len; i++) {
                *p1 = data_x[i];
                *p2 = data_y[i];
                p1++;
                p2++;
        }
}
