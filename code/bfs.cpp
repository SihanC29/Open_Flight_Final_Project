#include "bfs.h"
#include <climits>

using namespace std;

BFS::BFS(string &airportFile, string &routeFile){
    graph = Graph(airportFile, routeFile);
}


vector<string> BFS::converts(int sourceAP){
    vector<string> ans;
    vector<bool> visited(14111, false);
    
    //initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS
    while (!queue.empty()) {
        currentAP = queue.front();
        ans.push_back(graph.getAPName(currentAP));
        for (auto it : graph.adjVertWithWeight(currentAP)) {
            if (!visited[it.first]) {
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    return ans;
}



vector<string> BFS::moves(int sourceAP, int moves) {
    vector<string> ans;
    vector<bool> visited(14111, false);
    
    //initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS
    while (!queue.empty()) {
        if(ans.size() == (unsigned)moves + 1)
            return ans;
        currentAP = queue.front();
        ans.push_back(graph.getAPName(currentAP));
        for (auto it : graph.adjVertWithWeight(currentAP)){
            if (!visited[it.first]) { 
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }

    return ans;
}


vector<string> BFS::dest(int sourceAP, int destAP) {
    vector<string> ans;
    vector<bool> visited(14111, false); // In total 14111 different airports included in our dataset
    
    //initialization
    queue<int> queue;
    queue.push(sourceAP);
    int currentAP = sourceAP;
    visited[currentAP] = true;
    
    //BFS
    while (!queue.empty()) {
        currentAP = queue.front();
        if(currentAP == destAP){
            ans.push_back(graph.getAPName(currentAP));
            break;
        }
        ans.push_back(graph.getAPName(currentAP));
        for (auto it : graph.adjVertWithWeight(currentAP)) {
            if (!visited[it.first]) { 
                queue.push(it.first);  
                visited[it.first] = true;
            }
        }
        queue.pop();
    }
    if(currentAP != destAP)
        return vector<string> ();
    return ans;
}