// Thomas Ryan
// Graph.cpp
// CS 216 
// Purpose: Build a Graph

#include <map>
#include <set>
#include <queue>
#include "Graph.h"
using namespace std;

Graph::Graph()
{

}
// to check if an edge exists between v and w
bool Graph::hasEdge(char v, char w) const
{
	return adjMap.count(v) && adjMap.at(v).count(w); // makes sure v exists, then counts v to w if present
}

void Graph::addEdge(char v, char w)
{
    	// Since undirected, edge goes both ways
    	adjMap[v].insert(w);
    	adjMap[w].insert(v);
}

int Graph::BFS(char s, char t, map<char, int>& distance, map<char, char>& go_through) const
{
	const int INVALID_VERTEX = -2;
        const int NOPATH = -1;
	// initialize distance and go_through
	distance.clear();
    	go_through.clear();

	// CASE: check if either s or t does not exist (gets to adjMap.end())
	if (adjMap.find(s) == adjMap.end() || adjMap.find(t) == adjMap.end())
        {  
        	return INVALID_VERTEX;
        }

	// find shortest path from s to t
	// CASE: if they are equal
	if (s == t)
	{
		distance[s] = 0;
		return distance[s];
	}

	// create queue
	queue<char> breadth_first_search;
	breadth_first_search.push(s); // adds s to queue
	// store which ones have been visted store as set because duplicates dont serve a purpose order doesnt matter
	set<char> visited;
	visited.insert(s);
	
	distance[s] = 0; // distance from self is zero.
	
	// now to traverse
	// make sure breadth_first_search has at least on element
	while (!breadth_first_search.empty())
	{
		char curr = breadth_first_search.front();
		breadth_first_search.pop(); // remove curr from queue
		// for each to look at neighbors of first vertex
		for (char neighbor : adjMap.at(curr))
		{
			if (visited.count(neighbor) == 0) // see if neighbor has been visited
                	{
				breadth_first_search.push(neighbor); // add neighbor to queue
				visited.insert(neighbor); // inserts neighbor that was visited to the set
				// update the new distance
				distance[neighbor] = distance[curr] + 1;
				// update go_through map
				go_through[neighbor] = curr;
				// check if BFS has arrived at the desired value
				if (neighbor == t)
                		{
              				return distance[t]; // returns shortest path
               			}
			}
		}
	}
	return NOPATH;
}
