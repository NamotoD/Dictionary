// Adjective.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "Adjective.h"

using namespace std;

Adjective::Adjective(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int Adjective::totalNumberOfAdjectives = 0;

int Adjective::getTotalNumberOfAdjectives()
{
	return Adjective::totalNumberOfAdjectives;
}

void Adjective::increaseTotalNumberOfAdjectives()
{
	totalNumberOfAdjectives++;
}

string Adjective::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}