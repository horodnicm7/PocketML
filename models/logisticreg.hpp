#pragma once
#include <math.h>
#include "linearreg.hpp"
#include "../utils/utils.hpp"

template<typename T>
class LogisticRegression {
public:
        LogisticRegression();
        void train(T *x, double *y, int len);
        double* predict(T *x, int len, bool round);

        void set_thresold(double threshold);
        void set_delta(double delta);

        double a, b, threshold;
        double delta;
private:
        double function(T x);
};

template<typename T>
LogisticRegression<T>::LogisticRegression() {
        this->threshold = 0.5;
        this->delta = 0.0000001;
}

template<typename T>
void LogisticRegression<T>::train(T *x, double *y, int len) {
        LinearRegression<T, double> *lr = new LinearRegression<T, double>();

        register double *p = &y[0];
        for (int i = 0; i < len; i++, p++) {
                if (*p == 1) {
                        *p = log((*p - this->delta) / (1 - (*p - this->delta)));
                } else if (*p == 0) {
                        *p = log(this->delta / (1 - this->delta));
                } else {
                        *p = log(*p / (1 - *p));
                }
        }

        lr->train(x, y, len);

        this->a = lr->a;
        this->b = lr->b;

        delete lr;
}

template<typename T>
double* LogisticRegression<T>::predict(T *x, int len, bool round) {
        double *prediction = new double[len];
        register T *px = &x[0];
        register double *pp = &prediction[0];

        if (round == false) {
                for (int i = 0; i < len; i++) {
                        *pp = this->function(*px);
                        pp++;
                        px++;
                }
        } else {
                for (int i = 0; i < len; i++) {
                        *pp = this->function(*px);
                        if (*pp >= this->threshold) {
                                *pp = 1;
                        } else {
                                *pp = 0;
                        }
                        pp++;
                        px++;
                }
        }

        return prediction;
}

template<typename T>
void LogisticRegression<T>::set_thresold(double threshold) {
        if (threshold >= 0 && threshold <= 1) {
                this->threshold = threshold;
        }
}

template<typename T>
void LogisticRegression<T>::set_delta(double delta) {
        if (delta < 1) {
                this->delta = delta;
        }
}

template<typename T>
double LogisticRegression<T>::function(T x) {
        double term = pow(EULER, this->a + this->b * x);
        return term / (1 + term);
}
