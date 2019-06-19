#pragma once
#include <math.h>
#include <thread>
#include <mutex>

using namespace std;

template<typename T1, typename T2>
class LinearRegression {
public:
        double a, b;
        LinearRegression();
        void train(T1 *x, T2 *y, int len);
        double* predict(T1 *x, int len);

        void set_no_threads(unsigned no_threads);
private:
        unsigned no_threads;
        T1 *x;
        T2 *y;
        unsigned length;
        mutex mtx;
        double gl_up, gl_down;

        double mean_x(T1 *v, int len);
        double mean_y(T2 *v, int len);
        double function(T1 x);
        void th_train_function(int id, double mean_x, double mean_y);
};

template<typename T1, typename T2>
LinearRegression<T1, T2>::LinearRegression() {
        this->a = 0;
        this->b = 0;
        this->no_threads = 1;
        this->gl_up = 0;
        this->gl_down = 0;
}

template<typename T1, typename T2>
void LinearRegression<T1, T2>::th_train_function(int id, double mean_x, double mean_y) {
        int how_much = this->length / this->no_threads;
        int start = id * how_much;
        int stop = (id + 1) * how_much;
        if (id == this->no_threads - 1) {
                stop = this->length;
        }

        register double up = 0, down = 0;
        register T1 *p1 = &this->x[start];
        register T2 *p2 = &this->y[start];

        for (int i = start; i < stop; i++, p1++, p2++) {
                up += (*p1 - mean_x) * (*p2 - mean_y);
                down += pow(*p1 - mean_x, 2);
        }

        mtx.lock();
        this->gl_up += up;
        this->gl_down += down;
        mtx.unlock();
}

template<typename T1, typename T2>
void LinearRegression<T1, T2>::train(T1 *x, T2 *y, int len) {
        double mean_x = this->mean_x(x, len);
        double mean_y = this->mean_y(y, len);

        // the equation I'm trying to determine is y = A + Bx
        if (this->no_threads == 1) {
                // sequential version
                register double up = 0, down = 0;
                register T1 *p1 = &x[0];
                register T2 *p2 = &y[0];

                for (int i = 0; i < len; i++, p1++, p2++) {
                        up += (*p1 - mean_x) * (*p2 - mean_y);
                        down += pow(*p1 - mean_x, 2);
                }

                this->b = up / down;
                this->a = mean_y - this->b * mean_x;
        } else {
                this->length = len;
                this->x = x;
                this->y = y;

                thread **threads = new thread*[this->no_threads];

                for (int i = 0; i < this->no_threads; i++) {
                        threads[i] = new thread(&LinearRegression<T1, T2>::th_train_function, this, i, mean_x, mean_y);
                }

                for (int i = 0; i < this->no_threads; i++) {
                        threads[i]->join();
                }

                this->b = this->gl_up / this->gl_down;
                this->a = mean_y - this->b * mean_x;
        }
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

template<typename T1, typename T2>
void LinearRegression<T1, T2>::set_no_threads(unsigned no_threads) {
        if (no_threads > 0) {
                this->no_threads = no_threads;
        }
}
