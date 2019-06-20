#pragma once
#include <iostream>
#include "../models/logisticreg.hpp"

using namespace std;

void test_logistic_regression_1(int no_threads) {
        cout << "Executing with: " << no_threads << " threads:\n";
        // corect output: [0 0 1 1 1]
        LogisticRegression<int> *lr = new LogisticRegression<int>();
        lr->set_no_threads(no_threads);

        int data_x[] = {1, 2, 3, 5, 6, 7, 8, 10, 11, 14, 15, 16, 17};
        double data_y[] = {0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1};
        int test_x[] = {4, 9, 12, 13, 20};
        int N = 13;
        int NT = 5;

        auto start = high_resolution_clock::now();
        lr->train(data_x, data_y, N);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by training: " << duration.count() << " microseconds" << endl;

        double *tr = lr->predict(test_x, NT, true);

        cout << lr->a << " " << lr->b << endl;
        for (int i = 0; i < NT; i++) {
                cout << test_x[i] << " -> " << tr[i] << endl;
        }
        cout << endl;

        delete lr;
        delete[] tr;
}
