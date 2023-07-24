#include "Flight.h"
#include <limits.h>

Flight::Flight(){
    sourceAP = -1;
    destinationAP = -1; 
    weight = INT_MAX;
};



Flight::Flight(int s, int d){
    sourceAP = s;
    destinationAP = d; 
    weight = INT_MAX;
};


Flight::Flight(int s, int d, double w){
    sourceAP = s;
    destinationAP = d; 
    weight = w;
};


int Flight::getSourceId() {
    return sourceAP;
}


int Flight::getDestId() {
    return destinationAP;
}


double Flight::getWeight() {
    return weight;
}


void Flight::setWeight(double w) {
    weight = w;
}

void Flight::setSource(double s) {
    sourceAP = s;
}

void Flight::setDestination(double d) {
    destinationAP = d; 
}


bool Flight::operator<(const Flight& other) const {
    return weight < other.weight;
}


bool Flight::operator==(Flight& other) const {
    if (sourceAP != other.sourceAP)
        return false;
    if (destinationAP != other.destinationAP)
        return false;
    return true;
}