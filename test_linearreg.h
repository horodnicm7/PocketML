#include "linearreg.h"

void test_linear_regression_1() {
        LinearRegression<double, double> *lr = new LinearRegression<double, double>();

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

        //cout << "MSE: " << MSE(data_x, t, NT) << endl;
        //cout << "MAE: " << MAE(data_x, t, NT) << endl;
        //cout << "MSLE: " << MSLE(data_x, t, NT) << endl;
        //cout << "RMSE: " << RMSE(data_x, t, NT) << endl;

        delete t;
        delete lr;
}
