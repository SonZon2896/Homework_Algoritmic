#include <iostream>
#include <stdio.h>
#include <time.h>
#include <chrono>

#include "ModifyBinarySearch.hpp"

int main()
{
    std::vector<int> vector(100000000); // 0.1 milliard
    for (size_t i = 0; i < vector.size(); ++i)
        vector[i] = i + 1;
    /*for (size_t i = 0; i < vector.size(); ++i)
        std::cout << vector[i] << ' ';*/

    int value = 0;

    while (value != -1)
    {
        std::cout << std::endl << "choose value before\n" << vector.size() << ": \n";
        std::cin >> value;

        auto begin = std::chrono::steady_clock::now();
        auto result = ModifyBinarySearch(vector, value);
        auto end = std::chrono::steady_clock::now();
    
        if (result.has_value())
            std::cout << "result is " << result.value() << std::endl;
        else
            std::cout << "error" << std::endl;
        std::cout << "working time is " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    }
}
