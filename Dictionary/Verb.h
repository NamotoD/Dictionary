// Verb.h
// defines class Verb
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef VERB_H
#pragma once
#define VERB_H
#include "Word.h"

class Verb : virtual public Word
{
private:
	static int totalNumberOfVerbs;
public:
	Verb();
	Verb(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfVerbs();
	static void increaseTotalNumberOfVerbs();
	string getDefinition();
};
#endif // !VERB_H
