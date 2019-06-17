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
