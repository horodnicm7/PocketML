#pragma once
#include <math.h>

// function to compute the "mean squared error"
template<typename T>
double MSE(T *expected, T *actual, int len) {
        register double sum = 0;
        register T *p1 = &expected[0];
        register T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += pow(*p1 - *p2, 2);
        }

        return sum / len;
}

// function to compute the "mean absolute error"
template<typename T>
double MAE(T *expected, T *actual, int len) {
        register double sum = 0;
        register T *p1 = &expected[0];
        register T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += abs(*p1 - *p2);
        }

        return sum / len;
}

// function to compute the "mean squared log error"
template<typename T>
double MSLE(T *expected, T *actual, int len) {
        register double sum = 0;
        register T *p1 = &expected[0];
        register T *p2 = &actual[0];

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

// function that computes the RSS (Residual Sum of Squares)
// RSS = sum((yp - ye)^2), yp = predicted y, ye = correct y
template<typename T>
double RSS(T *expected, T *actual, int len) {
        register double sum = 0;
        register T *p1 = &expected[0];
        register T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                sum += pow(*p1 - *p2, 2);
        }

        return sum;
}

// function that computes the RSE (residual standard error)
// RSE = sqrt((1/n-2) * RSS)
template<typename T>
double RSE(T *expected, T *actual, int len) {
        return sqrt((double) (1 / (len - 2)) * RSS<T>(expected, actual, len));
}

// function that computes the TTS (Total Sum of Squares)
// TSS = sum((ye - my) ^ 2), my = average y
template<typename T>
double TSS(T *expected, int len) {
        register double avg = 0, sum = 0;
        register T *p = &expected[0];

        for (int i = 0; i < len; i++, p++) {
                avg += *p;
        }
        avg /= len;

        p = &expected[0];
        for (int i = 0; i < len; i++, p++) {
                sum += pow(*p - avg, 2);
        }

        return sum;
}

// function that computes the R2 statistics
// R2 = (TSS - RSS) / TSS, always between 0 and 1
template<typename T>
double R2(T *expected, T *actual, int len) {
        double tss = TSS(expected, len);
        double rss = RSS(expected, actual, len);

        return (double) ((tss - rss) / tss);
}

// function that computes how many predictions were correct
template<typename T>
double accuracy(T *expected, T *actual, int len) {
        int correct = 0;
        T *p1 = &expected[0];
        T *p2 = &actual[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                if (*p1 == *p2) {
                        correct++;
                }
        }

        return (double) (len / correct);
}
