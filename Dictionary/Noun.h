// Noun.h
// defines class Noun
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef NOUN_H
#pragma once
#define NOUN_H
#include "Word.h"

class Noun : virtual public Word
{
private:
	static int totalNumberOfNouns;
public:
	Noun();
	Noun(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfNouns();
	static void increaseTotalNumberOfNouns();
	string getDefinition();
};
#endif // !NOUN_H
