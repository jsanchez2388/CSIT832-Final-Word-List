//Josue Sanchez
//Date: 11/28/2018
//CSIT 832 Assignment 10
//Description: This program reads a txt file and identifies all of the words in that file. It them retrieves
//the number of unique words and how often they appear in the text, and the total number of words. It then
//outputs the results in a txt file

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "wordtree.h"

using namespace std;

//Function Prototype
void parseString(string&, WordTree&);

int main() {
	ifstream fin;
	ofstream fout;
	string filename;
	cout << "Enter name of file with text to analyze: ";
	cin >> filename;
	fin.open(filename.c_str());
	if (fin.fail()) {
		cout << "Error opening file.\n";
		exit(1);
	}
	cout << "\nAnalyzing " << filename << ".\n";

	WordTree myTree;
	string tempString;

	//Process all lines in file
	while (!fin.eof())
	{
		getline(fin, tempString);	//read each line
		parseString(tempString, myTree);	//Call funtion to find words and add them to tree
	}

	fin.close();
	fout.open("results.txt");
	unsigned int wordcount = myTree.totalWords();
	cout << "\nWord counts:\n\n";
	cout << myTree;
	fout << myTree;
	cout << "\nTotal number of words in text: " << wordcount << ".\n";
	fout << "\nTotal number of words in text: " << wordcount << ".\n";
	cout << "Number of distinct words appearing in text: "
		<< myTree.distinctWords() << ".\n";
	fout << "Number of distinct words appearing in text: "
		<< myTree.distinctWords() << ".\n";
	fout.close();
	system("pause");
	return 0;
}

void parseString(string& s, WordTree& t)
{
	string container = ""; //Used to hold characters

	for (unsigned int i = 0; i <= s.size(); i++)
	{
		if (isalpha(s[i]) || s[i] == '\'')	//Check for letters or '
		{
			if (s[i] != '\'')
			{
				s[i] = tolower(s[i]);	//Convert to lowercase if char isalpha
			}
			container += s[i];	//Append to container
		}
		else
		{
			if (container.size() > 0)	//If container not empty
			{
				t.add(container);	//Add word to tree
				container = "";	//Clear container
			}
		}
	}
}