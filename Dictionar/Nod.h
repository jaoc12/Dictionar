#pragma once

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

template <class K, class V>
class Nod{
private:
	Nod<K, V> *st, *dr, *parent;
	int height;
	K key;
	V value;
	Nod();
	Nod(K, V);
	int Height();
	template <typename, typename> friend class Dictionar;
};

template<class K, class V>
Nod<K, V>::Nod(): st(nullptr), dr(nullptr), parent(nullptr){}

template<class K, class V>
Nod<K, V>::Nod(K k, V v): key(k), value(v), st(nullptr), dr(nullptr), height(1), parent(nullptr) {}

template<class K, class V>
int Nod<K, V>::Height()
{
	if (this == nullptr)
		return 0;
	return height;
}

