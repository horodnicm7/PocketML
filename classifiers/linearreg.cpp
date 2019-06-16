#include <math.h>
#include "linearreg.h"

template<typename T>
LinearRegression<T>::LinearRegression() {

}

template<typename T>
void LinearRegression<T>::train(T *x, T *y, int len) {
        double mean_x = this->mean(x, len);
        double mean_y = this->mean(y, len);

        // the equation I'm trying to determine is y = A + Bx
        register double up = 0, down = 0;
        register T *p1 = &x[0];
        register T *p2 = &y[0];

        for (int i = 0; i < len; i++, p1++, p2++) {
                up += (*p1 - mean_x) * (*p2 - mean_y);
                down += pow(*p1 - mean_x, 2);
        }

        this->b = up / down;
        this->a = mean_y - this->b * mean_x;
}

template<typename T>
T* LinearRegression<T>::predict(T *y, int len) {

}

template<typename T>
double LinearRegression<T>::mean(T *v, int len) {
        register double sum = 0;
        register T *p = &v[0];

        for (int i = 0; i < len; i++, p++) {
                sum += *p;
        }

        return sum / len;
}
