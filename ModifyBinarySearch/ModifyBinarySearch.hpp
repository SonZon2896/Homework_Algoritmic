#pragma once
#include <vector>
#include <optional>

template<typename T>
std::optional<size_t> ModifyBinarySearch(const std::vector<T>& vector, T value)
{
	if (vector[0] == value)
		return 0;
	if (value < *vector.begin() || *(vector.end() - 1) < value)
		return std::nullopt;

	for (size_t i = 0, j = 1; i < vector.size(); )
	{
		if (i + j >= vector.size() || vector[i + j] > value)
		{
			i += j / 2;
			j = 1;
			continue;
		}
		if (vector[i + j] == value)
			return i + j;
		j *= 2;
	}
}