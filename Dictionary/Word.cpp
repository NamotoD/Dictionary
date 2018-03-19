// Word.cpp
// class used when parsing words into Dictinary vector
// provides accessor methods for Dictionary class
// has attributes for word, definition, and type(part 2 of the assignment)

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<string>
#include"Word.h"

using namespace std;
Word::Word() {};

Word::Word(string wordIn, string definitionIn, string typeIn)
{
	word = wordIn;
	definition = definitionIn;
	type = typeIn;
}

Word::~Word() {};

string Word::getWord()
{
	return Word::word;
}

string Word::getDefinition()
{
	return Word::definition;
}

string Word::getType()
{
	return Word::type;
}

bool Word::isPalindrome()
{
	bool isPalindrome = true;
	int left = 0, right = word.length() - 1;
	
	while ( left < right)
	{
		if (word[left] != word[right])
		{
			isPalindrome = false;
		}
		left++, right--;
	}
	return isPalindrome;

};
bool Word::isVerb()
{
	bool isVerb = false;
	if (type == "v" || type == "n_and_v")
	{
		isVerb = true;
	}
	return isVerb;
};
bool Word::isNoun()
{
	bool isNoun = false;
	if (type == "n" || type == "n_and_v")
	{
		isNoun = true;
	}
	return isNoun;
};