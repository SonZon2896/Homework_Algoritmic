#pragma once
#include <vector>
#include <optional>

template<typename T>
std::optional<size_t> ModifyBinarySearch(void* iter_start, void* iter_end, T value)
{
	T* start = (T*)iter_start;
	T* end = (T*)iter_end;
	size_t size = end - start + 1;

	// checking weak point
	if (*start == value)
		return 0;
	// checking bounds
	if (value < *start || *end < value)
		return std::nullopt;

	// main algorithm
	for (size_t i = 0, j = 1; i < size; )
	{
		if (i + j >= size || *(start + i + j) > value)
		{
			// checking if stuck
			if (j == 1)
				return std::nullopt;
			// i += j / 2;
			i += j >> 1;
			j = 1;
			continue;
		}
		if (*(start + i + j) == value)
			return i + j;
		// j *= 2;
		j <<= 1;
	}
}