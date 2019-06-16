template<typename T>
class LinearRegression {
public:
        LinearRegression();
        void train(T *x, T *y, int len);
        T* predict(T *y, int len);
private:
        T *x;
        T *y;
        double a, b;
        double mean(T *v, int len);
};
