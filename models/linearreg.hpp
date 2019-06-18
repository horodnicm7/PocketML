#pragma once
#include <math.h>

template<typename T1, typename T2>
class LinearRegression {
public:
        double a, b;
        LinearRegression();
        void train(T1 *x, T2 *y, int len);
        double* predict(T1 *x, int len);
private:
        double mean_x(T1 *v, int len);
        double mean_y(T2 *v, int len);
        double function(T1 x);
};

template<typename T1, typename T2>
LinearRegression<T1, T2>::LinearRegression() {
        this->a = 0;
        this->b = 0;
}

template<typename T1, typename T2>
void LinearRegression<T1, T2>::train(T1 *x, T2 *y, int len) {
        double mean_x = this->mean_x(x, len);
        double mean_y = this->mean_y(y, len);

        // the equation I'm trying to determine is y = A + Bx
        register double up = 0, down = 0;
        register T1 *p1 = &x[0];
        register T2 *p2 = &y[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                up += (*p1 - mean_x) * (*p2 - mean_y);
                down += pow(*p1 - mean_x, 2);
        }

        this->b = up / down;
        this->a = mean_y - this->b * mean_x;
}

template<typename T1, typename T2>
double* LinearRegression<T1, T2>::predict(T1 *x, int len) {
        double *prediction = new double[len];
        T1 *px = &x[0];
        double *pp = &prediction[0];

        for (int i = 0; i < len; i++, px++, pp++) {
                *pp = this->function(*px);
        }

        return prediction;
}

template<typename T1, typename T2>
double LinearRegression<T1, T2>::mean_x(T1 *v, int len) {
        register double sum = 0;
        register T1 *p = &v[0];

        for (int i = 0; i < len; i++, p++) {
                sum += *p;
        }

        return sum / len;
}

template<typename T1, typename T2>
double LinearRegression<T1, T2>::mean_y(T2 *v, int len) {
        register double sum = 0;
        register T2 *p = &v[0];

        for (int i = 0; i < len; i++, p++) {
                sum += *p;
        }

        return sum / len;
}

template<typename T1, typename T2>
double LinearRegression<T1, T2>::function(T1 x) {
        return this->a + this->b * x;
}
