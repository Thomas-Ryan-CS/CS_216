/*
 * File: imdb.cpp
 * Course: CS216-00x
 * Project: Project 1
 * Purpose: Provide the implementation of the class named IMDB
 *          This class represents a movie-actor database
 *
 * Name: Thomas Ryan
 */
#include <regex>  // needs c++11 standard
#include "imdb.h"

using namespace std;

// default constructor
IMDB::IMDB()
{
    //do nothing
    //since map class contains a default contructor
    //      which constructs an empty container, with no elements
}

// insert a pair<actorName, the set of movieTitle of this actor>
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
	if (!isExistingActor(actorName)) // if the actors name is not in the database
		actors_db[actorName] = movieTitles; // at actors name, actor has x movie ytitles
	else
	{
		actors_db[actorName].insert(movieTitles.begin(), movieTitles.end()); // inserts movie titles at actor
	}

	for (auto it = movieTitles.begin(); it != movieTitles.end(); it++) // from fist movie title to the last
	{
		if (movies_db.find(*it) == movies_db.end())
		{
			set<string> actors; // creates a set of actor names
			actors.insert(actorName); // inserts actor's name into set
			movies_db[*it] = actors; // movie database @ *it = the set of actors
		}
		else
		{
			movies_db[*it].insert(actorName); // actor is inserted @ *it in Movies_db
		}
	}
}

// insert a pair <movieTitle, the set of actor names in this movie>
// this function is optional to this project
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames) 
{
    // First upgrade movies_db
    // if the key moiveTitle does not exist
    //        add the key to the map movies_db
    if (!isExistingMovie(movieTitle))
        movies_db[movieTitle] = actorNames;
    else // if the key movieTitle does exist
    {
        movies_db[movieTitle].insert(actorNames.begin(), actorNames.end());
    }

    // Second upgrade actors_db
    // for each actor name in the set of actorNames,
    // insert movieTitle to its movie set
    for (auto it = actorNames.begin(); it != actorNames.end(); it++)
    {
        if (actors_db.find(*it) == actors_db.end())
        {
            set<string> movies;
            movies.insert(movieTitle);
            actors_db[*it] = movies;
        }
        else
        {
            actors_db[*it].insert(movieTitle);
        }
    }
}

// use passing in parameter, movieTitle, as the pattern to match 
// one existing movie in the map
// return the matched movie title from the map
// otherwise return empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    // generate the regular expression to match 
    // which contains movieTitle as a substring
    // note that it performs case insensitive matching
    regex reg(movieTitle, regex_constants::icase);
    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true; // movie is found
            matchedMovie = it->first; // matched movie is the first value
        }
        else
            it++;
    }
    return matchedMovie;
}

// check if a movieTitle does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingMovie(string movieTitle) const
{
	// returns a bool
	return !(movies_db.find(movieTitle) == movies_db.end());
}

// check if an actorName does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingActor(string actorName) const
{
	// returns a bool
	return !(actors_db.find(actorName) == actors_db.end());
}

// return a set of movie titles which actorName is in
// if the passing in parameter: actorName, is not in the database, 
//                   display message andreturn an empty set
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
	set<string> emp;
	if (actors_db.find(actorName) == actors_db.end())
	{
		// couln't find that actors name
		return emp;
	}
	else
	{
		return actors_db.find(actorName)->second; // found actor,and returns it as secon value
	}
}

// return a set of actor names which are all in the movieTitle
// if the passing in parameter: movieTitle is not in the database, 
//                   display message and return an empty set
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
	set<string> emp;
	if (movies_db.find(movieTitle) == movies_db.end())
	{
		// could not find movie title
		return emp;
	}
	else
	{
		// movie in db
		return movies_db.find(movieTitle)->second;
	}
}
