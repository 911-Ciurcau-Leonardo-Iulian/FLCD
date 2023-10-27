#pragma once
#include <string>

template<typename K, typename V>
class HashTable {
private:
	struct HashBucket {
		K key;
		V value;
		HashBucket* next;
	};

	static constexpr double loadFactorLimit = 0.7;
	int size = 16;
	int count = 0;
	HashBucket** buckets;

	int hash(std::string value);
	double loadFactor();
	bool loadFactorExceeded();
	void resize();

public:
	HashTable();
	void add(K key, V value);
	bool contains(K key);
	V* get(K key);
	~HashTable();
};