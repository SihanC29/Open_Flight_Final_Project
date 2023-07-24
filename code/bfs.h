#pragma once
#include "airportGraph.h"
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <vector>

using namespace std;

class BFS {
    public:
        /** Constructor: calls graph constructor
         * @param airportFile airport file
         * @param routeFile routes file
        **/
        BFS(string &airportFile, string &routeFile);

        /** Traversal in BFS order
         * @param sourceAP source airport
         * Return a vector of string of the traversed airports
        **/
        vector<string> converts(int sourceAP);

        /** Traversal in BFS order
         * @param sourceAP source airport
         * @param moves given number of moves
         * Return a vector of string of the traversed airports up to given moves
        **/
        vector<string> moves(int sourceAP, int moves);

        /** Traversal in BFS order
         * @param sourceAP source airport
         * @param destAP given destination
         * Return a vector of string of the traversed airports up to given destination
         * Return an empty vector if no path
        **/
        vector<string> dest(int sourceAP, int destAP);
    
    private:
        Graph graph;
};