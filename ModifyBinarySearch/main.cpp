#include <iostream>
#include <stdio.h>
#include <time.h>
#include <chrono>

#include "ModifyBinarySearch.hpp"

int main()
{
    std::vector<int> Vector(100);
    for (size_t i = 0; i < Vector.size(); ++i)
        Vector[i] = (i + 1) * 5;
    for (size_t i = 0; i < Vector.size(); ++i)
        std::cout << Vector[i] << ' ';

    int value = 0;

    while (value != -1)
    {
        std::cout << std::endl << "choose value before\n" << Vector.back() << ": \n";
        std::cin >> value;

        auto begin = std::chrono::steady_clock::now();
        auto result = ModifyBinarySearch(&Vector.front(), &Vector.back(), value);
        auto end = std::chrono::steady_clock::now();
    
        if (result.has_value())
            std::cout << "result is " << result.value() << std::endl;
        else
            std::cout << "error" << std::endl;
        std::cout << "working time is " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin) << std::endl;
    }
}
