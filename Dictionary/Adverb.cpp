// Adverb.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "Adverb.h"

using namespace std;




Adverb::Adverb(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int Adverb::totalNumberOfAdverbs = 0;

int Adverb::getTotalNumberOfAdverbs()
{
	return Adverb::totalNumberOfAdverbs;
}

void Adverb::increaseTotalNumberOfAdverbs()
{
	totalNumberOfAdverbs++;
}

string Adverb::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}