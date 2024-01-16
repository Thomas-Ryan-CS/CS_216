// Thomas Ryan
// Graph.cpp
// CS 216 
// Purpose: Build a Graph
#ifndef GRAPH_cpp
#define GRAPH_cpp

#include <map>
#include <set>
#include <queue>
#include "Graph.h"
using namespace std;

// default constructor empty becuz nothing needs to happen
template <typename Vertex>
Graph<Vertex>::Graph()
{

}
// to check if an edge exists between v and w
template <typename Vertex>
bool Graph<Vertex>::hasEdge(Vertex v, Vertex w) const
{
	return adjMap.count(v) && adjMap.at(v).count(w); // makes sure v exists, then counts v to w if present
}
// Adds an edge between vertexes
template <typename Vertex>
void Graph<Vertex>::addEdge(Vertex v, Vertex w)
{
    	// Since undirected, edge  goes both ways
    	adjMap[v].insert(w);
    	adjMap[w].insert(v);
}
// Performs Breadth First Search
template <typename Vertex> 
int Graph<Vertex>::BFS(Vertex s, Vertex t, map<Vertex, int>& distance, map<Vertex, Vertex>& go_through) const
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
	queue<Vertex> breadth_first_search;
	breadth_first_search.push(s); // adds s to queue
	// store which ones have been visted store as set because duplicates dont serve a purpose order doesnt matter
	set<Vertex> visited;
	visited.insert(s);
	
	distance[s] = 0; // distance from self is zero.
	
	// now to traverse
	// make sure breadth_first_search has at least on element
	while (!breadth_first_search.empty())
	{
		Vertex curr = breadth_first_search.front();
		breadth_first_search.pop(); // remove curr from queue
		// for each to look at neighbors of first vertex
		for (Vertex neighbor : adjMap.at(curr))
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
	return NOPATH; // NOPATH (SADNESS)
}
#endif
