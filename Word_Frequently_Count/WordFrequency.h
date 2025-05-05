#pragma once

#include<unordered_map>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class WordFrequnecy
{
public:

	WordFrequnecy();
	void removePunctuation(string& str);
	void toLowercase(string& str);
	string WriteParagraphinConsole();
	string ReadTheParagraphFromFile(string& filename);
	void WriteParagraphInFile(string& paragraph, string& filename);
	vector<string> AutoCompleteWords(unordered_map<string, int>& WordFrequency, string& word);
	string AutoCorrectWords(unordered_map<string, int>& WordFrequency,string& word);
	string AutoCompleteSentence(string& sentence, string& paragraph);
	string AutoCorrectSentence(unordered_map<string, int>& WordFrequency, string& sentence,string& paragraph);
	void display_Current_Paragrah(string& paragraph);
	void calculateWordsFrequencies(unordered_map <string, int>& WordFrequency, string paragraph);
	void displayWordFrequencies(unordered_map<string, int>& WordFrequency);
	void displaySortedWordFrequencies(unordered_map<string, int>& WordFrequency);
	void SearchWord(unordered_map <string, int>& WordFrequency);
	void displayTheRankOfTheWord(unordered_map <string, int>& WordFrequency);
	void displayRankingOfAllWord(unordered_map <string, int>& WordFrequency);
	void DeleteFromParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph);
	void EditInParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph);
	void continueWritingInParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map<string, int>& LocallWordFrequency, string& paragraph);
	void updateParagraph(unordered_map <string, int>& GlobalWordFrequency, unordered_map <string, int>& LocalWordFrequency, string& paragraph);

};


