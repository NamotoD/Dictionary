// Trigrams.cpp
// accepts a text file and calculates the probabilities for each letter to follow a complete combination of two alpabetical letters
// methods implemented:
// returnIndex() = adds one to a letter if afollowing a double letter
// calculateProbabilities() =calculates the actual probabilities
// getMostLikelyLetterToFollow() = return the letter that will most likely follow a word passed in
// getThreeMostOftenUsedAfterDoubleLetters() = displays three most likely letters to follow passed in double letter, and its probabilities of occurrence
// addLetter() = accepts a word and return it with most likely letters to occur, the number of letters to be appended is passed in a second parameter
// displayResults() return the results as specified in assignment description
// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#include "Trigrams.h"
#include<map>
#include <algorithm>
#include <random>
#include<string>
using namespace std;

int Trigrams::returnIndex(char a) // as per blackboard
{
	int index = -1;
	int currentCharCode = (int)a;
	if (currentCharCode == (int)' ')
	{
		index = 0;
	}
	else if ((int)'a' <= currentCharCode <= (int)'z')
	{
		index = currentCharCode - (int)'a' + 1;
	}
	else
	{
		index = 0;
	}
	return index;
}

void Trigrams::calculateProbabilities()
{
	cout << "Calculating the probabilities..";
	ifstream inFile("crap.txt");
	string fileIn((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>()); // read file into a string
	fileIn.c_str();
	fileIn.erase(0, 3); // get rid rid of Byte Order Mark characters at the beginning of the file
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), '\n'), fileIn.end()); // sanitize a bit
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), '('), fileIn.end());
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), ')'), fileIn.end());
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), '.'), fileIn.end());
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), ','), fileIn.end());
	fileIn.erase(std::remove(fileIn.begin(), fileIn.end(), ';'), fileIn.end());
	string parsedFile;

	for (int i = 0; i < fileIn.length(); i++) // convert all letters to lowercase by turning the value of 32 bit on
	{
		if (isalpha(fileIn[i]) || isspace(static_cast<unsigned char>(fileIn[i]))) {
			fileIn[i] |= 32; parsedFile += fileIn[i];
		}
	}

	int characterCount[27][27][27] = { 0 };
	int index1, index2, index3;
	for (int i = 0; i < parsedFile.length() - 1; i++)
	{
		char a = parsedFile[i];
		char b = parsedFile[i + 1];
		char c = parsedFile[i + 2];
		index1 = returnIndex(a);
		index2 = returnIndex(b);
		index3 = returnIndex(c);
		if ((index1 != -1) && (index2 != -1) && (index3 != -1))
		{
			characterCount[index1][index2][index3]++;
		}
	}


// calculate how many times each combination of two letters appears in the text - needed to calculate the probabulities
	for (int i = 0; i < 27; ++i)
	{
		for (int j = 0; j < 27; ++j)
		{
			int lettersFound = 0;
			for (int k = 0; k < 27; ++k)
			{
				if (characterCount[i][j][k] != 0)
				{

					lettersFound += characterCount[i][j][k];
				}
			}
			//cout << alphabetLetters[i] << alphabetLetters[j] << " appeared " << lettersFound << " times!\n\n";
			doublesAppearance[i][j] = lettersFound;
		}
	}

// first populate all possible combination of alphabetical two letters and assign initial probabilities of the letter following to 0
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 27; j++)
		{
			string doubleLetterin;
			for (int k = 0; k < 27; k++)
			{
				string singlein;
				doubleLetterin += alphabetLetters[i];
				doubleLetterin += alphabetLetters[j];
				singlein += alphabetLetters[k];
				letterProbabilitiesAfterAllDoubleLetters[doubleLetterin][singlein] = 0; 
			}
		}
	}
// assign to all possible combination of alphabetical two letters the probabilities of any letter following to occur
	for (int i = 0; i < 27; ++i)
	{
		for (int j = 0; j < 27; ++j)
		{
			//cout << "\n\nMatches for letter " << alphabetLetters[i] << alphabetLetters[j] << ": " << endl;
			for (int k = 0; k < 27; ++k)
			{
				if (characterCount[i][j][k] != 0)
				{
					//cout << "Letter " << alphabetLetters[k] << " was found " << characterCount[i][j][k] << " times!" << endl;
					//cout << (float)characterCount[i][j][k] << " / " << (float)doublesAppearance[i][j] * 100 << endl;
					float probability = (float)characterCount[i][j][k] / (float)doublesAppearance[i][j] * 100;
					//cout << "Probability of  " << alphabetLetters[i] << alphabetLetters[j] << " being followed by " << alphabetLetters[k] << " is " << probability << "%\n" << endl;
					string doubleLetterin, singlein;
					doubleLetterin += alphabetLetters[i];
					doubleLetterin += alphabetLetters[j];
					singlein += alphabetLetters[k];
					letterProbabilitiesAfterAllDoubleLetters[doubleLetterin][singlein] = probability;
				}
			}
		}
	}
	cout << "\nCalculating completed!!\n";
}


string Trigrams::getMostLikelyLetterToFollow(string wordIn)
{
	map<string, double> getAllProbabilitiesForDoubleLetter = letterProbabilitiesAfterAllDoubleLetters[wordIn];
	string key = "";
	double val = 0;

	for (auto it = getAllProbabilitiesForDoubleLetter.cbegin(); it != getAllProbabilitiesForDoubleLetter.cend(); ++it)
	{
		if (it->second > val) {
			if (it->first != " ") // get rid of blank spaces
			{
				key = it->first;
				val = it->second;
			}
		}
	}
	getAllProbabilitiesForDoubleLetter[key] = 0;
	return key;
}

void Trigrams::getThreeMostOftenUsedAfterDoubleLetters(string twoLetters)
{
	cout << "\nThe 3 most likely characters to follow letters '" << twoLetters << "' and the probabilities are: \n";
	map<string, double> getAllProbabilitiesForDoubleLetter = letterProbabilitiesAfterAllDoubleLetters[twoLetters];
	for (int i = 0; i < 3; ++i)
	{
		string key = "";
		double val = 0;
		for (auto it = getAllProbabilitiesForDoubleLetter.cbegin(); it != getAllProbabilitiesForDoubleLetter.cend(); ++it)
		{
			if (it->second > val) {
				key = it->first;
				val = it->second;
			}
		}
		getAllProbabilitiesForDoubleLetter[key] = 0;
		cout << "Letter '" << key << "' has probability of " << val << ". " << endl;
	}
	cout << "\n" << endl;

}

string Trigrams::addLetter(string wordIn, int numOfLetters) // add most probably to occur letters to a given word
{
	string WordToReturn = wordIn;
	string nextLetter;
	for (int i = 0; i < numOfLetters; i++)
	{
		nextLetter = getMostLikelyLetterToFollow(wordIn);
		WordToReturn += nextLetter;
		wordIn = WordToReturn.substr(WordToReturn.size() - 2, 2);

	}

	return WordToReturn;
}

void Trigrams::displayResults(string twoLetters)
{
	getThreeMostOftenUsedAfterDoubleLetters(twoLetters); // display the three most likely to occur letters after the double letter provided by user

	vector<string> prefixes{ "after", "anti", "back", "be", "by", "co", "de", "dis", "down", "en", "em", "ex", "fore", "hind", "mid", "midi", "mini",
		"mis", "off", "on", "out", "over", "post", "pre", "pro", "re", "self", "step", "twi", "un", "un", "under", "up", "Afro", "ambi", "amphi", "an", "ana",
		"Anglo", "ante", "anti", "apo", "ap", "arch", "astro", "auto", "bi", "bio",	"circum", "cis", "con", "co", "com", "col", "cor", "contra", "contro", "counter",
		"cryo", "crypto", "de", "demi", "emo", "deuter", "di", "dif", "du", "duo", "eco", "electro", "epi", "ep", "Euro", "ex", "extra", "franco", "geo", "gyro",
		"hetero", "hemi", "homo", "hydro", "hyper", "hypo", "ideo", "idio", "in", "Indo", "in", "il", "im", "ir", "infra", "nter", "intra", "iso", "macr",  "mal",
		"maxi", "mega", "megalo", "meta", "micro", "mono", "mon", "multi", "mult", "neo", "non", "omni", "ortho", "paleo", "pan", "para", "ped", "per", "peri", "photo",
		"pleo", "pod", "poly", "post", "pre", "preter", "pro", "pro", "pros", "proto", "pseudo", "pyro", "quasi", "retro", "semi", "socio", "sub", "sup", "super",
		"supra", "sur", "syn", "sy", "syl", "sym", "tele", "trans", "tri", "ultra", "uni", "vice" };

	vector<string> suffixes{ "able", "ac", "acity", "ance", "ant", "ar", "ard", "arian", "arium", "ary", "ate", "ation", "ative", "cide", "cracy", "crat", "cule", "cy",
		"cycle", "dom", "dox", "ectomy ", "ee", "eer", "emia", "en", "ence", "ency", "ent", "er", "ern", "escence", "ese", "esque", "ess", "est", "etic", "etteful", "fy",
		"gam", "gamy", "gon", "gonic", "angle", "ial", "ian", "iasis", "iatric", "ible", "ic", "ical", "ile", "ily", "ine", "ing", "ion", "ious", "ish", "ism",
		"ist", "ite", "itis", "ive", "ize", "less", "let", "ostomy", "otomy", "ous ", "path", "phile", "phobia", "phone ", "phyte ", "plegia ", "plegic", "pnea", "scopy", "sect",
		"ship", "sion", "some", "sophy", "sophic", "th", "tion", "tome", "tomy ", "trophy", "tude", "ty", "ular", "uous", "ure", "ward", "ware", "wise" };

	for (auto const &prefix : prefixes)
	{
		string WordToReturn = addLetter(prefix, 1); //add number of most likely to occur letters to the prefix; first para is prefix passed, second the number of letters to be added
		for (auto const &suffix : suffixes)
		{
			random_shuffle(suffixes.begin(), suffixes.end());
			if (WordToReturn.back() == suffix.front()) // glue in random suffix if its first letter is the same as last letter of the word to return
			{
				WordToReturn.pop_back();
				WordToReturn += suffix;
				break;
			}
		}
		finalWords.push_back(WordToReturn);
	}
	random_shuffle(finalWords.begin(), finalWords.end());

	cout << "Following are randomly generated words using the most likely to occur letters: \n";
	for (string word : finalWords)
	{
		cout << "word: " << word << endl;
	}
}