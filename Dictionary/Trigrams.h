// Trigrams.h
// defines class Trigrams

// CSP2104 - 2017/1
// Oto Drahonovsky: 10139126

#ifndef TRIGRAMS_H
#pragma once
#define TRIGRAMS_H
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include <algorithm>

using namespace std;

class Trigrams
{
private: 

	map<string, map<string, double> > letterProbabilitiesAfterAllDoubleLetters; // store all possible combinations of two alpha letters and the probabilities associated with the letter following the double letter
	map<string, double> fiftyMostUsedDoubleLetters;
	vector <string> finalWords;
	vector <string> finalTenRandwords;
	vector <string> randwords;
	int returnIndex(char a);
	int doublesAppearance[27][27] = { 0 }; // how many times letter appeared in the file
	char alphabetLetters[27] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f' , 'g', 'h', 'i' , 'j', 'k', 'l' , 'm', 'n', 'o' , 'p', 'q', 'r' , 's', 't', 'u' , 'v', 'w', 'x' , 'y', 'z' };
	void Trigrams::getThreeMostOftenUsedAfterDoubleLetters(string twoLetters);
	string Trigrams::getMostLikelyLetterToFollow(string wordIn);
public:
	void calculateProbabilities();
	void displayResults(string twoLetters); 
	string Trigrams::addLetter(string wordIn, int numOfLetters);
};
#endif // !TRIGRAMS_H