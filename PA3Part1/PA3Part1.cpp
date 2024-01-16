/*
 *course: CS216-00x
 *Project: Project 3 Part 1
 *Purpose: create a graph from given set of vertices and edges
 *         repeatedly ask the user to choose a source vertex, then a destination vertex (enter "Q" or "q" to quit)
 *         and calculate the shortest distance from the source to the destination
 *         then display the shortest path from the destination back to the source
 *         It is a sub-problem of Project 3.
 *Author: Thomas Ryan
 */

#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
    // Create a graph given by Figure 1 of Lab11 description
    Graph testingGraph;
    testingGraph.addEdge('A', 'B');
    testingGraph.addEdge('A', 'E');     //you need to comment out this statement for one testing case --- I DID
    testingGraph.addEdge('B', 'C');
    testingGraph.addEdge('B', 'D');
    testingGraph.addEdge('C', 'D');
    testingGraph.addEdge('E', 'F');
    testingGraph.addEdge('E', 'G');
    testingGraph.addEdge('F', 'H');
    testingGraph.addEdge('G', 'H');

    char inputS, inputD;
    char source, destination;

    while (true)
    {
        cout << endl << endl;
        cout << "Welcome to CS216--Breadth First Traversal (to find the shortest path)" << endl;
        if (testingGraph.hasEdge('A', 'E'))
            cout << "Assumption: it is a connected graph!" << endl;
        else
            cout << "Assumption: it is a disjoint graph!" << endl;

        cout << "Please choose the vertex as the source (a single upper-case letter to label) (type 'Q' or 'q' to quit): " << endl;
        cin >> inputS;
        cin.ignore(256, '\n');

        if (inputS == 'q' || inputS == 'Q')
            break;

        cout << "Please choose the vertex as the destination (a single upper-case letter to label) (type 'Q' or 'q' to quit): " << endl;
        cin >> inputD;
        cin.ignore(256, '\n');

        if (inputD == 'q' || inputD == 'Q')
            break;

        source = toupper(inputS);
        destination = toupper(inputD);
        cout << endl;
        cout << "Finding the shortest path: " << endl;
        cout << "(starting from the vertex: " << source << " ---> to the vertex: " << destination << " )" << endl;

        map<char,int> distance;
        map<char, char> go_through;
        int dis = testingGraph.BFS(source, destination, distance, go_through);
        // Display the distance from the destination vertex to the source vertex
        // Display the shortest path from the destination vertex back to the source vertex 
        // the distance is defined as the number of edges
        // the distance from the source to the source is 0
        // there is no path from the source to a vertex if its distance is -1
        if ( dis == NOPATH || dis == INVALID_VERTEX)
            cout << "There is no path from " << source << " to " << destination << endl;
        else if ( dis == 0)
        {
            cout << "The source and the destination should be different." << endl;
        }
        else 
        {
            cout << "The distance from " << source << " to " << destination << " is " << dis << "-edge away." << endl;
            cout << "The path back to the source vertex: " << endl;
            char nextVertex = destination;
            cout << destination;
            while (go_through[nextVertex] != source)
            {
                cout << " ---> " << go_through[nextVertex];
                nextVertex = go_through[nextVertex];
            }
            cout << " ---> " << source << endl;
        }   
    }

    cout << "Thank you for using this program, bye..." << endl;
    return 0;
}

