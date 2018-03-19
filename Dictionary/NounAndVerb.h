// NounAndVerb.h
// defines class NounAndVerb
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef NOUNANDVERB_H
#pragma once
#define NOUNANDVERB_H
#include "Noun.h"
#include "Verb.h"

class NounAndVerb : public Noun, public Verb
{
private:
	static int totalNumberOfNounAndVerbs;
public:
	NounAndVerb(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	static int getTotalNumberOfNounAndVerbs();
	static void increaseTotalNumberOfNounAndVerbs();
	string getDefinition();
};
#endif // !NOUNANDVERB_H
