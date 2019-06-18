#pragma once

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
