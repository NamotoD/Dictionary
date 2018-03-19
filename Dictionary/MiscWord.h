// MiscWord.h
// defines class MiscWord
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef MISCWORD_H
#pragma once
#define MISCWORD_H
#include "Word.h"

using namespace std;


class MiscWord : public Word
{
private:
	static int totalNumberOfMiscWords;
public:
	MiscWord(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfMiscWords();
	static void increaseTotalNumberOfMiscWords();
	string getDefinition();
};
#endif // !MISCWORD_H
