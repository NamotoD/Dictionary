// ProperNoun.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include "ProperNoun.h"

using namespace std;

ProperNoun::ProperNoun(string wordIn, string definitionIn, string typeIn)
	: Word(wordIn, definitionIn, typeIn) {
}

int ProperNoun::totalNumberOfProperNouns = 0;

int ProperNoun::getTotalNumberOfProperNouns()
{
	return ProperNoun::totalNumberOfProperNouns;
}

void ProperNoun::increaseTotalNumberOfProperNouns()
{
	totalNumberOfProperNouns++;
}

string ProperNoun::getWord()
{
	string word = Word::getWord();
	word[0] = toupper(word[0]);
	return word;
}

string ProperNoun::getDefinition()
{
	string definition = "(";
	definition += Word::getType();
	definition += ".) ";
	definition += Word::getDefinition();
	return definition;
}