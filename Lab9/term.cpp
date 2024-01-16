/* File: term.cpp
 * Course: CS216-00x
 * Project: Project 2
 * Purpose: the implementation of member functions for the Term class.
 * Name: Thomas Ryan
 */
#include <iostream>
#include "term.h"

// default constructor
Term::Term()
{
    query = "";
    weight = 0;
}

// initializes a term with the given query string and weight
Term::Term(string query, long weight)
{
    this->weight = weight;
    this->query = query;
}

// compares the two terms in descending order by weight
// if the order of T1 and T2 in descending order by weight, return 1;
// if T1 and T2 are of the same weight, return 0;
// otherwise return -1
int Term::compareByWeight(Term T1, Term T2)
{
    if (T1.weight > T2.weight) 
    {
	return 1; // because in descending order
    }
    else if (T1.weight == T2.weight)
    {
	return 0; // because same weight
    }
    else
    {
	return -1; // because third else case
    }
}

// compares the two terms in lexicographic order but using only the first r characters of each query
int Term::compareByPrefix(Term T1, Term T2, int r)
{
    if (r < 0)
    {
        cout << "The length of the prefix should be a positive number!" << endl;
        return 2;
    }    
    string T1_prefix = (T1.query).substr(0,r);
    string T2_prefix = (T2.query).substr(0,r);

    if (T1_prefix < T2_prefix)
        return 1;
    if (T1_prefix == T2_prefix)
        return 0;
    else
        return -1;
}

// operator overloading for operators "<" and "<<"
// they both are defined as friend functions

// define the operator "<" for Term class
// T1 < T2 if and only if the query of T1 is less than the query of T2 (based on string comparison)
bool operator<(Term T1, Term T2)
{
    return T1.query < T2.query; // returns true or false based on this statement... meaning no conditional
}

// define the operator "<<" for Term class
// to send the Term object to the cout, in the following format:
// the weight, followed by a tab key, followed by the query
ostream& operator<<(ostream &out, const Term& t)
{
    out << t.weight << "\t" << t.query;
    return out;
}
