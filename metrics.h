#pragma once

// function to compute the "mean squared error"
template<typename T>
double MSE(T *expected, T *actual, int len);

// function to compute the "mean absolute error"
template<typename T>
double MAE(T *expected, T *actual, int len);

// function to compute the "mean squared log error"
template<typename T>
double MSLE(T *expected, T *actual, int len);

// function to compute the "root mean square error"
template<typename T>
double RMSE(T *expected, T *actual, int len);
