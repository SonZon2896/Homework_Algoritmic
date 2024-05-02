#include <iostream>
#include <string>
#include "HashSet.h"

struct Human {
    std::string first_name;
    std::string last_name;

    Human(std::string first, std::string last) : first_name(first), last_name(last) {  };
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

#define ADD(hash_set, set_name, object) \
    std::cout << "Adding " << object << std::endl; \
    hash_set.Add(object); \
    hash_set.Print(set_name); \

#define REMOVE(hash_set, set_name, object) \
    std::cout << "Removing " << object << std::endl; \
    hash_set.Remove(object); \
    hash_set.Print(set_name);

#define CONTAINS(hash_set, set_name, object) \
    std::cout << object << " contains in " << set_name << "? - "; \
    if (hash_set.Contains(object)) \
        std::cout << "YES\n"; \
    else \
        std::cout << "NO\n"; \

int main()
{
    setlocale(LC_ALL, "Russian");

    HashSet<Human> humans{ { "Алена", "Константиновна" }, { "Марк", "Жуков" }, { "Кирилл", "Петров" } };
    humans.Print("humans");
    ADD(humans, "humans", Human("Евгений", "Захаров"))
    ADD(humans, "humans", Human("Николай", "Злобин"))

    REMOVE(humans, "humans", Human("Евгений", "Захаров"))
    REMOVE(humans, "humans", Human("Неопознанный", "Человек"))

    CONTAINS(humans, "humans", Human("Алена", "Константиновна"))
    CONTAINS(humans, "humans", Human("Евгений", "Захаров"))
    CONTAINS(humans, "humans", Human("Марк", "Жуков"))
    CONTAINS(humans, "humans", Human("Неопознанный", "Человек"))
}