#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "airports.h"
#include "PageRank.h"
#include "airportGraph.h"
#include "djikstras.h"
#include "bfs.h"

using namespace std;


int main() {
    cout << "                                    "<< endl;
    cout << "CS225 Final Project: OpenFlights" << endl;
    cout << "Team member: mingqiw2, jingyud2, lingyiz4, sihanc6" << endl;
    
    while (true) {
        string airportFile;
        string routesFile;
        string StartingAirport;
        string DestinationAirport;
        
        bool validDataset = false;
        
        while(validDataset == false){
            cout << "Enter \"default\" to construct graph using datasets from OpenFlights.org \nor enter name of airports dataset" << endl;
            string airportIn;
            cin >> airportIn;
            if(airportIn != "default"){
                airportFile = airportIn;
                cout << "\nEnter name of routes dataset" << endl;
                string routesIn;
                cin >> routesIn;
                string routesFile = routesIn;
                Graph airportGraph(airportFile, routesFile);
                
                if(airportGraph.getVertices().size() == 0){
                    cout << "\nEmpty graph constructed. Please try different input:" << endl;
                }else
                    validDataset = true;
            }
            else{
                validDataset = true;
                airportFile = "data/airports.dat";
                routesFile = "data/routes.dat";
            }
        }

        Graph airportGraph(airportFile, routesFile);
        unordered_map<int, Airport> verticesInGraph = airportGraph.getVertices();

        
        cout << "Enter a number to select an operation:" << endl;
        cout << "(0) Using BFS, traverse all of the graph from a given airport " << endl;
        cout << "(1) Using BFS, traverse a given number of moves of the graph from a given airport" << endl;
        cout << "(2) Using BFS, traverse the graph until reaching the destination airport from a given airport" << endl;
        cout << "(3) Calculate the shortest path between two airports" << endl;
        cout << "(4) PageRank" << endl;

        int mode; 
        cin >> mode;
         
        bool validSource = false;

        switch (mode)
        {
            case 0:{
                validSource = false;
                while (validSource == false) {
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if (it != verticesInGraph.end()) {

                        validSource = true;
                        BFS BFS(airportFile, routesFile);
                        vector<string> result_all = BFS.converts(sourceAP);
                        string sourceAPName = it->second.getName();
                        cout << "\nID " << sourceAP << " " << sourceAPName << "\n";
                        cout << "Printing out traversal from " << sourceAPName << ": " << endl;
                        for (unsigned i = 0; i < result_all.size(); i++){
                            cout << result_all[i] << " --> ";
                        }
                        break;
                    } else {
                        cout << "Source airport ID is not found in the graph. Please input a valid ID." << endl;
                    }
                }
                break;
            }


            case 1:{
                validSource = false;
                while(validSource == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if(it != verticesInGraph.end()){
                        validSource = true;
                        cout << "Enter moves to traverse:" << endl;
                        int moves;
                        cin >> moves;
                        BFS BFS(airportFile, routesFile);
                        vector<string> resultMoves = BFS.moves(sourceAP, moves);
                        string sourceAPName = it->second.getName();
                        cout << "Printing out first " << moves << " moves from " << sourceAPName << ": " << endl;
                        for (unsigned i = 0; i < resultMoves.size(); i++){
                            cout << resultMoves[i];
                            if (i != resultMoves.size() - 1) {
                                cout << " --> ";
                            }
                        }
                        break;
                    } else {
                        cout << "Source airport ID is not found in the graph. Please input a valid ID." << endl;
                    }
                }
                break;
            }


        
            case 2:{
                bool validAP = false;
                while(validAP == false){
                    cout << "Enter a source airport ID:" << endl;
                    int sourceAP; 
                    cin >> sourceAP;
                    auto it = verticesInGraph.find(sourceAP);
                    if (it != verticesInGraph.end()){
                        string sourceAPName = it->second.getName();
                        cout << "Start: ID " << sourceAP << " " << sourceAPName << endl;
                        cout << "Enter a destination airport ID:" << endl;
                        int destAP; 
                        cin >> destAP;
                        auto it2 = verticesInGraph.find(destAP);
                        if (it2 != verticesInGraph.end()){
                            validAP = true;
                            BFS BFS(airportFile, routesFile);
                            vector<string> resultDest = BFS.dest(sourceAP, destAP);
                            string destAPName = it2->second.getName();
                            cout << "Destination: ID " << destAP << " " << destAPName << endl;
                            cout << "Printing out traversal from " << sourceAPName << " to " << destAPName<< ": " << endl;
                            for (unsigned i = 0; i < resultDest.size(); i++){
                                cout << resultDest[i];
                                if (i != resultDest.size() - 1) {
                                    cout<< " --> ";
                                }
                            }
                        } else {
                            cout << "Valid source airport ID but invalid destination airport ID, please enter a valid destination airport ID" << endl;
                        }
                    } else {
                        cout << "Invalid source airport ID, please enter a valid source airport ID" << endl;
                    }
                } 
                break;
            }


            case 3:{
                string start; 
                cout << "Enter the name of source airport name, \nor enter 'default' to use 'Beijing Capital International Airport' as start and 'John F Kennedy International Airport' as end:\n";
                
                cin.ignore();
                getline(std::cin, start);

                if (start == "default") {
                    Djikstras shortestpath = Djikstras(airportGraph, "Beijing Capital International Airport", "John F Kennedy International Airport");
                    vector<string> path = shortestpath.getPathVertices();
                    double distance = shortestpath.getShortestDistance();

                    cout << "Airports Visited: \n" << endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if(i != path.size()-1)
                            cout<< " --> ";
                        if(i % 4 == 0 && i != 0)
                            cout << "" << endl;
                    }
                    cout<<""<<endl;
                    cout<<"Total Distance: "<< distance << " KM" << endl;
                } else {
                    cout << "Enter the end location: \n";
                    string end; 
                    getline(std::cin, end);
                    Djikstras shortestPath = Djikstras(airportGraph, start, end);
                    vector<string> path = shortestPath.getPathVertices();
                    double distance = shortestPath.getShortestDistance();
                    if(distance == 0.0){
                        cout<< "One or more airport not found!"<<endl;
                        break;
                    }
                    cout << "Airports Visited: \n" << endl;
                    for (unsigned long i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if (i != path.size() - 1) {
                            cout<< " --> ";
                        }
                    }
                    cout << "\nTotal Distance: "<< distance << " KM" << endl;
                }
                break;
            }

            case 4:{
                if (true) {
                    PageRank *test = new PageRank();                      //create pagerank obj
                    airportGraph.adjMatrix(test);                         //generate initial adjmatrix from graph
                    test->makeA(test->num, 0.85);                         //finalize adjmatrix
                    vector<double> initial = test->initialVector();      //generate initial vector 
                    vector<double> re = test->rank(initial, 100, false);           //perform pagerank alg, 100 iteration                        
                    cout << "\nEnter the number of the most important airport to be printed: \n";
                    int top;
                    cin >> top; 
                    vector<int> id_rank = test->topAirport(top);           //pickout the top top important airport        
                }
                break;
            }
        }
        cout << "\n\nComputation finished, restarting the program automatically. Press Control+C to stop the program.\n "<< endl;
    }
    return 0;
}