// Word.h
// defines class Word
// It is a part of the Dictionary aggregate

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef WORD_H
#pragma once
#define WORD_H
#include<string>

using namespace std;

class Word
{
private:
	string word;
	string definition;
	string type;
public:
	virtual string getWord();
	virtual string getDefinition();
	string getType();
	bool isPalindrome();
	bool isVerb();
	bool isNoun();
	Word();
	Word(string wordIn, string definitionIn, string typeIn); // typeIn for second part
	virtual ~Word(); // needed to deallocate memory from the vector
};
#endif // !WORD_H

