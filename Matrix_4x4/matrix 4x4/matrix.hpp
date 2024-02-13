#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

template<typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> matrix;

	Matrix<double> Triangle() const;
public:
	const int size = 4;
	
	Matrix();
	Matrix(const Matrix& other);
	Matrix(std::string path_to_file);

	std::vector<T>& operator[](size_t index);
	const std::vector<T>& operator[](size_t index) const;
	Matrix& operator=(const Matrix& second);
	Matrix& operator+=(const Matrix& second);
	Matrix& operator-=(const Matrix& second);
	Matrix& operator*=(const Matrix& second);
	Matrix& operator*=(double second);
	Matrix& operator/=(double second);
	Matrix operator+(const Matrix& second) const;
	Matrix operator-(const Matrix& second) const;
	Matrix operator*(const Matrix& second) const;
	Matrix operator*(double second) const;
	Matrix operator/(double second) const;

	Matrix<double> Inverse() const;
	double Det() const;

	void SaveToFile(std::string path_to_file) const;
};

template<typename T>
Matrix<T>::Matrix()
{
	matrix.resize(size);
	for (size_t i = 0; i < size; ++i)
		matrix[i].resize(size);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
	matrix.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		matrix[i].resize(size);
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] = other[i][j];
	}
}

template<typename T>
Matrix<T>::Matrix(std::string path_to_file)
{
	matrix.resize(size);
	for (size_t i = 0; i < size; ++i)
		matrix[i].resize(size);

	std::ifstream file(path_to_file);
	std::string temp_line;
	std::getline(file, temp_line);
	file.close();
	std::string temp;
	size_t j = 0;
	for (size_t i = 0; i < temp_line.size(); ++i)
	{
		char symbol = temp_line[i];
		if (symbol != ',')
			temp += symbol;
		else
		{
			matrix[j / size][j % size] = std::stod(temp);
			temp.clear();
			++j;
			++i;
		}
	}
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](size_t index)
{
	return this->matrix[index];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](size_t index) const
{
	return this->matrix[index];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& second)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] = second[i][j];
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& second)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] += second[i][j];
	return *(this);
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& second)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] -= second[i][j];
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& second)
{
	std::vector<std::vector<T>> matrix_temp(size);
	for (size_t i = 0; i < size; ++i)
	{
		matrix_temp[i].resize(size);
		for (size_t j = 0; j < size; ++j)
			for (size_t k = 0; k < size; ++k)
				matrix_temp[i][j] += matrix[k][i] * second[j][k];
	}
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] = matrix_temp[i][j];
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(double second)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] *= second;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator/=(double second)
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix[i][j] /= second;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& second) const
{
	Matrix<T> matrix_temp = *this;
	matrix_temp += second;
	return matrix_temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& second) const
{
	Matrix<T> matrix_temp = *this;
	return matrix_temp -= second;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& second) const
{
	Matrix<T> matrix_temp(*this);
	return matrix_temp *= second;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(double second) const
{
	Matrix<T> matrix_temp = *this;
	return matrix_temp *= second;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(double second) const
{
	Matrix<T> matrix_temp = *this;
	return matrix_temp /= second;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
	double Eps = 0.000001f;
	for (size_t i = 0; i < matrix.size; ++i)
	{
		for (size_t j = 0; j < matrix.size; ++j)
		{
			if (abs(matrix[i][j]) < Eps)
				os << "0 ";
			else
				os << matrix[i][j] << ' ';
		}
		os << "\n";
	}
	return os;
}

template<typename T>
Matrix<double> Matrix<T>::Triangle() const
{
	auto sub = [](std::vector<double>& minuend, const std::vector<double>& subtrahend, double koef)
		{
			for (size_t i = 0; i < minuend.size(); ++i)
				minuend[i] -= subtrahend[i] * koef;
		};

	Matrix<double> matrix_double;
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix_double[i][j] = (double)matrix[i][j];

	int sign = 1;

	for (size_t i = 0; i < size; ++i)
	{
		if (matrix_double[i][i] == 0)
			for (size_t j = 0; j < size - i; ++j)
			{
				if (matrix_double[i + j][i] != 0)
				{
					std::swap(matrix_double[i], matrix_double[i + j]);
					sign *= -1;
					break;
				}
			}
		for (size_t j = 1; j < size - i; ++j)
			if (matrix_double[i + j][i] != 0)
				sub(matrix_double[i + j], matrix_double[i], (matrix_double[i + j][i] / matrix_double[i][i]));
	}
	matrix_double[0][0] *= sign;

	return matrix_double;
}

template<typename T>
Matrix<double> Matrix<T>::Inverse() const
{
	if (this->Det() == 0)
		throw std::exception("the matrix is ​​singular, there is no inverse!\n");
	
	auto sub = [](std::vector<double>& minuend, const std::vector<double>& subtrahend, double koef)
	{
		for (size_t i = 0; i < minuend.size(); ++i)
			minuend[i] -= subtrahend[i] * koef;
	};

	Matrix<double> matrix_inversed;
	for (size_t i = 0; i < size; ++i)
		matrix_inversed[i][i] = 1;

	Matrix<double> matrix_double;
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			matrix_double[i][j] = (double)matrix[i][j];

	for (size_t i = 0; i < size; ++i)
	{
		if (matrix_double[i][i] == 0)
			for (size_t j = 0; j < size - i; ++j)
			{
				if (matrix_double[i + j][i] != 0)
				{
					std::swap(matrix_double[i], matrix_double[i + j]);
					std::swap(matrix_inversed[i], matrix_inversed[i + j]);
					break;
				}
			}
		for (size_t j = 1; j < size - i; ++j)
			if (matrix_double[i + j][i] != 0)
			{
				double koef = matrix_double[i + j][i] / matrix_double[i][i];
				sub(matrix_double[i + j], matrix_double[i], koef);
				sub(matrix_inversed[i + j], matrix_inversed[i], koef);
			}
	}

	for (int i = size - 1; i >= 0; --i)
	{
		for (size_t j = 0; j < i; ++j)
			sub(matrix_inversed[j], matrix_inversed[i], matrix_double[j][i] / matrix_double[i][i]);
		double koef = matrix_double[i][i];
		for (size_t j = 0; j < size; ++j)
			matrix_inversed[i][j] /= koef;
	}

	return matrix_inversed;
}

template<typename T>
double Matrix<T>::Det() const
{
	auto matrix_triangle = this->Triangle();
	double result = 1;
	for (size_t i = 0; i < size; ++i)
		result *= matrix_triangle[i][i];
	return result;
}

template<typename T>
void Matrix<T>::SaveToFile(std::string path_to_file) const
{
	std::ofstream file(path_to_file);
	for (size_t i = 0; i < pow(size, 2); ++i)
		file << matrix[i / size][i % size] << ", ";
	file.close();
}

#endif

// Если подключен вектор, то говорим ему, чтобы определил умножение
#ifdef VECTOR4_H
#include "../../Vector_4/Vector4/vector4.h"
#endif