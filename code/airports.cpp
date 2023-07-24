#include "airports.h"
#include <string>

using namespace std;

Airport::Airport(){
    id_ = 0;
    name_ = "";
    city_ = "";
    country_ = "";
    latitude_ = 0.0;
    longitude_ = 0.0;
}

Airport::Airport(int id, string name, string city, string country, double latitude, double longitude)
: id_(id), name_(name), city_(city), country_(country), latitude_(latitude), longitude_(longitude) { }

Airport::Airport(string & line){
    bool Flag = false;
    string str = "";
    vector<string> v;

    for(size_t i = 0; i < line.size(); ++i){
        char current = line[i];

        if (Flag) {
            if (current == '"') {
                if (i + 1 < line.size()) {
                    if(line[i + 1] == '"') {
                        str += '"';
                        i++;
                    }
                    else {
                        Flag = false;
                    }
                }
            }
            else {
                str += current;
            }
        }
        else {
            if (current == ',') {
                v.push_back(str);
                str = "";
            }
            else if (current == '"') {
                Flag = true;
            }
            else {
                str += current;
            }
        }
    }   
    //updating
    id_ = stoi(v[0], NULL);
    name_ = v[1];
    city_ = v[2];
    country_ = v[3];
    latitude_ = stod(v[6], NULL);
    longitude_ = stod(v[7], NULL);
}

Airport::Airport(vector<string> airport){
    id_ = stoi(airport[0], NULL);
    name_ = airport[1];
    city_ = airport[2];
    country_ = airport[3];
    latitude_ = stod(airport[6], NULL);
    longitude_ = stod(airport[7], NULL);
}


int Airport::getID() {
    return id_;
}
string Airport::getName() {
    return name_;
}
string Airport::getCity() {
    return city_;
}
string Airport::getCountry() {
    return country_;
}
double Airport::getLatitude() {
    return latitude_;
}
double Airport::getLongitude() {
    return longitude_;
}

