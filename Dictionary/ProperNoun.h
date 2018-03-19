// ProperNoun.h
// defines class ProperNoun
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef PROPERNOUN_H
#pragma once
#define PROPERNOUN_H
#include "Noun.h"

class ProperNoun : public Noun
{
private:
	static int totalNumberOfProperNouns;
public:
	ProperNoun(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfProperNouns();
	static void increaseTotalNumberOfProperNouns();
	string getWord();
	string getDefinition();
};
#endif // !PROPERNOUN_H
