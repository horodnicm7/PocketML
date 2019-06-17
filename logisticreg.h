#pragma once

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
