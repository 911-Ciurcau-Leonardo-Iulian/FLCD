#include "HashTable.h"

template<typename K, typename V>
HashTable<K, V>::HashTable()
{
	buckets = new HashBucket*[size];
	for (int i = 0; i < size; i++)
	{
		buckets[i] = nullptr;
	}
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	for (int i = 0; i < size; i++)
	{
		HashBucket* current = buckets[i];
		while (current)
		{
			HashBucket* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] buckets;
}

template<typename K, typename V>
int HashTable<K, V>::hash(std::string value)
{
	int result = 0;
	for (auto& c : value)
	{
		result += c % size;
	}
	result %= size;

	return result;
}

template<typename K, typename V>
double HashTable<K, V>::loadFactor()
{
	return (double)count / (double)size;
}

template<typename K, typename V>
bool HashTable<K, V>::loadFactorExceeded()
{
	return loadFactor() > loadFactorLimit;
}

template<typename K, typename V>
void HashTable<K, V>::add(K key, V value)
{
	int hashVal = hash(key);
	if (buckets[hashVal] == nullptr)
	{
		buckets[hashVal] = new HashBucket{ key, value, nullptr };
		count++;
	}
	else
	{
		HashBucket* current = buckets[hashVal];
		while (current->next)
		{
			current = current->next;
		}
		current->next = new HashBucket{ key, value, nullptr };
		count++;
	}

	if (loadFactorExceeded())
	{
		resize();
	}
}

template<typename K, typename V>
void HashTable<K, V>::resize()
{
	HashBucket** oldBuckets = buckets;
	buckets = new HashBucket*[size * 2];

	int oldSize = size;
	size *= 2;
	count = 0;

	for (int i = 0; i < size; i++)
	{
		buckets[i] = nullptr;
	}

	for (int i = 0; i < oldSize; i++)
	{
		HashBucket* current = oldBuckets[i];
		while (current)
		{
			add(current->key, current->value);
			HashBucket* oldCurrent = current;
			current = current->next;
			delete oldCurrent;
		}
	}

	delete[] oldBuckets;
}

template<typename K, typename V>
std::pair<int, int> HashTable<K, V>::getPosition(K key)
{
	int hashValue = hash(key);
	int pos1 = hashValue;
	if (buckets[hashValue] != nullptr)
	{
		HashBucket* current = buckets[hashValue];
		int pos2 = 0;
		while (current)
		{
			if (current->key == key)
			{
				return std::pair<int, int>{pos1, pos2};
			}
			pos2++;
			current = current->next;
		}
	}

	return std::pair<int, int>{-1, -1};
}

template<typename K, typename V>
bool HashTable<K, V>::contains(K key)
{
	int hashValue = hash(key);
	if (buckets[hashValue] != nullptr)
	{
		HashBucket* current = buckets[hashValue];
		while (current)
		{
			if (current->key == key)
			{
				return true;
			}
			current = current->next;
		}
	}

	return false;
}