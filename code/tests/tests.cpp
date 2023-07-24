#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>


#include "../airports.h"
#include "../PageRank.h"
#include "../airportGraph.h"
#include "../djikstras.h"
#include "../bfs.h"

#include "../cs225/catch/catch.hpp"


using namespace std;



TEST_CASE("Testing Airport constructor with vector") { 

    //507,"London Heathrow Airport","London","United Kingdom","LHR","EGLL",51.4706,-0.461941,83,0,"E","Europe/London","airport","OurAirports"

    unordered_map<string, Airport> vertices;
    cout<<"Testing vector constructor with London Heathrow airport"<<endl;
    vector<string> airport_data = {"507","London Heathrow Airport","London","United Kingdom", "", "", "51.4706", "-0.461941"};
    vertices["London Heathrow Airport"] = Airport(airport_data);
    int ID = vertices["London Heathrow Airport"].getID();
    string Name = vertices["London Heathrow Airport"].getName();
    string City = vertices["London Heathrow Airport"].getCity();
    string Country = vertices["London Heathrow Airport"].getCountry();
    int Latitude = (int)vertices["London Heathrow Airport"].getLatitude();
    int Longitude = (int)vertices["London Heathrow Airport"].getLongitude();

    REQUIRE(507 == ID);
    REQUIRE("London Heathrow Airport" == Name);
    REQUIRE("London" == City);
    REQUIRE("United Kingdom" == Country);
    REQUIRE(51 == Latitude);
    REQUIRE(0 == Longitude);
}


TEST_CASE("Testing Airport constructor with string") { 

    unordered_map<string, Airport> vertices;

    cout<<"Testing string constructor with Agra Airport"<<endl;
    string agra = "3079,\"Agra Airport\",\"Agra\",\"India\",\"AGR\",\"VIAG\",27.155799865722656,77.96089935302734,551,5.5,\"N\",\"Asia/Calcutta\",\"airport\",\"OurAirports\"";
    vertices["Agra Airport"] = Airport(agra);
    int ID = (vertices["Agra Airport"].getID());
    string Name = (vertices["Agra Airport"].getName());
    string City = (vertices["Agra Airport"].getCity());
    string Country = (vertices["Agra Airport"].getCountry());
    int Latitude = (int)vertices["Agra Airport"].getLatitude();
    int Longitude = (int)vertices["Agra Airport"].getLongitude();
    

    REQUIRE(3079 == ID);
    REQUIRE("Agra Airport" == Name);
    REQUIRE("Agra" == City);
    REQUIRE("India" == Country);
    REQUIRE(27 == Latitude);
    REQUIRE(77 == Longitude);
}

	
TEST_CASE("Testing Pagerank function topAirport()") { 
    cout << "\n\n\n\n >>>>>>>>Testing Pagerank function topAirport()\n" << endl;
    //construct a pagerank obj, manually setup the nameList and prResult
    PageRank *test = new PageRank(); 
    test->nameList.resize(5);
    test->prResult.resize(5);

    test->nameList[0] = 0;
    test->nameList[1] = 1;
    test->nameList[2] = 2;
    test->nameList[3] = 3;
    test->nameList[4] = 4;

    test->prResult[0] = 0.245;
    test->prResult[1] = 324.15;
    test->prResult[2] = 23.21;
    test->prResult[3] = 56.33;
    test->prResult[4] = 4;

    //pick out the top 3 airport's id
    vector<int> rank = test->topAirport(3); 
    REQUIRE(1 == rank[0]);
    REQUIRE(3 == rank[1]);
    REQUIRE(2 == rank[2]);
}


TEST_CASE("Testing Pagerank function makeA()") {
    PageRank *test = new PageRank();

    int size = 2;
    test->adjVec.resize(size,vector<double>(size));

    //to test normalize(column sum == 1)
    test->adjVec[0][0] = 0.0;
    test->adjVec[1][0] = 0.0;

    //to test normalize and dampling factor
    test->adjVec[0][1] = 4.0;   
    test->adjVec[1][1] = 6.0;  

    test->nameList.resize(size);
    test->num = size;

    test->PageRank::makeA(size, 0.85);
    REQUIRE(0.5 == test->adjVec[0][0]);
    REQUIRE(0.5 == test->adjVec[1][0]);
    REQUIRE(1 == test->adjVec[0][1] + test->adjVec[1][1]);
}


TEST_CASE("Testing Pagerank function rank()") { 
    cout << "\n\n\n\n >>>>>>>>Testing Pagerank function rank()\n" << endl;
    PageRank *test = new PageRank();

    int size = 10;
    test->adjVec.resize(size,vector<double>(size));

    test->nameList.resize(size);
    test->num = size;

    //set only one edge from id:1 to id:0. Thus the id:0 should be the most important
    for(int i = 0; i < size; i++){
        test->nameList[i] = i;
        for(int j = 0; j < size; j++){
            test->adjVec[i][j] = 0.0;
        }        
    }
    test->adjVec[0][1] = 10;

    test->PageRank::makeA(size, 0.85);
    vector<double> initial = test->PageRank::initialVector();
    vector<double> temp = test->PageRank::rank(initial, 50, true);
    vector<int> rank = test->topAirport(1); 
    REQUIRE(0 == rank[0]);
}


TEST_CASE("Testing Pagerank implementation on a subset of the whole data set") { 
    //adjust the precision of the weight of edge to be shown
    cout << setprecision(10);
    cout << "\n\n\n\n >>>>>>>>Testing constructing graph from a subset of data and pagerank on the data set\n" << endl;
    string airportFile = "tests/airport_sample.dat";
    string routesFile = "tests/routes_sample.dat";
    Graph airportGraph(airportFile, routesFile);
    unordered_map<int, Airport> airportMap = airportGraph.getVertices();

    //printing out all flights departing from O'Hare, Newark and Beijing airport
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        cout << "Airport ID: " << it->first <<endl;
        if(it->first == 3830 || it->first == 3494 || it->first == 3364){
            cout << "Airport ID: " <<it->second.getID() << " ";
            cout << "Airport Name: " <<it->second.getName() << endl;

            unordered_map<int, Flight> adjList = it->second.m;
            for(auto it = adjList.begin(); it != adjList.end(); ++it){
                cout << "Source ID: " << it->second.getSourceId() << " ";
                cout << "Destination ID: " << it->second.getDestId() << " ";
                cout << "Flight weight: " << it->second.getWeight() << endl;
            }
        }
    }
    cout << "\n";
    PageRank *test = new PageRank();                      //create pagerank obj
    airportGraph.adjMatrix(test);                         //generate initial adjmatrix from graph
    test->makeA(test->num, 0.85);                         //finalize adjmatrix
    test->printAdjMatrix();                              //print adjVec
    vector<double> initial = test->initialVector();      //generate initial vector 
    vector<double> re = test->rank(initial, 100, true);           //perform pagerank alg, 5 iteration
    test->printResult();                                 //print result
    vector<int> id_rank = test->topAirport(5);           //pickout the top 5 important airport

    REQUIRE(3364 == id_rank[0]);
    REQUIRE(3728 == id_rank[1]);
}


TEST_CASE("Testing constructing whole graph") {
    string airportFile = "data/airports.dat";
    string routesFile = "data/routes.dat";
    Graph airportGraph(airportFile, routesFile);
    unordered_map<int, Airport> airportMap = airportGraph.getVertices();
    cout << "Number of airports: " << airportMap.size() <<endl;

    //printing out all flights departing from O'Hare, Newark and Beijing airport
    for(auto it = airportMap.begin(); it != airportMap.end(); ++it){
        //cout << "Airport ID: " << it->first <<endl;
        if(it->first == 3830 || it->first == 3494 || it->first ==3364){
            cout << "Airport ID: " <<it->second.getID() << " ";
            cout << "Airport Name: " <<it->second.getName() << endl;

            unordered_map<int, Flight> adjList = it->second.m;
            for(auto it = adjList.begin(); it != adjList.end(); ++it){
                cout << "Source ID: " << it->second.getSourceId() << " ";
                cout << "Destination ID: " << it->second.getDestId() << " ";
                cout << "Flight weight: " << it->second.getWeight() << endl;
            }
        }
    }
    REQUIRE(7000 <= airportMap.size());
}


TEST_CASE("Testing BFS_moves") {
    
    cout << "testing BFS_moves" << endl;
    string airportFile = "data/airports.dat";
    string routesFile = "data/routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> resultMoves = myBFS.moves(3830, 50);
    cout << "Printing out first 50 moves from O'Hare airport" << endl;
    for(unsigned i = 0; i < resultMoves.size(); i++){
        cout << resultMoves[i] ;
        if(i != resultMoves.size()-1)
            cout << " --> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout << endl;

    REQUIRE(51 == resultMoves.size());
    REQUIRE("Chicago O'Hare International Airport" == resultMoves[0]);
}

TEST_CASE("Testing BFS_dest") {
    cout << "testing BFS_dest" << endl;
    string airportFile = "data/airports.dat";
    string routesFile = "data/routes.dat";    
    BFS myBFS(airportFile, routesFile);
    vector<string> resultDest = myBFS.dest(3830, 3494);
    cout << "Printing out traversal from O'Hare to Newark" << endl;
    for(unsigned i = 0; i < resultDest.size(); i++){
        cout << resultDest[i] ;
        if(i != resultDest.size() - 1)
            cout << " --> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout << endl;

    
    REQUIRE("Chicago O'Hare International Airport" == resultDest[0]);
}



TEST_CASE("Testing Djikstra's algorithm with BFS") { 

    cout << "Testing Djikstra's algorithm with BFS" << endl;
    string airportFile = "data/airports.dat";
    string routesFile = "data/routes.dat";
    string StartingAirport;
    string DestinationAirport;
    Graph airportGraph(airportFile, routesFile);
    Djikstras shortestpath = Djikstras(airportGraph, "Chicago O'Hare International Airport", "Newark Liberty International Airport");

    vector<string> path = shortestpath.getPathVertices();
    double distance = shortestpath.getShortestDistance();

    cout<<"Airports Visited: \n"<<endl;
    for (unsigned long i = 0; i < path.size(); i++) {
        cout << path[i] ;
        if(i != path.size()-1)
            cout << " --> ";
        if(i%5 == 0 && i != 0)
            cout << endl;
    }
    cout<<endl;
    cout<<"Total Distance: "<<distance<<endl;

    BFS BFS(airportFile, routesFile);
    vector<string> result_dest = BFS.dest(3830, 3494);

    REQUIRE("Chicago O'Hare International Airport" == path[0]);
    unsigned length = path.size();
    REQUIRE("Newark Liberty International Airport" == path[length-1]);
    REQUIRE(result_dest.size() >= path.size());

}