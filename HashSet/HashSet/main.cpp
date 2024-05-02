#include <iostream>
#include <string>
#include "HashSet.h"

struct Human {
    std::string first_name;
    std::string last_name;
};

bool operator==(Human first, Human second) {
    if (first.last_name == second.last_name && first.first_name == second.first_name)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Human& human) {
    return os << human.last_name << ' ' << human.first_name;
}

template <>
struct std::hash<Human> {
    size_t operator()(Human object) 
    {
        size_t first_hash = std::hash<std::string>{}(object.first_name);
        size_t second_hash = std::hash<std::string>{}(object.last_name);
        return first_hash ^ (second_hash << 1);
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    HashSet<Human> humans;
    humans.Add({ "Алена", "Константиновна" });
    humans.Print();
    humans.Add({ "Марк", "Жуков" });
    humans.Print();
    humans.Add({ "Кирилл", "Петров" });
    humans.Print();
    humans.Add({ "Евгений", "Захаров" });
    humans.Print();
    humans.Add({ "Николай", "Злобин" });
    humans.Print();

    std::cout << humans.Contains({ "Николай", "Злобин" });
    std::cout << humans.Contains({ "ав", "Злобин" });
    humans.Remove({ "Николай", "Злобин" });
    std::cout << humans.Contains({ "Николай", "Злобин" });
    humans.Remove({ "Николай", "Злобин" });
    humans.Remove({ "Евгений", "Захаров" });
    humans.Remove({ "Алена", "Константиновна" });
    humans.Remove({ "Николай", "Злобин" });
    humans.Print();

    HashSet<int> ints{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 1, 5, 4 };
    ints.Print();
}