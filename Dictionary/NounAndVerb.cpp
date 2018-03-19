// NounAndVerb.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "NounAndVerb.h"
#include "Noun.h"

using namespace std;

NounAndVerb::NounAndVerb(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int NounAndVerb::totalNumberOfNounAndVerbs = 0;

int NounAndVerb::getTotalNumberOfNounAndVerbs()
{
	return NounAndVerb::totalNumberOfNounAndVerbs;
}

void NounAndVerb::increaseTotalNumberOfNounAndVerbs()
{
	totalNumberOfNounAndVerbs++;
}

string NounAndVerb::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}