#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "airports.h"
#include "PageRank.h"

using namespace std;

class Graph {
    public:
        /**
         * Default constructor
        **/
        Graph();

        
        /** Constructor with dataset input
         * @param airportFile Dataset with airport information
         * @param routesFile Dataset with routes information
         * Using two helper
        **/
        Graph(string & airportFile, string & routesFile);
        

        /** Connect each airport with its ID
         * @param ver vertex
         * @param air airport
         * Construct vertices
        **/
        void insertVertex(int ver, Airport air);


        /** Insert airport.dat line by line
         * @param fileName Name of dataset
         * Only works with all 14 variables
        **/
        void insertAllVertices(string & fileName);
        

        /** Helper function that converts a line of information to vector
         *  @param line Airport information
         * Seperate information by comma
         * If input line has less than 8 variables, return empty vector
        **/
        vector<string> _createEdge(string & line);


        /** Helper function that converts above vector to edge
         *  @param flightVector Output from _createEdge
        **/
        Flight createEdge(vector<string> flightVector);     


        /** Insert single edge
         *  @param f Edge
         * Using above two helper functions
        **/
        void insertEdge(Flight f);


        /** Insert all edge
         *  @param fileName route.dat
         * Insert flight for all lines
        **/
        void insertAllEdge(string & fileName);
        

        //Return unordered_map of airports 
        unordered_map<int, Airport> getVertices();


        //returns the flights coming out of the given airport
        unordered_map<int, Flight> adjVertWithWeight(int airportID);


        //Return the name of the airport
        string getAPName(int ID);
        

        //get adjmatrix from a graph obj
        void adjMatrix(PageRank* obj);


    private:
        /** Helper function to calculte weight
         *  @param degree 
        **/
        double radianConvert(double degree);


        /** Calculate distance between two places
         *  @param fromID Id of the airport 
         *  @param toID Id of another airport
        **/
        double calcWeight(int fromID, int toID);
        
        
        //each graph object hosts a map of airports to its corresponding ID
        unordered_map<int, Airport> vertices;
};