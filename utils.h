#pragma once

// function that splits a set of data in 2 (training and testing), depending
// on the test_ratio. The first elements are assigned to testing
template<typename T>
void split_data(T *data_x, T *data_y, int len, T **train_x, T **train_y,
        T **test_x, T **test_y, double test_ratio);
