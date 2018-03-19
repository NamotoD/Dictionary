// Preposition.h
// defines class Preposition
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef PREPOSIITON_H
#pragma once
#define PREPOSIITON_H
#include "Word.h"
#include "MiscWord.h"

using namespace std;

class Preposition : public MiscWord
{
private:
	static int totalNumberOfPrepositions;
public:
	Preposition(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfPrepositions();
	static void increaseTotalNumberOfPrepositions();
	string getDefinition();
};
#endif // !PREPOSIITON_H
