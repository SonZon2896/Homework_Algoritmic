#include <iostream>
#include <deque>
#include <vector>

void PrintMinMaxInMovingScope(const std::vector<int>& src, int k) {
    std::deque<size_t> maxDeque{ 0 };
    std::deque<size_t> minDeque{ 0 };

    for (int i = 1; i < k; ++i)
    {
        // удаляем элементы, которые меньше (больше) того, которое мы сейчас добавим (нет смысла их хранить)
        while (!maxDeque.empty() && src[maxDeque.back()] <= src[i])
            maxDeque.pop_back();
        maxDeque.push_back(i);
        while (!minDeque.empty() && src[minDeque.back()] >= src[i])
            minDeque.pop_back();
        minDeque.push_back(i);
    }

    std::cout << "Min in Window: " << src[minDeque.front()] << ", Max in Window: " << src[maxDeque.front()] << std::endl;

    for (int i = k; i < src.size(); ++i)
    {
        // Удаляем элементы, которые вышли за окно
        if (!maxDeque.empty() && maxDeque.front() <= i - k)
            maxDeque.pop_front();
        if (!minDeque.empty() && minDeque.front() <= i - k)
            minDeque.pop_front();

        // удаляем элементы, которые меньше (больше) того, которое мы сейчас добавим (нет смысла их хранить)
        while (!maxDeque.empty() && src[maxDeque.back()] <= src[i])
            maxDeque.pop_back();
        maxDeque.push_back(i);
        while (!minDeque.empty() && src[minDeque.back()] >= src[i])
            minDeque.pop_back();
        minDeque.push_back(i);

        std::cout << "Min in Window: " << src[minDeque.front()] << ", Max in Window: " << src[maxDeque.front()] << std::endl;
    }
}

void PrintMinMaxInMovingScopeTrue(const std::vector<int>& arr, int k)
{
    for (size_t i = 0; i < arr.size() - k; ++i)
    {
        int min = arr[i];
        int max = arr[i];
        for (size_t j = 0; j < k; ++j)
        {
            max = std::max(max, arr[i + j]);
            min = std::min(min, arr[i + j]);
        }
        std::cout << "Min in Window: " << min << ", Max in Window: " << max << std::endl;
    }
}

int main() {
    std::vector<int> arr = { 1, 6, 8, 1, 7, 11, 56, 5, 5, 2, 1, 7, 8 ,2 , 2 ,8 ,5 ,1 ,8 ,2 };
    int k = 5;

    //вывод за O(n)
    PrintMinMaxInMovingScope(arr, k);
    //вывод за O(n*k) (по определению)
    std::cout << "\nTRUE\n\n";
    PrintMinMaxInMovingScopeTrue(arr, k);

    return 0;
}