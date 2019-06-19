#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "../utils/metrics.hpp"
#include "../models/linearreg.hpp"

using namespace std;
using namespace std::chrono;

void test_linear_regression_1(int no_threads) {
        cout << "Execution with " << no_threads << " threads:\n";
        LinearRegression<int, double> *lr = new LinearRegression<int, double>();
        lr->set_no_threads(no_threads);
        int N1 = 3000000;
        int NT = 100;

        int *data_x = new int[N1];
        double *data_y = new double[N1];
        int *test_x = new int[NT];

        auto start = high_resolution_clock::now();
        fstream f("test.txt", ios::in);
        for (int i = 0; i < N1; i++) {
                f >> data_x[i];
        }

        for (int i = 0; i < N1; i++) {
                f >> data_y[i];
        }

        for (int i = 0; i < NT; i++) {
                f >> test_x[i];
        }
        f.close();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Time taken by IO: " << duration.count() << " milliseconds" << endl;

        start = high_resolution_clock::now();
        lr->train(data_x, data_y, N1);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);
        cout << "Time taken by training: " << duration.count() << " milliseconds" << endl;

        start = high_resolution_clock::now();

        double *t = lr->predict(test_x, NT);

        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout << "Time taken by prediction: " << duration.count() << " milliseconds" << endl << endl;


        /*cout << lr->a << " " << lr->b << endl;
        for (int i = 0; i < NT; i++) {
                cout << test_x[i] << " -> " << t[i] << endl;
        }
        cout << endl;*/

        /*cout << "MSE: " << MSE(data_x, t, NT) << endl;
        cout << "MAE: " << MAE(data_x, t, NT) << endl;
        cout << "MSLE: " << MSLE(data_x, t, NT) << endl;
        cout << "RMSE: " << RMSE(data_x, t, NT) << endl;*/

        delete t;
        delete lr;
        delete data_x;
        delete data_y;
        delete test_x;
}
