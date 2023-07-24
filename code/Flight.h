#pragma once

class Flight {
    public:
        //Default constructor
        Flight();

        /** Constructor without weight
         * @param s sourceAP
         * @param d destination
         * Set weight to infinite
        **/
        Flight(int s, int d);


        /** Constructor with all variables
         * @param s sourceAP
         * @param d destination
         * @param w weight
        **/
        Flight(int s, int d, double w);

        //getters
        int getSourceId();       
        int getDestId();         
        double getWeight();
       
        //setters
        void setWeight(double w);
        void setSource(double s);
        void setDestination(double d); 


        //Operator overloading, comparing weight of edges in later algorithms
        bool operator<(const Flight& other) const;
        //Operator overloading, checking if two edges are the same in later algorithms
        bool operator==(Flight& other) const;
    
    private:
        //Airport ID
        int sourceAP;
        //Destination airport ID
        int destinationAP;
        //Distances in KM between two airports
        double weight;
};