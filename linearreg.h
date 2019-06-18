template<typename T1, typename T2>
class LinearRegression {
public:
        double a, b;
        LinearRegression();
        void train(T1 *x, T2 *y, int len);
        double* predict(T1 *x, int len);
private:
        double mean_x(T1 *v, int len);
        double mean_y(T2 *v, int len);
        double function(T1 x);
};
