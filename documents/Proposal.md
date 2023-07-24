## Leading Question 
In this project, we will explore [OpenFlights](https://openflights.org/data.html) dataset to understand how people in the world can be efficiently connected by airlines. Using the algorithms described below, a real life application would be able to generate a planned route to find the shortest path from one place to one place, visiting all the famous places in the world, ect. We plan to find the the shortest path between two locations, by using the nearest airports corresponding to each country. 

## Dataset Acquisition

#### Data Format:
We download our datasets(airports.dat and routes.dat) from [OpenFlights](https://openflights.org/data.html). Both datasets are UTF-8 encoded and formatted as common-seperated values(csv). Airports.dat contains 5888 airports, and each entry contains airport ID, name, city, country, IATA, ICAO, latitude, longitude, altitude, timezone, DST, Tz database timezone, type, and source. Routes.dat contains 67663 routes between 3321 airports on 548 airlines spanning the globe, each entry contains airline, airline ID, source airport, source airport ID, destination airport, destination airport ID, codeshare, stops, and equipments. 

#### Data Correction:
Instead of using C++, we will use Python Pandas libarary to clean our data before we implement those data into our project. We will not use the whole data since we only care about some information related to airport and route. First of all, we will correct airport data. We will use Pandas built in functions to find all entries with null IATA code and delete those missing values, since we should use IATA code to identify the airport. Also, we will delete some useless coloumns to make our data smaller, such as "type" and "source". Then we will correct the route data. Since we only care about the shortest distance, we will delete all entries will non 0 "stop". We will also delete useless coloumns in route dataset, such as "equipment". After that, we believe our data can be succssfully implemented in our project. However, we will consider to use regular expression to correct columns like "name" if necessary.

#### Data Storage:
We will store airports as nodes, routes as edges, distance as weight. We will first parse each source and destination airport and calculate the distance between them. After that, we will sum the distance and find the shortest distance. If an error occurs due to invalid data, we would ignored the faulty data. Then we use PageRank algorithm to generate a matrix which contains vectors with information of each airport. Finally we will traverse through our graph to retrieve the information of desired airports and map them into a world map. The estimate of the total storage costs is O(n+m), where n is number of nodes and m is number of edges.

## Algorithm 
we will use Djikstra’s shortest path algorithm to find the shortest path between any two airports. Using min-priority queue, the runtime of Djikstra’s will be O(V+E logV). V is the number of vertices, and E is the number of edges. Since we will use BFS traversal for our project, the space complexity will be O(V+E). Before using Djikstra's algorithm, we will construct a weighted graph, as airports being nodes, airlines being edges, and distance being weight. Input of Djikstra's algorithm will be the weighted graph, and the output will produce a shortest-path tree.Input will be the weighted graph translated from dataset, output will be a weighted graph contains shortest distance. 

## Timeline
Nov 19th: Have dataset processed, start working on tranfer it to graph.

Nov 22nd: Have Djikstra's written.

Nov 28nd: Finish the other algorithm if necessery. Working on test.

Dec 7th: Finish the whole project
