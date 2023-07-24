#pragma once
#include <vector>

using namespace std;


//pagerank class
class PageRank
{
  public:
    /** Adjust adjacent matrix
     * @param num Dimension of matrix
     * @param damping Damping factor
     * Modified adjmatrix according to damping factor, set num of the pagerank object
    **/
    void makeA(int num, double damping);


    /** Perform pagerank
     * @param initial Starting vector
     * @param time Time of iteration
     * @param normalize Perform normalize when true
    **/
    vector<double> rank(vector<double> initial, int time, bool normalize);



    /** Pick out the most important airport
     * @param num Top number of airport
     * Return the vector contains the id of the airports
    **/
    vector<int> topAirport(int num);


    // Generate starting vector
    vector<double> initialVector();

    // Print adjmatrix
    void printAdjMatrix();

    // Print the result vector
    void printResult();

    // The adj matrix variable, for pagerank
    vector<vector<double>> adjVec; 

    // The namelist of the airport. contains the airport id
    vector<int> nameList; 

    // The pagerank result
    vector<double> prResult;

    // Dimension of the adjcent matrix, namelist, initial vector and result vector
    int num;
};