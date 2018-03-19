// Dictionary.cpp
// Loads dictionary and perform tasks on it, also keeps track of the number of records.
// methods implemented:
// getTotalNumberOfWords() = number of words in dictionary
// loadDictionary() = parses the dictionary into 'words' vector
// getWordDefinition() = displays the definition for a chosen word
// findWordWithMoreThanThreeZ() = displays words with more than 3 'Z'
// ListWordsWithQNotFollowedByU() = displays words containing 'Q' not followed by 'U'
// displayWordsThatAreNounAndVerb() = Displays words tha re noun sand verbs
// displayPalindromes() = displays words that are spelled backwards the same as forwards
// displayAnagrams() = displays words created by rearranging the letters in a word provided by a user
// guessingGame() = shows a word definition and let the user to have three guesses what the word is, hints are provided after unsuccesful guesses
// trigrams() = calculates the most likely to folloe letter, also shows randomly generated words
// editableDictionary() = allows the user to add, delete and edit the dictionary file
// Each word takes up 4 lines in the text file(word, definition, type and a blank line separator).
// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126


#include<string>
#include<fstream>
#include<iostream>
#include "Dictionary.h" // inherits from Word
#include "NounAndVerb.h" // inherits from Noun and Verb
#include "ProperNoun.h"  // inherits from Noun
#include "Adverb.h" // inherits from Word
#include "Adjective.h" // inherits from Word
#include "Preposition.h"  // inherits from Misc
#include<algorithm>
#include<random>
#include "Trigrams.h"
#include<thread>
#include<vector>
#include<mutex>

using namespace std; 
//ref: https://stackoverflow.com/questions/13084236/function-to-remove-spaces-from-string-char-array-in-c
char* deblank(char* input)
{
	int i, j;
	char *output = input;
	for (i = 0, j = 0; i<strlen(input); i++, j++)
	{
		if (input[i] != ' ')
			output[j] = input[i];
		else
			j--;
	}
	output[j] = 0;
	return output;
}
// end of ref

static mutex barrier;

Dictionary::~Dictionary()
{
	for (int i = 0; i < words.size(); ++i) // free the allocated memory in words vector
	{
		delete words[i];
	}	
	words.clear();
}

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
			if (type == "v")
			{
				Verb *wordIn = new Verb(word, definition, type);
				words.push_back(wordIn);
				Verb::increaseTotalNumberOfVerbs();
			}
			if (type == "n")
			{
				Noun *wordIn = new Noun(word, definition, type);
				words.push_back(wordIn);
				Noun::increaseTotalNumberOfNouns();
			}
			if (type == "adv")
			{
				Adverb *wordIn = new Adverb(word, definition, type);
				words.push_back(wordIn);
				Adverb::increaseTotalNumberOfAdverbs();
			}
			if (type == "adj")
			{
				Adjective *wordIn = new Adjective(word, definition, type);
				words.push_back(wordIn);
				Adjective::increaseTotalNumberOfAdjectives();
			}
			if (type == "misc")
			{
				MiscWord *wordIn = new MiscWord(word, definition, type);
				words.push_back(wordIn);
				MiscWord::increaseTotalNumberOfMiscWords();
			}
			if (type == "prep")
			{
				Preposition *wordIn = new Preposition(word, definition, type);
				words.push_back(wordIn);
				Preposition::increaseTotalNumberOfPrepositions();
			}
			if (type == "pn")
			{
				ProperNoun *wordIn = new ProperNoun(word, definition, type);
				words.push_back(wordIn);
				ProperNoun::increaseTotalNumberOfProperNouns();
			}
			if (type == "n_and_v")
			{
				NounAndVerb *wordIn = new NounAndVerb(word, definition, type);
				words.push_back(wordIn);
				NounAndVerb::increaseTotalNumberOfNounAndVerbs();
			}
			Dictionary::totalNumberOfWords++;
		}
		cout << "Number of nouns:\t\t" << Noun::getTotalNumberOfNouns() << endl;
		cout << "Number of verbs:\t\t" << Verb::getTotalNumberOfVerbs() << endl;
		cout << "Number of adverbs:\t\t" << Adverb::getTotalNumberOfAdverbs() << endl;
		cout << "Number of adjectives:\t\t" << Adjective::getTotalNumberOfAdjectives() << endl;
		cout << "Number of miscellaneous:\t" << MiscWord::getTotalNumberOfMiscWords() << endl;
		cout << "Number of prepositions:\t\t" << Preposition::getTotalNumberOfPrepositions() << endl;
		cout << "Number of proper nouns:\t\t" << ProperNoun::getTotalNumberOfProperNouns() << endl;
		cout << "Number of nouns and verbs:\t" << NounAndVerb::getTotalNumberOfNounAndVerbs() << endl;
		cout << "The accumulated total is:\t" << (Noun::getTotalNumberOfNouns() + Verb::getTotalNumberOfVerbs() + Adverb::getTotalNumberOfAdverbs() + Adjective::getTotalNumberOfAdjectives() + MiscWord::getTotalNumberOfMiscWords() + Preposition::getTotalNumberOfPrepositions() + ProperNoun::getTotalNumberOfProperNouns() + NounAndVerb::getTotalNumberOfNounAndVerbs()) << endl;
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
	for (Word *word : Dictionary::words)
	{
		string currentWord = (*word).getWord();
		currentWord[0] = tolower(currentWord[0]);
		if (currentWord == wordIn) {
			cout << "Word exists!\n";
			cout << "Definition for " << (*word).getWord() << " is:\n" << (*word).getDefinition();
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
	vector <Word*> wordsWithThreeZ;
	for (Word *word : words)
	{
		int numOfZ = 0;
		for (char letter : (*word).getWord())
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
		for (Word *word : wordsWithThreeZ)
		{
			cout << (*word).getWord() << endl;
		}
	}
}

void Dictionary::displayWordsWithQNotFollowedByU() // print out words with 'q' not followed by 'u'
{
	cout << "Words that have a 'q' without a following 'u':\n";
	char q = 'q';
	char u = 'u';
	vector <Word*> wordsWithQNotFollowedByU;
	for (Word *word : words)
	{
		string currentWord = (*word).getWord();
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
		for (Word *word : wordsWithQNotFollowedByU)
		{
			cout << (*word).getWord() << endl;
		}
	}

}

void Dictionary::displayWordsThatAreNounAndVerb() // print out words with that are noun and a verb
{
	cout << "Words that are noun and a verb";
	vector <Word*> displayWordsThatAreNounAndVerb;
	int numberOfNounsAndVerbs = 0;
	for (Word *word : words)
	{
		if ((*word).isVerb() && (*word).isNoun()) // found the word! It is a noun and a verb
		{
			displayWordsThatAreNounAndVerb.push_back(word);
			numberOfNounsAndVerbs++;
		}
	}

	cout << "\nThere are " << numberOfNounsAndVerbs << " words that are noun and a verb" << endl;

	if (!displayWordsThatAreNounAndVerb.empty()) // if found some results print it out
	{
		for (Word *word : displayWordsThatAreNounAndVerb)
		{
			cout << (*word).getWord() << endl;
		}
	}

}

void Dictionary::displayPalindromes()
{
	cout << "\nWords that are palindromes";
	vector <Word*> displayPalindromes;
	int numberOfPalindromes = 0;
	for (Word *word : words)
	{
		if ((*word).isPalindrome()) // found the word!
		{
			displayPalindromes.push_back(word);
			numberOfPalindromes++;
		}
	}

	cout << "There are " << numberOfPalindromes << " palindromes in the dictionary." << endl;

	if (!displayPalindromes.empty()) // if found some results print it out
	{
		for (Word *word : displayPalindromes)
		{
			cout << (*word).getWord() << endl;
		}
	}
}

void Dictionary::displayAnagrams()
{
	string wordIn;
	string definition;
	vector <Word*> displayAnagrams;
	cin.ignore();
	cout << "Enter the word you wish to find anagrams for: ";
	getline(cin, wordIn);
	string wordInNoSpaces = wordIn;
	wordInNoSpaces.erase(remove(wordInNoSpaces.begin(), wordInNoSpaces.end(), ' '), wordInNoSpaces.end()); // remove all blank spaces
	//cout << "wordInNoSpaces: " << wordInNoSpaces << endl;
	string wordInToLower = wordInNoSpaces;
	for (int i = 0; i < wordInToLower.length(); i++) // convert all letters to lowercase by turning the value of 32 bit on
	{
		wordInToLower[i] |= 32;
	}
	string sortedWordIn = wordInToLower;
	sort(sortedWordIn.begin(), sortedWordIn.end());
	bool found = false;
	for (Word *word : Dictionary::words)
	{
		string currentWord = (*word).getWord();
		string currentWordToLower = currentWord;
		currentWordToLower[0] = tolower(currentWordToLower[0]);
		string sortedWord = currentWordToLower;
		sort(sortedWord.begin(), sortedWord.end());
		if (sortedWord == sortedWordIn && wordInToLower != currentWordToLower) {
			//cout << "WordIn: " << wordIn << endl;
			//cout << "wordInNoSpaces: " << wordInNoSpaces << endl;
			//cout << "wordInToLower: " << wordInToLower << endl;
			//cout << "sortedWordIn: " << sortedWordIn << endl;
			//cout << "currentWord: " << currentWord << endl;
			//cout << "currentWordToLower: " << currentWordToLower << endl;
			//cout << "sortedWord: " << sortedWord << endl;

			displayAnagrams.push_back(word);
			found = true;
		}
	}

	if (found)
	{
		cout << "Word exists!\n";
		cout << "These are anagrams of " << wordIn << ":" << endl;;
		for (Word *word : displayAnagrams)
		{
			cout << (*word).getWord() << endl;
		}
	}
	else
	{
		cout << "There is no such a word!\n";
	}
}

void Dictionary::guessingGame()
{
	bool anotherGuess = true;
	while (anotherGuess)
	{
		vector <Word*> Nouns;
		int numberOfNouns = 0;
		for (Word *word : words)
		{
			if ((*word).isNoun()) // found the word! It is a noun and a verb
			{
				Nouns.push_back(word);
				numberOfNouns++;
			}
		}

		// ref: http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, (int)Nouns.size() - 1); // guaranteed unbiased
		auto random_integer = uni(rng);
		// end of ref
		Word randomNoun = (*Nouns.at(random_integer));
		string guess;
		int remainingLettersInWord = randomNoun.getWord().length();
		int numberOfGuesses = 3;


		while (numberOfGuesses > 0 && remainingLettersInWord > 0)
		{
			cout << "\nThe definition for a random word is:\n\n";
			cout << randomNoun.getDefinition() << "\n\n";
			cout << "The length of the word to guess is " << randomNoun.getWord().length() << " letters.\n\n";
			cout << "Try to guess the corect word: ";
			cin >> guess;
			if (guess == randomNoun.getWord())
			{
				cout << "Correct guess!";
				numberOfGuesses = 0;
				cout << "\nPlay again? Press '1' to continue, anything else to leave the game: ";
				cin >> anotherGuess;
				if (!cin)// if not an integer
				{
					anotherGuess = 0;
				}
			}
			else
			{
				cout << "Wrong guess!\n";
				numberOfGuesses--;
				remainingLettersInWord--;
				if (remainingLettersInWord > 0)
				{
					if (numberOfGuesses == 2)
					{
						cout << "Hint: The first letter of the word is '" << randomNoun.getWord()[0] << string(randomNoun.getWord().length() - 1, '-') << "'" << endl;
					}
					else if (numberOfGuesses == 1)
					{
						cout << "Hint: The first two letters of the word are '" << randomNoun.getWord()[0] << randomNoun.getWord()[1] << string(randomNoun.getWord().length() - 2, '-') << "'" << endl;
					}
					else
					{
						cout << "You lost!!";
						cout << "The correct word was " << randomNoun.getWord();
						cout << "\nPlay again? Press '1' to continue, anything else to leave the game: ";
						cin >> anotherGuess;
						if (!cin)// if not an integer
						{
							anotherGuess = 0;
						}
					}
				}
				else
				{
					cout << "No more hints available!!\n";
					cout << "The correct word was " << randomNoun.getWord();
				}
			}
		}
	}
}

void Dictionary::trigrams()
{
	Trigrams trigram;
	trigram.calculateProbabilities();

	string twoLetters;
	cout << "Enter two letters and press enter: ";
	cin >> twoLetters;
	trigram.displayResults(twoLetters);
	
}

void Dictionary::editableDictionary()
{
	Dictionary dictionary;
	bool leaveEditableDictionary = false;
	while (!leaveEditableDictionary) // The main loop showing menu options to the user
	{
		int choice;
		cout << "\n\nChoose an action to perform: " << endl;
		cout << "1) Add a word" << endl;
		cout << "2) Edit a word" << endl;
		cout << "3) Delete a word" << endl;
		cout << "4) Leave editable dictionary" << endl;
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
				dictionary.addWord();
				break;
			case 2:
				dictionary.editWord();
				break;
			case 3:
				dictionary.deleteWord();
				break;
			case 4:
				leaveEditableDictionary = true;
				break;
			default:
				cout << "Invalid choice! Enter an integer between 1 and 4!" << endl;
				break;
			}
		}
	}
}

void Dictionary::addWord()
{
	thread t3(&Dictionary::saveAddFile, this);
	t3.join();
};

void Dictionary::saveAddFile()
{
	const int newWordSize = 46, newDefinitionSize = 6015, newTypeSize = 8;
	string wordToInsert, n_and_v = "n_and_v", adv = "adv", adj = "adj", prep = "prep", pn = "pn", misc = "misc";
	char newWord[newWordSize], newDefinition[newDefinitionSize], newType[newTypeSize];
	const char * nAndV = n_and_v.c_str(), *Adv = adv.c_str(), *Adj = adj.c_str(), *Prep = prep.c_str(), *Pn = pn.c_str(), *Misc = misc.c_str();

	cin.ignore(100, '\n'); // ignore characters left in cin
	cout << "Type in a word: ";
	cin.get(newWord, newWordSize);
	deblank(newWord);
	cin.ignore(46, '\n');
	cout << "Type in a word definintion: ";
	cin.get(newDefinition, newDefinitionSize);
	cin.ignore(6015, '\n');
	cout << "Type in a word type: ";
	cin.get(newType, newTypeSize);

	while (*newType != 'v' && *newType != 'n' && *newType != *Adv && *newType != *Adj && *newType != *Prep &&
		*newType != *Pn && *newType != *nAndV && *newType != *Misc)
	{
		cin.ignore(8, '\n');
		cout << "You have typed in a wrong type the only allowed types are 'v', 'n', 'adv', 'adj', 'prep', 'pn', 'n_and_v' and 'misc'!\n";
		cout << "Type in a correct word type: ";
		cin.get(newType, newTypeSize);

	}
	cin.ignore(8, '\n');
	wordToInsert += newWord;
	wordToInsert += "\n";
	wordToInsert += newDefinition;
	if (wordToInsert.back() != '.')
	{
		wordToInsert += '.';
	}
	wordToInsert += "\n";
	wordToInsert += newType;
	wordToInsert += "\n\n";

	ofstream outFile;
	lock_guard<mutex> block(barrier);
	outFile.open("dictionary.txt", ios_base::app);
	outFile << wordToInsert;


	cout << "New word has been added to the dictionary.";
}

void Dictionary::editWord()
{
	thread t2(&Dictionary::saveEditFile, this);
	t2.join();
};

void Dictionary::saveEditFile()
{
	string wordToBeEdited, record, word, definition, type, emptyLine;
	bool found = false;

	ifstream inFile;
	lock_guard<mutex> block(barrier);
	inFile.open("dictionary.txt");
	ofstream tempDictionaryShort;
	tempDictionaryShort.open("dictionaryShortTemp.txt");
	cout << "Type in the word to be edited: ";
	cin >> wordToBeEdited;


	while (!inFile.eof())
	{
		getline(inFile, record);
		if (record == "") // check first for two consecutive blank lines, one line is already blank since previous iteration
		{
			break;
		}

		if (record != wordToBeEdited)
		{
			word = record;
			tempDictionaryShort << word << endl;
			getline(inFile, record);
			definition = record;
			tempDictionaryShort << definition << endl;
			getline(inFile, record);
			type = record;
			tempDictionaryShort << type << endl;
			getline(inFile, record); // blank line record delimiter
			emptyLine = record;
			tempDictionaryShort << emptyLine << endl;
		}
		else
		{
			found = true;
			const int newWordSize = 46, newDefinitionSize = 6015, newTypeSize = 8;
			char newWord[newWordSize], newDefinition[newDefinitionSize], newType[newTypeSize];
			string n_and_v = "n_and_v", adv = "adv", adj = "adj", prep = "prep", pn = "pn", misc = "misc";
			const char *nAndV = n_and_v.c_str(), *Adv = adv.c_str(), *Adj = adj.c_str(), *Prep = prep.c_str(), *Pn = pn.c_str(), *Misc = misc.c_str();

			cin.ignore(100, '\n'); // ignore characters left in cin
			cout << "Type in a new word: ";
			cin.get(newWord, newWordSize);
			tempDictionaryShort << newWord << endl;


			getline(inFile, record); // blank line record delimiter
			cin.ignore(46, '\n');
			cout << "Type in a word definintion: ";
			cin.get(newDefinition, newDefinitionSize);
			tempDictionaryShort << newDefinition << endl;


			getline(inFile, record);
			cin.ignore(6015, '\n');
			cout << "Type in a word type: ";
			cin.get(newType, newTypeSize);
			while (*newType != 'v' && *newType != 'n' && *newType != *Adv && *newType != *Adj && *newType != *Prep &&
				*newType != *Pn && *newType != *nAndV && *newType != *Misc)
			{
				cin.ignore(8, '\n');
				cout << "You have typed in a wrong type the only allowed types are 'v', 'n', 'adv', 'adj', 'prep', 'pn', 'n_and_v' and 'misc'!\n";
				cout << "Type in a correct word type: ";
				cin.get(newType, newTypeSize);

			}
			tempDictionaryShort << newType << endl;

			getline(inFile, record); // blank line record delimiter
			cin.ignore(8, '\n');
			emptyLine = record;
			tempDictionaryShort << emptyLine << endl;
		}
	}

	tempDictionaryShort.close();
	inFile.close();
	remove("dictionary.txt");
	rename("dictionaryShortTemp.txt", "dictionary.txt");
	if (found)
	{
		cout << "Word has been sucessfully edited";
	}
	else
	{
		cout << "Word has not been found";

	}
}

void Dictionary::deleteWord()
{
	thread t1(&Dictionary::saveDeleteFile, this);
	t1.join();
};

void Dictionary::saveDeleteFile()
{
	string wordToBeDeleted, record, word, definition, type, emptyLine;
	bool found = false;

	ifstream inFile;
	lock_guard<mutex> block(barrier);
	inFile.open("dictionary.txt");
	ofstream tempDictionaryShort;
	tempDictionaryShort.open("dictionaryShortTemp.txt");
	cout << "Type in the word to be deleted: ";
	cin >> wordToBeDeleted;

	while (!inFile.eof())
	{
		getline(inFile, record);
		if (record == "") // check first for two consecutive blank lines, one line is already blank since previous iteration
		{
			break;
		}

		if (record != wordToBeDeleted)
		{
			word = record;
			tempDictionaryShort << word << endl;
			getline(inFile, record);
			definition = record;
			tempDictionaryShort << definition << endl;
			getline(inFile, record);
			type = record;
			tempDictionaryShort << type << endl;
			getline(inFile, record); // blank line record delimiter
			emptyLine = record;
			tempDictionaryShort << emptyLine << endl;
		}
		else
		{
			found = true;
			getline(inFile, record);
			getline(inFile, record);
			getline(inFile, record); // blank line record delimiter
		}
	}

	tempDictionaryShort.close();
	inFile.close();
	remove("dictionary.txt");
	rename("dictionaryShortTemp.txt", "dictionary.txt");
	if (found)
	{
		cout << "Word has been sucessfully deleted";
	}
	else
	{
		cout << "Word has not been found";

	}
}