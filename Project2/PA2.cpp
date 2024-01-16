/*
 * Course: CS216-00x
 * Project: Project 2
 * Purpose: repeatedly ask the user to type prefix to match
 *          and generate all the prefix-matched terms
 *          then display the prefix-matched terms in descending order by weight.
 * Name: Thomas Ryan
 */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv) {
    // checking argument count
    const int ARGUMENTS = 1;
    if (argc != ARGUMENTS+2)
    {
        cout << endl << "Warning: need exactly 3 command line arguments." << endl;
        cout << "Usage: " << argv[0] << " <filename> number" << endl << endl;
        return 1;
    }
    // conversion from char to int
    // cant convert << (*argv[2]) because it only handles first character
    // stoi would have been nicer
    stringstream convert(argv[2]);
    int quantity = 0;
    convert >> quantity;

    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << endl << "Warning: cannot open the file named " << argv[1] << endl << endl;
        return 2;
    }
    // check 3rd argument using argv[2] through str to int conversion, quantity
    if (quantity <= 0)
    {
	cout << endl << "Warning: the number of matching terms needs to be a positive number!" << endl << endl;
	return 3;
    }

    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;

    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }
    }
    // std::sort
    autocomplete.sort();
    string input;
    string prefix;
    cout << endl << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = input;
    while (prefix != "exit")
    {
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        if (matchedTerms.size() == 0) // empty
        {
            cout << "No matched query!" << endl;
        }
	else if (matchedTerms.size() < quantity) // prevents out of bounds error
	{
	    for (int i = 0; i < matchedTerms.size(); i++)
            {
                cout << matchedTerms[i] << endl;
            }
	}
        else
        {
	    for (int i = 0; i < quantity; i++)
	    {
		cout << matchedTerms[i] << endl;
	    }
	}

        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, input);
        prefix = input;
    }
    return 0;
}
