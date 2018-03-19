// Dictionary.h
// defines class Dictionary

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef DICTIONARY_H
#pragma once
#define DICTIONARY_H
#include<vector>
#include "Word.h"

using namespace std;

class Dictionary
{
private:
	static int totalNumberOfWords;
	vector<Word> words;
public:
	int getTotalNumberOfWords();
	void loadDictionary(string dictionaryFile);
	void displayWordDefinition();
	void displayWordsWithMoreThanThreeZ();
	void displayWordsWithQNotFollowedByU();
};
#endif // !DICTIONARY_H