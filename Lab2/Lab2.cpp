/*
 * Course: CS216-00x
 * Project: Lab 2
 * Purpose: practice how to run unix command from C++ program
 *          system() is used to invoke an operating command from a C++ program
 *          demo cowsay command using three different cow files
 * Author: (your name)
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in_file;
    in_file.open("cowFiles.txt");
    int NUM_OF_COWS = 0;
    string line;
    vector <string> cowNames;
    if (in_file.is_open())
    {
	while (getline(in_file, line))
	{
          NUM_OF_COWS++;
          cowNames.push_back(line);
	}
    }
    else
    {
      cout << "Unable to open file" << endl;
    }
    
    for (int i = 0; i < NUM_OF_COWS; i++)
    {
        // each time use a different cow file for cowsay command to use
        string command_str = "cowsay -f /usr/share/cowsay/cows/";
        command_str = command_str + cowNames.at(i);
        command_str = command_str + " Hello, CS216 Students!";
        const char* command = command_str.c_str();
        system(command);
    }
    cout << "There are " << NUM_OF_COWS << " cow Files stored in my VM" << endl;
    in_file.close();
    return 0;
}


