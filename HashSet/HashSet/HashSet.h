#pragma once
#include <unordered_set>
#include <list>
#include <vector>

#define START_SIZE 4

template<typename T>
class HashSet
{
private:
	std::vector<std::list<T>> data;
	size_t size_contains;

	size_t GetHash(T object);
	void Rebuild(size_t new_size);

public:
	HashSet();
	HashSet(std::initializer_list<T> objects);

	void Add(T object);
	bool Contains(T object);
	void Remove(T object);
	void Print();
	void Print(std::string hash_name);
};

template<typename T>
inline size_t HashSet<T>::GetHash(T object)
{
	size_t hash = std::hash<T>{}(object);
	size_t number = hash % data.size();
	return number;
}

template<typename T>
inline void HashSet<T>::Rebuild(size_t new_size)
{
	std::vector<std::list<T>> old_data = data;
	data.clear();
	data.resize(new_size);
	for (auto list : old_data)
		for (auto value : list)
			data[GetHash(value)].push_back(value);
}

template<typename T>
inline HashSet<T>::HashSet()
{
	data.resize(START_SIZE);
	size_contains = 0;
}

template<typename T>
inline HashSet<T>::HashSet(std::initializer_list<T> objects)
{
	data.resize(START_SIZE);
	size_contains = 0;
	for (auto object : objects)
		Add(object);
}

template<typename T>
inline void HashSet<T>::Add(T object)
{
	if (Contains(object))
		return;
	if (size_contains >= data.size())
		Rebuild(data.size() * 2);
	data[GetHash(object)].push_back(object);
	++size_contains;
}

template<typename T>
inline bool HashSet<T>::Contains(T object)
{
	for (auto value : data[GetHash(object)])
		if (value == object)
			return true;
	return false;
}

template<typename T>
inline void HashSet<T>::Remove(T object)
{
	if (!Contains(object))
		return;
	data[GetHash(object)].remove(object);
	--size_contains;
}

template<typename T>
inline void HashSet<T>::Print()
{
	std::cout << "HashSet {\n\tSize: " << data.size() << "\n\tContains: " << size_contains << "\n\tValues:\n";
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::cout << "\t\t" << i << " bucket: ";
		for (auto value : data[i])
			std::cout << value << ", ";
		std::cout << '\n';
	}
	std::cout << "\n}" << std::endl;
}

template<typename T>
inline void HashSet<T>::Print(std::string hash_name)
{
	std::cout << "HashSet \"" << hash_name << "\" {\n\tSize: " << data.size() << "\n\tContains: " << size_contains << "\n\tValues:\n";
	for (size_t i = 0; i < data.size(); ++i)
	{
		std::cout << "\t\t" << i << " bucket: ";
		for (auto value : data[i])
			std::cout << value << ", ";
		std::cout << '\n';
	}
	std::cout << "\n}" << std::endl;
}