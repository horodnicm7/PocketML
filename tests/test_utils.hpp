#pragma once
#include <iostream>
#include "../utils/utils.hpp"

using namespace std;

void test_split_data_1() {
        int x[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        int y[] = {4, 6, 3, 9, 1, 0, 1, 9, 8, 1, 4, 5, 6, 8, 9, 10};
        int N = 16;

        int *tx, *ty, *trx, *trry;
        double ratio = 0.7;
        int len = (int) ((double) N * ratio);

        split_data<int>(x, y, N, &trx, &trry, &tx, &ty, ratio);

        for (int i = 0; i < len; i++) {
                cout << tx[i] << " " << ty[i] << endl;
        }
        cout << endl;

        for (int i = 0; i < N - len; i++) {
                cout << trx[i] << " " << trry[i] << endl;
        }
        cout << endl;
}
