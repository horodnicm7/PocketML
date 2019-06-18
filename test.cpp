#include <iostream>
#include <math.h>

#include "tests/test_linearreg.hpp"
#include "tests/test_logisticreg.hpp"
#include "tests/test_utils.hpp"

using namespace std;

int main() {
        test_linear_regression_1();
        test_split_data_1();
        test_logistic_regression_1();

        return 0;
}
