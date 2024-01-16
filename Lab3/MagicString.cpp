/* 
 * File:   MagicString.cpp
 * Purpose: provide the definition of the MagicString class
 *
 * Author: Thomas Ryan
 *
 */
#include <iostream>
#include <stack>
#include "MagicString.h"

using namespace std;

// initialize str with ini_str passing as a parameter
MagicString::MagicString(string ini_str)
{
	str = ini_str;
}

// return the current value of the private data member: str
string MagicString::getString() const
{
	return str;
}
// set the value of str to be the passed in parameter input_str
void MagicString::setString(string input_str)
{
	str = input_str;
}

// return a reverse string
// using a loop to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_loop() const {
	// loop time. 
	string cope = str;
	int string_length = str.length();
	for (int i = 0; i < string_length / 2; i++)
	{
		char temp = cope[i];
		cope[i] = cope[string_length-i-1];
		cope[string_length-i-1] = temp;
		// swaps last with first moving towards middle
					      // string_length - i gets to correct number, subtract
					      // one to account for 0 position
	}
	return cope;	
}

// return a reverse string
// using recursion to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_recursion() const
{
	int string_length = str.length();
	if (string_length <= 1) // base case
		return str;
	else // returns last (in reverse order) and uses substr to recursively get to first character
	{
		return str.back() + MagicString(str.substr(0, str.length() - 1)).rev_recursion();
	}
}

// return a reverse string
// using a stack to implement
// Note that the private data member named str, has not been changed
string MagicString::rev_stack() const
{
	stack <char> word; // char because stack is accepting indicidual characters.
	int string_length = str.length();
	for (int i = 0; i < string_length; i++)
	{
	word.push(str.at(i)); // adds each character to stack
	}
	string str2; // make str empty, using another variable for ease
	// we want stack to output everything in stack until empty
	while (!word.empty()) // We can do this by negating this premise and put it in while loop
	{
		str2.push_back(word.top()); // adds chars to string from stack startong from top
					   // or the most recent hence in a backwards order
		word.pop(); // removes top element
	}
	return str2;
}

// return true if str is a palindrome
// otherwise return false
// A palindrome is defined as a sequence of characters which reads the same backward as forward
// calling member function to  implement
// Note that the private data member named str, has not been changed
bool MagicString::isPalindrome() const
{
	bool ret;
	if (rev_loop() == str)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}
        
// return true if str is a palindrome
// otherwise return false
// A palindrome is defined as a sequence of characters which reads the same backward as forward
// using recursion to implement
// Note that the private data member named str, has not been changed
bool MagicString::isPalindrome_recursion() const
{
	int string_length = str.length();
	int i = 0;
	// base case
	if (string_length <= 1)
	{
		return true;
	}
	// second base case
	else if (str[i] != str[string_length-1])
	{
		return false;
	}
	// recursive case
	else // returns last (in reverse order) and uses substr to recursively get to first character
	     // This works because if it is a palindrome it will evetually trigger base case
	{
		return MagicString(str.substr(1, str.length() - 2)).isPalindrome_recursion();
	}
}
        
// displays str followed by a new line marker
// to the standard output
void MagicString::print() const
{
	cout << str << endl;
}
