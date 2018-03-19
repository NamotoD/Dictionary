// Main.cpp
// Dictionary main program
// Loads dictionary words from a text file in the form:
// word
// definition
// type [either verb, noun, adverb, adjsective, preposition, proper noun, noundAndVerb or other]
// Lets the user to choose from set of tasks to be executed

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include<iostream>
#include "Dictionary.h"

using namespace std;

int main()
{
	Dictionary dictionary;
	dictionary.loadDictionary("dictionary.txt");
	cout << "There are " << dictionary.getTotalNumberOfWords() << " words in the dictionary." << endl;
	bool exitProgram = false;
	while (!exitProgram) // The main loop showing menu options to the user
	{
		int choice;
		cout << "\n\nChoose a task to perform: " << endl;
		cout << "BASIC TASKS" << endl;
		cout << "1) Get word definition" << endl;
		cout << "2) Find the word(s) with more than three 'z''s" << endl;
		cout << "3) List the words that have a 'q' without a following 'u'" << endl;
		cout << "4) List the words that are a noun and a verb" << endl;
		cout << "5) List the words that are palindromes" << endl;
		cout << "INTERMEIDATE TASKS" << endl;
		cout << "6) Get anagrams of a word" << endl;
		cout << "7) Play guessing game" << endl;
		cout << "ADVANCED TASKS" << endl;
		cout << "8) Fun with Tri-Grams" << endl;
		cout << "9) Editable dictionary" << endl;
		cout << "10) Quit" << endl;
		cout << "\nYour choice: ";
		cin >> choice;
		// ref: http://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
		if (!cin)// if not an integer
		{
			cout << "Input must be an integer!" << endl;    
			cin.clear(); // reset failbit
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input
		}
		// end of ref
		else
		{
			switch (choice) // Decide on action based on choice input
			{
			case 1:
				dictionary.displayWordDefinition();
				break;
			case 2:
				dictionary.displayWordsWithMoreThanThreeZ();
				break;
			case 3:
				dictionary.displayWordsWithQNotFollowedByU();
				break;
			case 4:
				dictionary.displayWordsThatAreNounAndVerb();
				break;
			case 5:
				dictionary.displayPalindromes();
				break;
			case 6:
				dictionary.displayAnagrams();
				break;
			case 7:
				dictionary.guessingGame();
				break;
			case 8:
				dictionary.trigrams();
				break;
			case 9:
				dictionary.editableDictionary();
				break;
			case 10:
				exitProgram = true;
				break;
			default:
				cout << "Invalid choice! Enter an integer between 1 and 4!" << endl;
				break;
			}
		}
	}
	return 0;
}