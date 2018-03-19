// Dictionary.cpp
// Loads dictionary and perform tasks on it, also keeps track of the number of records.
// methods implemented:
// getTotalNumberOfWords() = number of words in dictionary
// loadDictionary() = parses the dictionary into 'words' vector
// getWordDefinition() = displays the definition for a chosen word
// findWordWithMoreThanThreeZ() = displays words with more than 3 'Z'
// ListWordsWithQNotFollowedByU() = displays words containing 'Q' not followed by 'U'
// Each word takes up 4 lines in the text file(word, definition, type and a blank line separator).
// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126


#include<string>
#include<fstream>
#include<iostream>
#include "Dictionary.h"
#include "Word.h"

using namespace std;

int Dictionary::totalNumberOfWords = 0;

int Dictionary::getTotalNumberOfWords()
{
	return Dictionary::totalNumberOfWords;
}

void Dictionary::loadDictionary(string dictionaryFile) // load the dictionary words into vector 'words'
{
	cout << "Attempting to read the dictionary...\n";
	ifstream myfile(dictionaryFile);
	if (myfile.is_open())
	{
		string record;
		string word;
		string definition;
		string type;
		string emptyLine;
		while (!myfile.eof())
		{
			getline(myfile, record);
			if (record == "") // check first for two consecutive blank lines, one line is already blank since previous iteration
			{
				break;
			}
			word = record;
			getline(myfile, record);
			definition = record;
			getline(myfile, record);
			type = record;
			getline(myfile, record); // blank line record delimiter
			emptyLine = record;
			Word word(word, definition, type);
			words.push_back(word);
			Dictionary::totalNumberOfWords++;
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open dictionary";
	}

}

void Dictionary::displayWordDefinition() // print out a definition of a word user typed in, if in dictionary
{
	string wordIn;
	string definition;
	cout << "Enter the word you want a definition for: ";
	cin >> wordIn;
	for (int i = 0; i < wordIn.length(); i++) // convert all letters to lowercase by turning the value of 32 bit on
	{
		wordIn[i] |= 32;
	}
	bool found = false;
	for (Word word : Dictionary::words)
	{
		if (word.getWord() == wordIn) {
			cout << "Word exists!\n";
			cout << "Definition for " << word.getWord() << " is:\n" << word.getDefinition();
			found = true;
			break;
		}
	}
	if (!found)
	{
		cout << "There is no such a word!\n";
	}

}

void Dictionary::displayWordsWithMoreThanThreeZ() // print out words with more than three z's
{
	cout << "Words with more than three 'z''s:\n";
	char z = 'z';
	vector <Word> wordsWithThreeZ;
	for (Word word : words)
	{
		int numOfZ = 0;
		for (char letter : word.getWord())
		{
			if (letter == z)
			{
				numOfZ++;
			}
		}
		if (numOfZ > 3)
		{
			wordsWithThreeZ.push_back(word);
		}
	}

	if (!wordsWithThreeZ.empty()) // if found some results print it out
	{
		for (Word word : wordsWithThreeZ)
		{
			cout << word.getWord() << endl;
		}
	}
}

void Dictionary::displayWordsWithQNotFollowedByU() // print out words with 'q' not followed by 'u'
{
	cout << "Words that have a 'q' without a following 'u':\n";
	char q = 'q';
	char u = 'u';
	vector <Word> wordsWithQNotFollowedByU;
	for (Word word : words)
	{
		string currentWord = word.getWord();
		bool hasQ = false;
		for (char letter : currentWord)
		{
			if (hasQ && letter != u) // found the word! Q is followed by a letter that is not 'u'
			{
				wordsWithQNotFollowedByU.push_back(word);
				break;
			}
			else
			{
				letter == q ? hasQ = true : hasQ = false; //if letter is 'q' set hasQ true for next iteration, otherwise set to false in case if 'q' was followed by 'u'
			}
		}
		if (currentWord.back() == q) // found the word! 'Q' is the last letter in the word.
		{
			wordsWithQNotFollowedByU.push_back(word);
		}
	}

	if (!wordsWithQNotFollowedByU.empty()) // if found some results print it out
	{
		for (Word word : wordsWithQNotFollowedByU)
		{
			cout << word.getWord() << endl;
		}
	}

}