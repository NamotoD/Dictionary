// Noun.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "Noun.h"

using namespace std;

Noun::Noun() {};

Noun::Noun(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int Noun::totalNumberOfNouns = 0;

int Noun::getTotalNumberOfNouns()
{
	return Noun::totalNumberOfNouns;
}

void Noun::increaseTotalNumberOfNouns()
{
	totalNumberOfNouns++;
}

string Noun::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}