#include <iostream>
#include <math.h>

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

template<typename T>
LinearRegression<T>::LinearRegression() {
        this->a = 0;
        this->b = 0;
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
        T *prediction = new T[len];
        T *py = &y[0];
        T *pp = &prediction[0];

        for (int i = 0; i < len; i++, py++, pp++) {
                *pp = this->function(*py);
        }

        return prediction;
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

template<typename T>
double LinearRegression<T>::function(T x) {
        return this->a + this->b * x;
}

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

void test_split_data_1() {
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
}

int main() {
        test_linear_regression_1();
        test_split_data_1();

        return 0;
}
