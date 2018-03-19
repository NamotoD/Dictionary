// Adjective.h
// defines class Adjective
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef ADJECTIVE_H
#pragma once
#define ADJECTIVE_H
#include "Word.h"

using namespace std;

class Adjective : public Word
{
private:
	static int totalNumberOfAdjectives;
public:
	Adjective(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfAdjectives();
	static void increaseTotalNumberOfAdjectives();
	string getDefinition();
};
#endif // !ADJECTIVE_H
