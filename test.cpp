#include <iostream>
#include <math.h>

#include "utils.h"

using namespace std;

template<typename T>
class LinearRegression {
public:
        double a, b;
        LinearRegression();
        void train(T *x, T *y, int len);
        T* predict(T *y, int len);
private:
        double mean(T *v, int len);
        double function(T x);
};

template<typename T1, typename T2>
class LogisticRegression {
public:
        LogisticRegression();
        void train(T1 *x, T2 *y, int len);
        T2* predict(T1 *x, int len);

        void set_thresold(double threshold);

        double a, b, threshold;
private:
        T2 function(T1 x);
};

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

/*void test_split_data_1() {
        int x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        int y[] = {4, 6, 3, 9, 1, 0, 1, 9, 8, 1, 4, 5, 6, 8, 9, 10};
        int N = 16;

        int *tx, *ty, *trx, *trry;
        double ratio = 0.7;
        int len = (int) ((double) N * ratio);

        split_data<int>(x, y, N, &trx, &trry, &tx, &ty, ratio);

        for (int i = 0; i < len; i++) {
                cout << tx[i] << " " << ty[i] << endl;
        }
        cout << endl;

        for (int i = 0; i < N - len; i++) {
                cout << trx[i] << " " << trry[i] << endl;
        }
        cout << endl;
}

void test_linear_regression_1() {
        LinearRegression<double> *lr = new LinearRegression<double>();

        double data_x[] = {4.5, 8.2, 6.3, 2.9, 5.1, 10.8, 12.8, 7.4, 5.9, 8.6};
        double data_y[] = {3, 5, 10, 7, 8, 6, 7.6, 6.3, 5.9, 6.8};
        double test_x[] = {3, 8, 10, 5, 7, 1.8, 5.6, 24.5};
        int N1 = 10;
        int NT = 8;

        lr->train(data_x, data_y, N1);

        cout << lr->a << " " << lr->b << endl;
        double *t = lr->predict(test_x, NT);
        cout << "Finished predicting...\n";

        for (int i = 0; i < NT; i++) {
                cout << test_x[i] << " -> " << t[i] << endl;
        }
        cout << endl;

        cout << "MSE: " << MSE(data_x, t, NT) << endl;
        cout << "MAE: " << MAE(data_x, t, NT) << endl;
        cout << "MSLE: " << MSLE(data_x, t, NT) << endl;
        cout << "RMSE: " << RMSE(data_x, t, NT) << endl;

        delete t;
        delete lr;
}*/

int main() {
        /*test_linear_regression_1();
        test_split_data_1();*/

        return 0;
}
