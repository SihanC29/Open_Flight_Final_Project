# CS 225 Final Project - OpenFlights

## Authors

- Mingqi Wang (`mingqiw2`)
- Sihan Cheng (`sihanc6`)
- Kelly Dai (`jingyud2`)
- Teresa Zhang (`lingyiz4`)

## Deliverables 

* [Report](https://github.com/MasterWMQ0121/cs225finalproject/blob/main/documents/CS225-Final-Report.pdf)
* [Presentation Video](https://www.youtube.com/watch?v=3nA9krTnOLI)
* [Presentation Slides](https://github.com/MasterWMQ0121/cs225finalproject/blob/main/documents/cs225_final_presentation.pdf)

## Algorithms: BFS, PageRank, Dijkstra's

## Data

We are using the [OpenFlights](https://openflights.org/data.html) data and focusing on the following two files:

- [airports.dat](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
- [routes.dat](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)

## Repo Structure

- All code files are located in the code folder
- All test cases are located in the tests folder
- All data sets are located in the data folder
- All presentation file, video, and report are located in the main page.

## Running Instructions

### Building the application 
Users can firstly download the zip file on their destop and type in the following command in the terminal to build the program.

```
make
./main
```

### Running the application
Our main function consists of 5 cases where the user can interact with the various parts of our project.  
The user can see the results of running a BFS traversal, Pagerank algorithm, and Djikstra's algorithm.

Then user will enter the following interface and choose to use the default datasets or use their own datasets:
```
CS225 Final Project: OpenFlights
Team member: mingqiw2, jingyud2, lingyiz4, sihanc6
Enter "default" to construct graph using datasets from OpenFlights.org 
or enter name of airports dataset
```

After making the choice, the user will choose which operation to run and enter the corresponding number:
```
Enter a number to select an operation:
(0) Using BFS, traverse all of the graph from a given airport 
(1) Using BFS, traverse a given number of moves of the graph from a given airport
(2) Using BFS, traverse the graph until reaching the destination airport from a given airport
(3) Calculate the shortest path between two airports
(4) PageRank
```

Then users can follow the instruction to provide custom input and retrieve the output in the terminal.
To end the program at at time, use `Ctrl+C`.

### Testing the application

Use the following code to run the test:
```
make test
./test
```  

Our tests test the functionality of
- construct an airport 
- construct a graph
- the BFS traversal
- the Pagerank algorithm
- Djikstra's algorithm

