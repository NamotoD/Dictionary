// Word.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class
// has attributes for word, definition, and type(part 2 of the assignment)

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include"Word.h"

using namespace std;

Word::Word(string wordIn, string definitionIn, string typeIn)
{
	word = wordIn;
	definition = definitionIn;
}

string Word::getWord()
{
	return Word::word;
}

string Word::getDefinition()
{
	return Word::definition;
}