// Thomas Ryan
// CS216
// MAIN / PA1 FILE
// September 26 2023
// Purpose: To Use a movie name or actor name to output desired information based on user input and a map of information
#include <iostream> // for io
#include <limits>
#include <fstream> // for txt read
#include <string> // for strings
#include <cctype>
#include <set> // for sets
#include <map> // for map
#include <sstream>
#include "imdb.h" // header
#include <regex>
using namespace std;

void analyzeMovies(const IMDB& imdb); // Global for Option 1
void analyzeCoActors(const IMDB& imdb); // Global for option 2

int main(int argc, char* argv[])
{
    const int COMM_NUM = 2;
    // Check whether the number of command line arguments is exactly one 
    if (argc != COMM_NUM) // if not correct number of arguments
    {
	// Error message
        cout << "Warning: need exactly " << COMM_NUM - 1 << " command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1; // Return error 1
    }
    
    ifstream in_file; // to get actor_movies.txt
    in_file.open(argv[COMM_NUM-1]); // opens file specified in command line (actor_movies.txt)

    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
	// Error Message
        cout << "Warning: cannot open file named " << argv[COMM_NUM-1] << "!" << endl;
        return 2; // Return Error 2
    }

    // Read data from the input file, assume "good data" from the input file
    // each line of the input file: actor name; movie1; movie2; ...; movieN;
    // read one line at a time then tokenize it:
    // create a pair <actor_name, the set of movieTitles which the actor was in>
    //        and insert to IMDB object
    IMDB cs216_imdb;

    while (!in_file.eof()) // while not end of file
    {
        string line;
        getline(in_file, line); // get info from in_file, assign that info to string line.
        string actorName, movieTitle;
        // check if the text line is not empty then tokenize it
        if (line.length() != 0) 
        {
            istringstream iss(line);
            getline(iss, actorName,';');
            // Extract extra white space
            iss>>ws;
            // Create a new set of movies associated with name
            set<string> movies;
            while (getline(iss, movieTitle, ';'))
            {
                movies.insert(movieTitle);
                // extract white space 
                iss>>ws;
            }
            // insert the pair to IMDB object: cs216_imdb
            cs216_imdb.insert_an_actor(actorName, movies);
        }
    }
    // close the input file
    in_file.close();
    int option;
    //bool validInput = true; // boolean for while loop
    while (true) // while input is true
    {
	// Menu output
	bool validInput = true;
        cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
	// take in the option from User
        cin >> option;
	// If cin gets an invalid value
        if (cin.fail())
        {
            string input_to_check;
	    cin.clear();
            cin >> input_to_check;
	    // If user quits
	    if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Expecting a number as the option!" << endl;
                validInput = false;// will cause loop to end
	    }
          // clears invalid input
        }
        // get rid of anything left in the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // if there is a valid input option
	// Combined Lab4 and Lab5
        if (validInput)
        {
            switch (option)
            {
                case 1: analyzeMovies(cs216_imdb); // Lab4
                        break;
                case 2:  analyzeCoActors(cs216_imdb); // Lab5
                        break;
                default: // any other case
                        cout << "Invalid option number!" << endl;
            }
        }
    }
    // EOP Output
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}
/*
 * Purpose: this function asks the user to type an actor's name
 * then check if the user-input name is valid(it is valid if it is in the database stored in the passing in object
 * if it is valid, display each movie which this actor is in, the co-actors who appeared in the same movie
 *@param imdb, the object of IMDB class: stores all information to look up (const call by reference)
 *@return void function
 */
void analyzeCoActors(const IMDB& imdb)
{
    string actor_name; // actor name stored as string
    cout << "Finding the co-actors of the actor by typing his/her name: ";    
    getline(cin, actor_name); // gets actor's name from cin
    if (!imdb.isExistingActor(actor_name)) // if actor is not in database
    {
	// output and return
        cout << "The actor name you entered is not in the database." << endl;
        return;
    }

    set<string> movies_of_actor; // set that will store movies that the actor is in
    movies_of_actor = imdb.find_movies_for_an_actor(actor_name); // The set contains movies the actor is in, in imdb db by using actor_name to find
    for (set<string>::iterator im = movies_of_actor.begin(); im != movies_of_actor.end(); im++) // loops tgroough entire movies_of_actir set
    {
	// output of actor name and movie
        cout << "The co-actors of " << actor_name << " in the movie \"" << *im << "\" are: " << endl;
        // Display all the co-actors in one movie
        set<string> coactors = imdb.find_actors_in_a_movie(*im);
        for (set<string>::iterator ia = coactors.begin(); ia != coactors.end(); ia++)
        {
			if (*ia != actor_name) // if it does not equal the actor that was inputted
			{
        			cout << *ia << endl; // output
    			}
        }
        cout << "***********************************" << endl;
    }

}
/* Purpose: this function asks the user to input two movie titles
 *          then finds the matched two movies from the database
 *          and displays all the actors in either of the two movies
 *          if no matched movie then display "Invalid movie title" and do nothing
 * @para imdb const IMDB&: represent the actorName-Movies database
 *          note that using const call by reference is for efficiency purpose:
 *               no copy of IMDB object is made and the argument has been protected
 * @return void
*/
void analyzeMovies(const IMDB& imdb)
{
    // Ask the user to input two movie titles to search for
    string movie1, movie2;
    cout << "Please input the first movie title: ";
    getline(cin,movie1);
    cout << "Please input the second movie title: ";
    getline(cin,movie2);
    // Check if both movie1 and movie2 can be matched with movies in the database
    // If either one is not, quit the program
    // Otherwise display all the actors in either of two movies
    //                   which are actually the union of two sets
    string matchedMovie1, matchedMovie2;
    matchedMovie1 = imdb.matchExistingMovie(movie1);
    matchedMovie2 = imdb.matchExistingMovie(movie2);
    // decide which one movie title is not valid
    bool notValid = false;
    if (matchedMovie1.length() == 0) // if invalid movie title for 1st match
    {
        cout << "\" " << movie1 << " \"" << " is not a VALID movie title!" << endl;
        notValid = true;
    }
    if (matchedMovie2.length() == 0) // if invalid movie title for 2nd match
    {
        cout << "\" " << movie2 << " \"" << " is not a VALID movie title!" << endl;
        notValid = true;
    }
    if (notValid) // notValid checker
        return;
    // both movie titles are valid
    if (imdb.isExistingMovie(matchedMovie1) && imdb.isExistingMovie(matchedMovie2))
    {
	// output
        cout << "Your input matches the following two movies: " <<endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, please continue..." << endl;
        set<string> all;   // to store the union of actors_in_movie1 and actors_in_movie2
        all = imdb.find_actors_in_a_movie(matchedMovie1);
        set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
        for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
        {
            if (imdb.isExistingActor(*i))
                all.insert(*i);
            else
                cout << "isExistingActor function is not correct!!!" << endl;
        }
        // Display all the actors in either one movie
        //cout << "All the actors in either of the two movies:" << endl;
        //for (auto i = all.begin(); i != all.end(); i++)
            //cout << *i << endl;
    }
    else
    {
        cout << "isExistingMovie function is not correct!!!" << endl;
        return;
    }

    bool switcherton = true; // boolean for while loop, was initially for a switch
    while (switcherton)
    {
      cin.clear();// clears cin
      cout << "Would you like to:\n" <<
      "A -- to print all the actors in either of the two movies.\n" <<
      "C -- to print all the common actors in both of the movies.\n" <<
      "O -- to print all the actors who are in only one movie, but not in both.\n" <<
      "(Q or q): quit" << endl;
      string check;
      getline(cin, check);
      //cin >> check;
      // if user wants to quit
      char verify = check.at(0);
      if (verify == 'Q' || verify == 'q')
      {
      	switcherton = false;
      }
      // if user picks A or A
      else if ( verify == 'a'  || verify == 'A') // This was basically what option 1 did before 
      {
		  cout << "All the actors in either of the two movies:" << endl;
		  set<string> allA = imdb.find_actors_in_a_movie(matchedMovie1);
		  // loops through allA and prints all actors
		  for (auto i = allA.begin(); i != allA.end(); i++)
		  {
            		cout << *i << endl; // output
		  }
                  set <string> allB = imdb.find_actors_in_a_movie(matchedMovie2);
		  // loops through allB and prints all actors
                  for (auto i = allB.begin(); i != allB.end(); i++)
                  {
                        cout << *i << endl; // output
                  }
      }
      // if user picks c or C
      else if (verify == 'C'|| verify == 'c')
      {
	      	  // The two inital sets
	          set<string> allC = imdb.find_actors_in_a_movie(matchedMovie1);
  		  set<string> allC2 = imdb.find_actors_in_a_movie(matchedMovie2);
		  // nested loop
		  cout << "Common actors in both movies:" << endl;
		  for (auto i = allC.begin(); i != allC.end(); i++)
		  {
			  for (auto j = allC2.begin(); j != allC2.end(); j++)
			  {
				if (*i == *j) // if in both sets
				{
				   cout << *i << endl; // doesn't matter if *i or *j, same value anyway
				}
			  }
		  }
      }
      else if ( verify == 'o' || verify == 'O')
      {
      		 // The two inital sets
                  set<string> allC = imdb.find_actors_in_a_movie(matchedMovie1);
                  set<string> allC2 = imdb.find_actors_in_a_movie(matchedMovie2);
                  // The set of actors in both sets
                  set<string> totalC;
                  // nested loop
		  cout << "Actors only in one of two movies:" << endl;
                  for (auto i = allC.begin(); i != allC.end(); i++)
                  {
                          for (auto j = allC2.begin(); j != allC2.end(); j++)
                          {
                                if (*i == *j) // if in both sets
                                {
                                   totalC.insert(*i); // doesn't matter if *i or *j, same value anyway
                                }
                          }
                  }
		  // next two loops compares matchedMovie1 and matchedMovie2 to TotalC, totalC has all the common actors
		  // So if *i != *j then we will get the various actors for either movie that are not in both.
		  for (auto i = allC.begin(); i != allC.end(); i++)
		  {
			 for (auto j = totalC.begin(); j != totalC.end(); j++)
			 {
				if (*i != *j)
				{
					cout << *i << endl; // output for movie 1
				}
			 }
		  }
		  for (auto i = allC2.begin(); i != allC2.end(); i++)
		  {
			   for (auto j = totalC.begin(); j != totalC.end(); j++)
			   {
				    if (*i != *j)
                                {
                                        cout << *i << endl; // output for movie 2
                                }
			   }
		  }
      }
      else
      {
	cout << "Invalid Option!" << endl;
      }
   }
}
