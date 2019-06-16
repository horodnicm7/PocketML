#pragma once

template<typename T>
class LinearRegression {
public:
        LinearRegression();
        void train(T x, T y);
        T predict(T y);
private:
        T *x;
        T *y;
};
