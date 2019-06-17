#include <math.h>
#include "logisticreg.h"
#include "linearreg.h"
#include "utils.h"

template<typename T1, typename T2>
LogisticRegression<T1, T2>::LogisticRegression() {
        this->threshold = 0.5;
}

template<typename T1, typename T2>
void LogisticRegression<T1, T2>::train(T1 *x, T2 *y, int len) {
        LinearRegression<double> *lr = new LinearRegression<double>();

        register T2 *p = &y[0];
        for (int i = 0; i < len; i++, p++) {
                *p = log(*p / (1 + *p));
        }

        lr->train(x, y, len);

        this->a = lr->a;
        this->b = lr->b;

        delete lr;
}

template<typename T1, typename T2>
T2* LogisticRegression<T1, T2>::predict(T1 *x, int len) {
        T2 *prediction = new T2[len];
        register T1 *px = &x[0];
        register T2 *pp = &prediction[0];

        for (int i = 0; i < len; i++) {
                *pp = this->function(*px);
                pp++;
                px++;
        }

        return prediction;
}

template<typename T1, typename T2>
void LogisticRegression<T1, T2>::set_thresold(double threshold) {
        if (threshold >= 0 && threshold <= 1) {
                this->threshold = threshold;
        }
}

template<typename T1, typename T2>
T2 LogisticRegression<T1, T2>::function(T1 x) {
        double term = pow(EULER, this->a + this->b * x);
        return (T2) (term / (1 + term));
}
