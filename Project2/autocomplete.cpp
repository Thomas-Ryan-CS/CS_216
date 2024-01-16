/* File: autocomplete.cpp
 * Course: CS216-00x
 * Project: Project 2
 * Purpose: the implementation of member functions for the class named Autocomplete.
 *
 */
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{
    // You can leave it blank
    // since the private data member terms has been initialized through default constructor of SortingList class 
}
// inserts the newterm to the sequence
// note that a SortingList<Term> object, named terms
//          represents the sequence
void Autocomplete::insert(Term newterm)
{
    terms.insert(newterm);
}
// sort all the terms by query in the lexicographical order  
void Autocomplete::sort()
{
	terms.std_sort();
}
// binary search helper function
// as private function
// since it serves binary_search member function only
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if(right_index < left_index)
    {
        int KEY_NOT_FOUND = -1;
        return KEY_NOT_FOUND;
    }
    else
    {
        Term keyterm(key, 0);
        int r = key.length();
        int middle = (left_index + right_index) / 2;
        if(Term::compareByPrefix(keyterm,terms[middle],r) > 0)
        {
            return binary_searchHelper(terms, key, left_index, middle - 1);

        }
        else if(Term::compareByPrefix(keyterm,terms[middle],r)  < 0)
        {
            return binary_searchHelper(terms, key, middle + 1, right_index);
        }
        else
        {
            return middle;
        }
    }
}
// return the index number of the term whose query 
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequence
// Note that you may want a binary search helper function
int Autocomplete::binary_search(string prefix)
{
	// create two ends
        int left_end = 0;
        int right_end = terms.size()-1;
        // return binary_searchHelper, which does most of the work for us
        return binary_searchHelper(terms, prefix, left_end, right_end);
}
// first: the index of the first query whose prefix matches
//          the search key, or -1 if no such key
// last: the index of the last query whose prefix matches 
//         the search key, or -1 if no such key
// key: the given prefix to match
// hints: you can call binary_search() first to find one matched index number,
//        say hit, then look up and down from hit, to find first and last respectively
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
	int match = binary_search(key); // finds a match
    	if (match == -1) // no match
    	{
        	firstIndex = -1;
        	lastIndex = -1;
		return;
    	}
    	// With that case taken care of, we can proceed
    	int leftIndex = match;
    	while (leftIndex > 0 && Term::compareByPrefix(terms[leftIndex],terms[match],key.length()) == 0)
    	{	
       		leftIndex--; // moves left
    	}	
    	// Now that we searched left, we can now search right
    	int rightIndex = match;
    	while (rightIndex < terms.size() && Term::compareByPrefix(terms[match], terms[rightIndex], key.length()) == 0)
    	{
        	rightIndex++; // moves right
    	}
	firstIndex = leftIndex + 1;
	lastIndex = rightIndex - 1;
}
// returns all terms that start with the given prefix, in descending order of weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{
	// defining bounds
	int first = 0; 
	int last = terms.size()-1;
	search(prefix, first, last);
	SortingList<Term> found; // create list of all matches
	if (first == -1 || last == -1)
	{
		SortingList<Term> empty;
		return empty;
		// returns an empty list for handling in main
	}
	for (int i = last; i >= first; i--) // loops through the range of all terms that match
    	{
        	found.insert(terms[i]); // inserts
    	}
	if (found.size() > 0) // checking size/ need to to sort
    	{
        	found.merge_sort(Term::compareByWeight); // merge sort
    	}
    	return found; 
}
void Autocomplete::print()
{
	terms.print();
}
