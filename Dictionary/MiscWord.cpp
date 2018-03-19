// MiscWord.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "MiscWord.h"

using namespace std;

MiscWord::MiscWord(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int MiscWord::totalNumberOfMiscWords = 0;

int MiscWord::getTotalNumberOfMiscWords()
{
	return MiscWord::totalNumberOfMiscWords;
}

void MiscWord::increaseTotalNumberOfMiscWords()
{
	totalNumberOfMiscWords++;
}

string MiscWord::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}