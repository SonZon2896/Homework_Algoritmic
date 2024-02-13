#include <iostream>
#include "matrix.hpp"
#include <random>
#include <ctime>

#define M_PRINT(comment) std::cout << std::endl << comment << std::endl <<

#define TEST_OVERLOAD // working 
#define TEST_FUNCTIONS // working
//#define TEST_WRITING // working
//#define TEST_READING // working

int main()
{
    srand(std::time(0));
    Matrix<double> matrix;
    for (size_t i = 0; i < matrix.size; ++i)
        for (size_t j = 0; j < matrix.size; ++j)
            matrix[i][j] = (double)(rand() % 10);
    Matrix<double> matrix_second;
    for (size_t i = 0; i < matrix_second.size; ++i)
        for (size_t j = 0; j < matrix_second.size; ++j)
            matrix_second[i][j] = rand() % 10;

    M_PRINT("first matrix") matrix;
    M_PRINT("second matrix") matrix_second;

#ifdef TEST_OVERLOAD
	M_PRINT("first matrix + second matrix") matrix + matrix_second;
    M_PRINT("first matrix - second matrix") matrix - matrix_second;
    M_PRINT("first matrix * second matrix") matrix * matrix_second;
    M_PRINT("first matrix * 2") matrix * 2;
    M_PRINT("first matrix / 2") matrix / 2;
#endif

#ifdef TEST_FUNCTIONS
    double det = matrix.Det();
    std::cout << std::endl << "firt matrix determinant = " << det << std::endl;
    if (det != 0)
    {
        auto matrix_inversed = matrix.Inverse();
        M_PRINT("first inversed matrix") matrix_inversed;
        M_PRINT("first Inversed matrix * first matrix") matrix_inversed * matrix;
    }
#endif

#ifdef TEST_WRITING
    matrix.SaveToFile("matrix.txt");
    std::cout << "file writing to matrix.txt" << std::endl;
#endif

#ifdef TEST_READING
    Matrix<double> matrix_readed("matrix.txt");
    M_PRINT("matrix from file") matrix_readed; 
#endif
}