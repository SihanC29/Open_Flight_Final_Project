#include "djikstras.h"
#include <map>
#include <climits>
#include <stack>

using namespace std;


bool Djikstras::vertexExists(string node) {
    if (adjacencyList.find(node) == adjacencyList.end()) {
        return false;
    }
    return true;
}


vector<pair<int, double>> Djikstras::getAdjacent(string source) {
    auto lookup = adjacencyList.find(source);
    vector<string> result;

    if (lookup == adjacencyList.end())
        return vector<pair<int,double>>();

    else {
        vector<pair<int,double>> vertex_list;
        unordered_map<int, Flight> &map = adjacencyList.at(source);
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(make_pair(it->first, it->second.getWeight()));
        }
        return vertex_list;
    }
}


Djikstras::Djikstras(Graph g, string StartAirport, string DestAirport) {
    path_vertices.clear();
    vector<string> vertices;  

    unordered_map<int, Airport> airportMap = g.getVertices();

    for (auto it = airportMap.begin(); it != airportMap.end(); ++it) {
        vertices.push_back(it->second.getName());
        if(it->second.getName() == StartAirport) {
            distances.insert(make_pair(it->second.getName(), 0.0));
            prevNodes.insert(make_pair(it->second.getName(), ""));
            visited.insert(make_pair(it->second.getName(), false));
        }
        else {
            distances.insert(make_pair(it->second.getName(), INT_MAX));
            prevNodes.insert(make_pair(it->second.getName(), ""));
            visited.insert(make_pair(it->second.getName(), false));
        }
    }
    pair<double,string> initial = make_pair(0.0, StartAirport);
    prQueue.push(initial);

    for (auto it = airportMap.begin(); it != airportMap.end(); ++it) {
        adjacencyList.insert(make_pair(it->second.getName(), it->second.m));
    }

    while (prQueue.top().second != DestAirport) {
        pair<double, string> currentNode = prQueue.top();
        prQueue.pop();
        vector<pair<int , double>> neighbors = getAdjacent(currentNode.second);
        vector<pair<string, double>> neighborNames;
        for (auto each : neighbors) {
            for (auto it = airportMap.begin(); it != airportMap.end(); ++it) {
                if (each.first == it->first) {
                    neighborNames.push_back(make_pair(it->second.getName(), each.second));
                }
            }
        }
        for (auto neighbor : neighborNames) {
            if (visited[neighbor.first] == false && visited[currentNode.second] == false) {
                double weight = neighbor.second;
                if(weight + distances[currentNode.second] < distances[neighbor.first]) {
                    distances[neighbor.first] = weight + distances[currentNode.second];
                    prevNodes[neighbor.first] = currentNode.second;
                    prQueue.push(make_pair(distances[neighbor.first], neighbor.first)); 
                }
            }
        }
        visited[currentNode.second] = true;
    }
 
    path = distances[DestAirport];

    string key = DestAirport;
    path_vertices.push_back(DestAirport);
    while(key != StartAirport) {
        path_vertices.push_back(prevNodes[key]);
        key = prevNodes[key];
    }
    std::reverse(path_vertices.begin(), path_vertices.end());
}


double Djikstras::getShortestDistance() const {
  return path;
}


vector<string> Djikstras::getPathVertices() const {
  return path_vertices;
}