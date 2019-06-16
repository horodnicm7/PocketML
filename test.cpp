#include <iostream>
#include "utils/metrics.h"
#include "classifiers/linearreg.h"

using namespace std;

int main() {
        LinearRegression<double> *lr = new LinearRegression<double>();

        double data_x[] = {4.5, 8.2, 6.3, 2.9, 5.1, 10.8, 12.8, 7.4};
        double data_y[] = {3, 5, 10, 7, 8, 6, 7.6, 6.3, 5.9, 6.8};
        int N1 = 8;

        lr->train(data_x, data_y, N1);

        cout << MSE(data_x, data_y, N1);

        return 0;
}
