// Preposition.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "Preposition.h"
#include "MiscWord.h"

using namespace std;

Preposition::Preposition(string wordIn, string definitionIn, string typeIn)
	: MiscWord(wordIn, definitionIn, typeIn) {
}

int Preposition::totalNumberOfPrepositions = 0;

int Preposition::getTotalNumberOfPrepositions()
{
	return Preposition::totalNumberOfPrepositions;
}

void Preposition::increaseTotalNumberOfPrepositions()
{
	totalNumberOfPrepositions++;
}

string Preposition::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}