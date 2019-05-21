// Dictionar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Dictionar.h"
#include <cassert>
int main()
{
	Dictionar<int, int> I;
	assert(I.IsEmpty() == true);
	I.Add(5, 9);
	I.Add(9, 5);
	assert(I.InDictionary(9) == true);
	I.Add(2, 7);
	cout << I << endl;
	I.Add(9, 3);
	cout << "Se schimba valoarea din cheia 9" << endl;
	cout << I << endl;
	I.Remove(9);
	cout << "Eliminat nodul cu cheia 9" << endl;
	cout << I << endl;
	I.Clear();
	assert(I.IsEmpty() == true);
	Dictionar<float, int> F;
	assert(F.IsEmpty() == true);
	F.Add(5.2, 2);
	F.Add(4.2, 2);
	F.Add(3.0, 3);
	cout << "Dictionarul este balansat" << endl;
	cout << F << endl;
	Dictionar<float, int> H;
	H = F;
	cout << "Operator de atribuire" << endl;
	cout << H << endl;
	assert(H[4.2] == 2);
	Dictionar<string, int> S;
	S.Add("a", 1);
	S.Add("aa", 2);
	S.Add("c", 3);
	cout << S << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

