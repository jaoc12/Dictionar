#pragma once

#include <stdexcept>
#include "Nod.h"

template <class K, class V>
class Dictionar{
private:
	// functii interne
	Nod<K, V>* root;
	Nod<K, V>* Insert(K, V);
	void RotireDreapta(Nod<K, V>*);
	void RotireStanga(Nod<K, V>*);
	void Corectare(Nod<K, V>*, K);
	void Copy(const Nod<K, V>*);
	void Delete(Nod<K, V>*);
	ostream& Preorder(ostream&, const Nod<K, V>*) const;
	Nod<K, V>* Succesor(Nod<K, V>*);
	void BST_Remove(Nod<K, V>*);
	int getHeight(Nod<K, V>*);
	void setHeight(Nod<K, V>*);
	Nod<K, V>* Find(const K);
public:
	// constructori
	Dictionar<K, V>(const Dictionar<K, V>&);
	Dictionar<K, V>();
	~Dictionar<K, V>();
	// supraincarcare operatori
	Dictionar<K, V>& operator = (const Dictionar<K, V>&);
	V& operator [] (K) const;
	void Add(K, V);
	void Remove(K);
	// sterge toate elementele din dictionar
	void Clear();
	// cautare element
	bool InDictionary(K) const;
	bool IsEmpty() const;
	// supraincarcare afisare
	template <class T, class U>
	friend ostream& operator << (ostream& out, const Dictionar<T, U>& ob);
};

template<class K, class V>
Dictionar<K, V>::Dictionar(const Dictionar<K, V> &ob){
	// apelam functia de copiere recursiva
	Copy(ob.root);
}

template<class K, class V>
Dictionar<K, V>::Dictionar(){
	// constructor cu dictionar vid
	root = nullptr;
}

template<class K, class V>
Dictionar<K, V>::~Dictionar(){
	// apelare functie de stergere recursiva
	Delete(root);
}

template<class K, class V>
 Dictionar<K, V>& Dictionar<K, V>::operator=(const Dictionar<K, V>& ob){
	 // verificam daca obiectul este acelasi
	 if (this == &ob) {
		 return *this;
	 }
	 // stergem ce se afla in dictionar
	 Clear();
	 // apelam functia de copiere recursiva
	 Copy(ob.root);
	 return *this;
}

 template<class K, class V>
 V& Dictionar<K, V>::operator[](K k) const{
	 Nod<K, V>* curent = root;
	 // cautam nodul cu cheia data
	 while (curent != nullptr) {
		 if (k == curent->key) {
			 return curent->value;
		 }
		 if (k < curent->key) {
			 curent = curent->st;
		 }
		 if (k > curent->key) {
			 curent = curent->dr;
		 }
	 }
	 // exceptie daca este necesar
	 throw out_of_range("Cheia nu se gaseste in dictionar");
 }

 template<class K, class V>
 ostream& operator<<(ostream& out, const Dictionar<K, V>& ob){
	 // afisare radacina-stanga-dreapta recursiv
	 return ob.Preorder(out, ob.root);
 }

template<class K, class V>
Nod<K, V>* Dictionar<K, V>::Insert(K k, V v)
{
	Nod<K, V>* temp = new Nod<K, V>(k, v);
	// caz dictionar gol
	if (root == nullptr) {
		root = temp;
		return temp;
	}
	Nod<K, V>* curent = root;
	Nod<K, V>* prev = nullptr;
	while (curent != nullptr) {
		// caz in care cheia exista
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
	// legaturi intre noul nod si parintele sau
	if (k < prev->key) {
		prev->st = curent;
	}
	else {
		prev->dr = curent;
	}
	curent->parent = prev;
	// crestem inaltimea parintilor
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
	// caz in care nu rotim radacina
	// si trebuie schimbat tatal nodului rotit
	if (curent-> parent != nullptr) {
		if (curent->parent->dr == curent) {
			curent->parent->dr = fiu;
		}
		else {
			curent->parent->st = fiu;
		}
	}
	// schimbare de pozitii
	fiu->parent = curent->parent;
	curent->parent = fiu;
	if(fiuDreapta!=nullptr)
		fiuDreapta->parent = curent;
	fiu->dr = curent;
	curent->st = fiuDreapta;
	if (root == curent)
		root = fiu;
	// innoim inaltimea
	setHeight(root);
}

// analog rotire dreapta
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

// aplicam algoritmul de balansare pentru adaugare
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
void Dictionar<K, V>::Copy(const Nod<K, V>* nod_ob){
	// adaugam recursiv nodurile din obiectul copiat
	if (nod_ob != nullptr) {
		Add(nod_ob->key, nod_ob->value);
		Copy(nod_ob->st);
		Copy(nod_ob->dr);
	}

}

template<class K, class V>
void Dictionar<K, V>::Delete(Nod<K, V>* curent){
	// stergem recursiv
	if (curent != nullptr) {
		Delete(curent->st);
		Delete(curent->dr);
		delete curent;
		curent = nullptr;
	}
}

template<class K, class V>
ostream & Dictionar<K, V>::Preorder(ostream & out, const Nod<K, V>* curent) const{
	// afisare recursiva
	if (curent != nullptr) {
		out << curent->key << ":" << curent->value << endl;
		Preorder(out, curent->st);
		Preorder(out, curent->dr);
	}
	return out;
}

template<class K, class V>
Nod<K, V>* Dictionar<K, V>::Succesor(Nod<K, V>* curent){
	// cautam succesorul unui nod
	Nod<K, V>* temp = curent->dr;
	while (temp->st != nullptr) {
		temp = temp->st;
	}
	return temp;
}

// functie de eliminare dintr-un BST standard
template<class K, class V>
void Dictionar<K, V>::BST_Remove(Nod<K, V>* curent){
	// caz frunza
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
	// caz doar cu fiu stang
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
	// caz doar cu fiu drept
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
	// caz cu doi fii
	Nod<K, V>* succesor = Succesor(curent);
	// caz in care succesorul este nodul aflat in dreapta
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
	// caz in care succesorul este in stanga nodului din dreapta
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
	// functie de calculare a inaltimii unui nod in mod recursiv
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
	// functie care actualizeaza inaltimea unui subarbore
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
	// functie care adauga nod in arbore si il balanseaza dupa
	Nod<K, V>* temp = Insert(k, v);
	setHeight(root);
	Corectare(temp, k);
}

template<class K, class V>
void Dictionar<K, V>::Remove(K k){
	Nod<K, V>* temp = Find(k);
	Nod<K, V>* curent = temp->parent;
	// stergere standard
	BST_Remove(temp);
	setHeight(root);
	// mergem in sus pe arbore si il balansam
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
			// dreapta stanga
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
	// functie ce returneaza un nod dupa cheia cautata
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
	throw out_of_range("Cheia nu se gaseste in dictionar");
}

template<class K, class V>
void Dictionar<K, V>::Clear(){
	// functie de sters ce se afla in dictionar
	this->~Dictionar();
	this->root = nullptr;
}

template<class K, class V>
bool Dictionar<K, V>::InDictionary(K k) const{
	// functie ce returneaza daca un nod cu cheia k se afla in dictionar
	Nod<K, V>* curent = root;
	while (curent != nullptr) {
		if (k == curent->key) {
			return true;
		}
		if (k < curent->key) {
			curent = curent->st;
		}
		if (k > curent->key) {
			curent = curent->dr;
		}
	}
	return false;
}

template<class K, class V>
bool Dictionar<K, V>::IsEmpty() const{
	// verifica daca dictionarul este vid
	if (root == nullptr) {
		return true;
	}
	return false;
}
