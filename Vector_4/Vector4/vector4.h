#ifndef VECTOR4_H
#define VECTOR4_H
#include <iostream>

template <typename T>
class Vector4
{
public:
	T x, y, z, w;
	const size_t size = 4;

	Vector4() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {};
	Vector4(T value) : x{ value }, y{ value }, z{ value }, w{ value } {};
	Vector4(T x, T y, T z, T w) : x{ x }, y{ y }, z{ z }, w{ w } {};

	T& operator[](size_t index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw std::runtime_error("Index more then size vector4");
		}
	}
	const T& operator[](size_t index) const
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			throw std::runtime_error("Index more then size vector4");
		}
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector4<T>& vector4)
{
	for (size_t i = 0; i < vector4.size; ++i)
		os << vector4[i] << ' ';
	return os;
}

#endif

// Если подключена матрица, то определяем умножение на нее
#ifdef MATRIX_HPP

#ifndef VECTOR4_H_MULT_MATRIX
#define VECTOR4_H_MULT_MATRIX

template<typename T1, typename T2>
Vector4<T1> operator*(const Vector4<T1>& vector4, const Matrix<T2>& matrix)
{
	Vector4<T1> result;
	for (size_t i = 0; i < vector4.size; ++i)
		for (size_t j = 0; j < vector4.size; ++j)
			result[i] += vector4[j] * matrix[j][i];
	return result;
}

template<typename T1, typename T2>
Vector4<T2> operator*(const Matrix<T1>& matrix, const Vector4<T2>& vector4)
{
	Vector4<T2> result;
	for (size_t i = 0; i < vector4.size; ++i)
		for (size_t j = 0; j < vector4.size; ++j)
			result[i] += vector4[j] * matrix[i][j];
	return result;
}

#endif

#endif