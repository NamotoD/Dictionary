// Verb.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "Verb.h"

using namespace std;

Verb::Verb() {};

Verb::Verb(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int Verb::totalNumberOfVerbs = 0;

int Verb::getTotalNumberOfVerbs()
{
	return Verb::totalNumberOfVerbs;
}

void Verb::increaseTotalNumberOfVerbs()
{
	totalNumberOfVerbs++;
}

string Verb::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}