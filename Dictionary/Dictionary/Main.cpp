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
		cout << "1) Get word definition" << endl;
		cout << "2) Find the word(s) with more than three 'z''s" << endl;
		cout << "3) List the words that have a 'q' without a following 'u'" << endl;
		cout << "4) Quit" << endl;
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