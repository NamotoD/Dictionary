// Adverb.h
// defines class Adverb
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef ADVERB_H
#pragma once
#define ADVERB_H
#include "Word.h"

using namespace std;



class Adverb : public Word
{
private:
	static int totalNumberOfAdverbs;
public:
	Adverb(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfAdverbs();
	static void increaseTotalNumberOfAdverbs();
	string getDefinition();
};
#endif // !ADVERB_H
