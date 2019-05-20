#pragma once

#include "Nod.h"

template <class K, class V>
class Dictionar{
public:
	Nod<K, V>* root;
	Nod<K, V>* Insert(K, V);
	void RotireDreapta(Nod<K, V>*);
	void RotireStanga(Nod<K, V>*);
	void Corectare(Nod<K, V>*, K);
	void afisare(Nod<K, V>*);
	void Copy(const Nod<K, V>*);
	void Delete(Nod<K, V>*);
	ostream& InOrder(ostream&, const Nod<K, V>*) const;
	Nod<K, V>* Succesor(Nod<K, V>*);
	void BST_Remove(Nod<K, V>*);
	int getHeight(Nod<K, V>*);
	void setHeight(Nod<K, V>*);
public:
	Dictionar<K, V>(const Dictionar<K, V>&);
	Dictionar<K, V>();
	~Dictionar<K, V>();
	Dictionar<K, V>& operator = (const Dictionar<K, V>&);
	V& operator [] (const K) const;
	template <class T, class U>
	friend ostream& operator << (ostream& out, const Dictionar<T, U>& ob);
	void Add(K, V);
	void Remove(K);
	Nod<K, V>* Find(const K);
	void Clear();
};

template<class K, class V>
Dictionar<K, V>::Dictionar(const Dictionar<K, V> &ob){
	Copy(ob.root);
}

template<class K, class V>
Dictionar<K, V>::Dictionar(){
	root = nullptr;
}

template<class K, class V>
Dictionar<K, V>::~Dictionar(){
	Delete(root);
}

template<class K, class V>
 Dictionar<K, V>& Dictionar<K, V>::operator=(const Dictionar<K, V>& ob){
	 if (this == &ob) {
		 return *this;
	 }
	 Clear();
	 Copy(ob.root);
	 return *this;
}

 template<class K, class V>
 V& Dictionar<K, V>::operator[](const K k) const{
	 return Find(k)->value;
 }

 template<class K, class V>
 ostream& operator<<(ostream& out, const Dictionar<K, V>& ob){
	 return ob.InOrder(out, ob.root);
 }

template<class K, class V>
Nod<K, V>* Dictionar<K, V>::Insert(K k, V v)
{
	Nod<K, V>* temp = new Nod<K, V>(k, v);
	if (root == nullptr) {
		root = temp;
		return temp;
	}
	Nod<K, V>* curent = root;
	Nod<K, V>* prev = nullptr;
	while (curent != nullptr) {
		if (k == curent->key) {
			curent->value = v;
			return root;
		}
		if (k < curent->key) {
			prev = curent;
			curent = curent->st;
		}
		else {
			if (k > curent->key) {
				prev = curent;
				curent = curent->dr;
			}
		}
	}
	curent = temp;
	if (k < prev->key) {
		prev->st = curent;
	}
	else {
		prev->dr = curent;
	}
	curent->parent = prev;
	do {
		prev->height++;
		prev = prev->parent;
	} while (prev != nullptr);
	return temp;
}

template<class K, class V>
void Dictionar<K, V>::RotireDreapta(Nod<K, V>* curent){
	Nod<K, V>* fiu = curent->st;
	Nod<K, V>* fiuDreapta = fiu->dr;
	if (curent-> parent != nullptr) {
		if (curent->parent->dr == curent) {
			curent->parent->dr = fiu;
		}
		else {
			curent->parent->st = fiu;
		}
	}
	fiu->parent = curent->parent;
	curent->parent = fiu;
	if(fiuDreapta!=nullptr)
		fiuDreapta->parent = curent;
	fiu->dr = curent;
	curent->st = fiuDreapta;
	if (root == curent)
		root = fiu;
	setHeight(root);
}

template<class K, class V>
void Dictionar<K, V>::RotireStanga(Nod<K, V>* curent){
	Nod<K, V>* fiu = curent->dr;
	Nod<K, V>* fiuStanga = fiu->st;
	if (curent->parent != nullptr) {
		if (curent->parent->dr == curent) {
			curent->parent->dr = fiu;
		}
		else {
			curent->parent->st = fiu;
		}
	}
	fiu->parent = curent->parent;
	curent->parent = fiu;
	if (fiuStanga != nullptr)
		fiuStanga->parent = curent;
	fiu->st = curent;
	curent->dr = fiuStanga;
	if (root == curent)
		root = fiu;
	setHeight(root);
}

template<class K, class V>
void Dictionar<K, V>::Corectare(Nod<K, V>* curent, K k){
	while (curent != nullptr) {
		int echilibru = curent->st->Height() - curent->dr->Height();
		bool flag = false;
		// stanga stanga
		if (flag == false && echilibru > 1 && k < curent->st->key) {
			RotireDreapta(curent);
			flag = true;
		}
		// dreapta dreapta
		if (flag == false && echilibru <-1 && k>curent->dr->key) {
			RotireStanga(curent);
			flag = true;
		}
		// stanga dreapta
		if (flag == false && echilibru > 1 && k > curent->st->key) {
			RotireStanga(curent->st);
			RotireDreapta(curent);
			flag = true;
		}
		// dreapta stanga
		if (flag == false && echilibru < -1 && k < curent->dr->key) {
			RotireDreapta(curent->dr);
			RotireStanga(curent);
			flag = true;
		}
		curent = curent->parent;
	}
}

template<class K, class V>
void Dictionar<K, V>::afisare(Nod<K, V>* curent){
	if (curent != nullptr) {
		cout << curent->value << endl;
		afisare(curent->st);
		afisare(curent->dr);
	}
}

template<class K, class V>
void Dictionar<K, V>::Copy(const Nod<K, V>* nod_ob){
	if (nod_ob != nullptr) {
		Add(nod_ob->key, nod_ob->value);
		Copy(nod_ob->st);
		Copy(nod_ob->dr);
	}

}

template<class K, class V>
void Dictionar<K, V>::Delete(Nod<K, V>* curent){
	if (curent != nullptr) {
		Delete(curent->st);
		Delete(curent->dr);
		delete curent;
		curent = nullptr;
	}
}

template<class K, class V>
ostream & Dictionar<K, V>::InOrder(ostream & out, const Nod<K, V>* curent) const{
	if (curent != nullptr) {
		InOrder(out, curent->st);
		out << curent->key << ":" << curent->height << endl;
		InOrder(out, curent->dr);
	}
	return out;
}

template<class K, class V>
Nod<K, V>* Dictionar<K, V>::Succesor(Nod<K, V>* curent){
	Nod<K, V>* temp = curent->dr;
	while (temp->st != nullptr) {
		temp = temp->st;
	}
	return temp;
}

template<class K, class V>
void Dictionar<K, V>::BST_Remove(Nod<K, V>* curent){
	if (curent->st == nullptr && curent->dr == nullptr) {
		if (curent->parent->key < curent->key) {
			curent->parent->dr = nullptr;
		}
		else {
			curent->parent->st = nullptr;
		}
		delete curent;
		curent = nullptr;
		return;
	}
	if (curent->dr == nullptr) {
		if (curent != root) {
			if (curent->parent->key < curent->key) {
				curent->parent->dr = curent->st;
			}
			else {
				curent->parent->st = curent->st;
			}
		}
		else {
			root = curent->st;
		}
		curent->st->parent = curent->parent;
		setHeight(root);
		delete curent;
		curent = nullptr;
		return;

	}
	if (curent->st == nullptr) {
		if (curent != root) {
			if (curent->parent->key < curent->key) {
				curent->parent->dr = curent->dr;
			}
			else {
				curent->parent->st = curent->dr;
			}
		}
		else {
			root = curent->dr;
		}
		curent->dr->parent = curent->parent;
		setHeight(root);
		delete curent;
		curent = nullptr;
		return;
	}
	Nod<K, V>* succesor = Succesor(curent);
	if(succesor==curent->dr){
		if (curent != root) {
			if (curent->parent->key < curent->key) {
				curent->parent->dr = curent->dr;
			}
			else {
				curent->parent->st = curent->dr;
			}
		}
		else {
			root = curent->dr;
		}
		curent->dr->parent = curent->parent;
		if (curent->st != nullptr) {
			curent->st->parent = curent->dr;
		}
		curent->dr->st = curent->st;
		setHeight(root);
		delete curent;
		curent = nullptr;
		return;
	}
	if (curent != root) {
		if (curent->parent->key < curent->key) {
			curent->parent->dr = succesor;
		}
		else {
			curent->parent->st = succesor;
		}
	}
	else {
		root = succesor;
	}
	if (succesor->dr != nullptr) {
		succesor->dr->parent = succesor->parent;
		succesor->parent->st = succesor->dr;
	}
	succesor->parent->st = nullptr;
	succesor->parent = curent->parent;
	curent->st->parent = succesor;
	curent->dr->parent = succesor;
	succesor->st = curent->st;
	succesor->dr = curent->dr;
	setHeight(root);
	delete curent;
	curent = nullptr;
	return;
}

template<class K, class V>
int Dictionar<K, V>::getHeight(Nod<K, V>* curent){
	if (curent == nullptr) {
		return 0;
	}
	if (curent->st == nullptr&&curent->dr == nullptr) {
		return 1;
	}
	return max(getHeight(curent->st), getHeight(curent->dr)) + 1;
}

template<class K, class V>
void Dictionar<K, V>::setHeight(Nod<K, V>* curent) {
	if (curent == nullptr){
		return;
	}
	if (curent->st != nullptr) {
		setHeight(curent->st);
	}
	if (curent->dr != nullptr) {
		setHeight(curent->dr);
	}
	curent->height=getHeight(curent);
}

template<class K, class V>
void Dictionar<K, V>::Add(K k, V v){
	Nod<K, V>* temp = Insert(k, v);
	setHeight(root);
	Corectare(temp, k);
}

template<class K, class V>
void Dictionar<K, V>::Remove(K k){
	Nod<K, V>* temp = Find(k);
	Nod<K, V>* curent = temp->parent;
	BST_Remove(temp);
	setHeight(root);
	while (curent != nullptr) {
		int echilibru = curent->st->Height() - curent->dr->Height();
		if (echilibru > 1) {
			// stanga stanga
			if (curent->st->st->Height() - curent->st->dr->Height() >= 0) {
				RotireDreapta(curent);
			}
			// stanga dreapta
			else {
				RotireStanga(curent->st);
				RotireDreapta(curent);
			}
		}
		if (echilibru < -1) {
			// dreapta dreapta
			if (curent->dr->st->Height() - curent->dr->dr->Height() <= 0) {
				RotireStanga(curent);
			}
			else {
				RotireDreapta(curent->dr);
				RotireStanga(curent);
			}
		}
		curent = curent->parent;
	}
}

template<class K, class V>
Nod<K, V>* Dictionar<K, V>::Find(const K k){
	Nod<K, V>* curent = root;
	while (curent != nullptr) {
		if (k == curent->key) {
			return curent;
		}
		if (k < curent->key) {
			curent = curent->st;
		}
		if (k > curent->key) {
			curent = curent->dr;
		}
	}
	// De facut exceptie
}

template<class K, class V>
void Dictionar<K, V>::Clear(){
	this->~Dictionar();
	this->root = nullptr;
}
