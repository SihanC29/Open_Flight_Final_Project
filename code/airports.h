#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "Flight.h"

using namespace std;

class Airport {
    public:
        /**Default contructor
         * Set private variables to empty strings, int to 0, and double to 0.0
        **/
        Airport();   


        /** Constructor with variables
         *  @param id Unique OpenFlights identifier for this airport
         *  @param name Name of airport
         *  @param city Main city served by airport
         *  @param country Country or territory where airport is located
         *  @param latitude Decimal degrees. Negative is South, positive is North
         *  @param longitude Decimal degrees. Negative is West, positive is East
         * Can be used as an adjacency list: ID of adjacent airport and corresponding flight
        **/
        Airport(int id, string name, string city, string country, double latitude, double longitude);


        /** Contructor with dataset
         * @param line input dataset
         * Seperate airport information by comma, then construct a vector
         * Quotes are not included
         * The ending '\n' is not inlucded in the input line
        **/
        Airport(string & line);


        /** Constructor with vector input
         * @param airport
         * The vector must be in right order
        **/
        Airport(vector<string> airport); 

        /**
         * Getters
        **/
        int getID();
        string getName();
        string getCity();
        string getCountry();
        double getLatitude();
        double getLongitude();

        unordered_map<int, Flight> m;

    private:
        int id_;
        string name_;
        string city_;
        string country_;
        double latitude_;
        double longitude_;
        
};