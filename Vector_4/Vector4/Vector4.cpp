#include "vector4.h"
#include "../../Matrix_4x4/matrix 4x4/matrix.hpp"
#include <iostream>
#include <random>
#include <ctime>

#define PRINT(message) std::cout << message << std::endl <<

int main()
{
    srand(std::time(0));
    Vector4<double> vector4(1, 2, 3, 4);
    Matrix<double> matrix;
    for (size_t i = 0; i < matrix.size; ++i)
        for (size_t j = 0; j < matrix.size; ++j)
            matrix[i][j] = rand() % 10;
    PRINT("vector4") vector4 << std::endl << std::endl;
    PRINT("matrix") matrix << std::endl << std::endl;
    PRINT("vector4 * matrix") vector4 * matrix << std::endl << std::endl;
    PRINT("matrix * vector4") matrix * vector4 << std::endl;
}
