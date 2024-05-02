#pragma once
#include <unordered_set>
#include <list>
#include <vector>
#include <iterator>

#define START_SIZE 4

template<typename T>
class HashSet
{
private:
	std::vector<std::list<typename std::list<T>::iterator>> hash_table;
	std::list<T> data;
	size_t size_contains;

	size_t GetHash(T object);
	void Rebuild(size_t new_size);

public:
	HashSet();
	HashSet(std::initializer_list<T> objects);

	void Add(T object);
	bool Contains(T object);
	void Remove(T object);
	void Print() const;
	void Print(std::string hash_name) const;

	const std::list<T>* const GetOrder() const { return data; }
};

template<typename T>
inline size_t HashSet<T>::GetHash(T object)
{
	size_t hash = std::hash<T>{}(object);
	size_t number = hash % hash_table.size();
	return number;
}

template<typename T>
inline void HashSet<T>::Rebuild(size_t new_size)
{
	auto old_table = hash_table;
	hash_table.clear();
	hash_table.resize(new_size);
	for (auto list : old_table)
		for (auto value : list)
			hash_table[GetHash(*value)].push_back(value);
}

template<typename T>
inline HashSet<T>::HashSet()
{
	hash_table.resize(START_SIZE);
	size_contains = 0;
}

template<typename T>
inline HashSet<T>::HashSet(std::initializer_list<T> objects)
{
	hash_table.resize(START_SIZE);
	size_contains = 0;
	for (auto object : objects)
		Add(object);
}

template<typename T>
inline void HashSet<T>::Add(T object)
{
	if (Contains(object))
		return;
	if (size_contains >= hash_table.size())
		Rebuild(data.size() * 2);
	data.push_back(object);
	hash_table[GetHash(object)].push_back(--data.end());
	++size_contains;
}

template<typename T>
inline bool HashSet<T>::Contains(T object)
{
	for (auto value : hash_table[GetHash(object)])
		if (*value == object)
			return true;
	return false;
}

template<typename T>
inline void HashSet<T>::Remove(T object)
{
	if (!Contains(object))
		return;
	size_t hash = GetHash(object);
	for (auto value : hash_table[hash])
		if (*value == object) 
		{
			hash_table[hash].remove(value);
			data.erase(value);
			--size_contains;
			return;
		}
}

template<typename T>
inline void HashSet<T>::Print() const
{
	Print("");
}

template<typename T>
inline void HashSet<T>::Print(std::string hash_name) const
{
	std::cout << "HashSet ";
	if (hash_name != "")
		std::cout << '"' << hash_name << '"';
	std::cout << " {\n\tSize: " << data.size() << "\n\tContains: " << size_contains << "\n\tValues:\n";
	for (size_t i = 0; i < hash_table.size(); ++i)
	{
		std::cout << "\t\t" << i + 1 << " bucket: ";
		for (auto value : hash_table[i])
			std::cout << *value << ", ";
		std::cout << '\n';
	}
	std::cout << "\tOrder:\t";
	for (auto value : data)
		std::cout << value << ", ";
	std::cout << "\n}" << std::endl;
}