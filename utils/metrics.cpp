#pragma once
#include <math.h>
#include "metrics.h"

// function to compute the "mean squared error"
template<typename T>
double MSE(T *expected, T *actual, int len) {
        double sum = 0;
        T *p1 = &expected[0];
        T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += pow(*p1 - *p2, 2);
        }

        return sum / len;
}

// function to compute the "mean absolute error"
template<typename T>
double MAE(T *expected, T *actual, int len) {
        double sum = 0;
        T *p1 = &expected[0];
        T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += abs(*p1 - *p2);
        }

        return sum / len;
}

// function to compute the "mean squared log error"
template<typename T>
double MSLE(T *expected, T *actual, int len) {
        double sum = 0;
        T *p1 = &expected[0];
        T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += pow(log((*p1 + 1) / (*p2 + 1)), 2);
        }

        return sum / len;
}

// function to compute the "root mean square error"
template<typename T>
double RMSE(T *expected, T *actual, int len) {
        return sqrt(MSE(expected, actual, len));
}
