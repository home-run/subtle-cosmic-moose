#include "graph.h"
#include <fstream>
#ifndef INF
#define INF INT_MAX - 10000
#endif

Graph::Graph()
{
    // Initialze the number of vertices in the graph to be 0
    this->numVertices = 0;

    // Initializes every weight in the adjacency matrix to be -1
    for(int i = 0; i < this->numVertices; i++)
    {
        for(int j = 0; j < this->numVertices; j++)
        {
            this->adjacencyMatrix[i][j] =    0;
        }
    }

}

/**
 * @brief Graph::~Graph
 * Deconstructor of the graph, clears the currently allocated edges and vertexList.
 */
Graph::~Graph()
{
    while(!edges.isEmpty())
    {
        this->edges.removeMin();
    }

    vertexList.clear();
}

/**
 * @brief Graph::createGraph
 * This method will generate the graph based on the given information and data stored in
 * the sqlite database. A list of vertices and an adjacency matrix will be created from
 * the method. This data will be stored within the graph object itself. The data is
 * provided by the Database object given upon calling the createGraph method.
 * @param db
 */
void Graph::createGraph(Database *db)
{
    QSqlQuery queryResult;		// Executes & stores the query for retrieving vertices
                                //		and edges from the database.
    Vertex vertex;				// Temporary vertex used as a factory for inserting
                                // 		Vertices into the graph.
    Edge edge;					// Temporary edge used as a factory for inserting
                                //		edges into the graph.
    int toId, fromId, weight, id;//	Integer values to store temporary To, From, Weight
                                //		and Current IDs
    QString stadiumName;		// Stores the name of the stadium for inserting into the
                                // 	graph

    numVertices = db->getNumberOfStadiums();

    if(!vertexList.isEmpty())
    {
        vertexList.clear();
    }
    // TODO: Clear graph in case that a new graph is needed when more stadiums have
    //	been added to the graph.

    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            adjacencyMatrix[i][j] = 0;
        }
    }

    // Calls on the database method that retrieves the SQL Query for access the stadium
    //	names and ids within the SQLite datbase
    queryResult = db->getStadiumsNameId();
    // While there still is a query record left within the query...
    while(queryResult.next())
    {
        // Get the ID field and convert it to int then store it in id
        id = queryResult.record().field("id").value().toInt() - 1;
        // Get the stadium name field and convert it to string then store it in the
        //	StadiumName variable
        stadiumName = queryResult.record().field("name").value().toString();
        // Take the vertex factory and set its values to the ID and Stadium Name from
        //	the database.
        vertex.setId(id);
        vertex.setName(stadiumName);
        vertexList.append(vertex);
    }


    // Executes a query from the database to get all the edges, ids and the
    //	corresponding weights
    queryResult = db->getEdges();

    while(queryResult.next())
    {
        toId = queryResult.record().field("id_to").value().toInt() - 1;
        fromId = queryResult.record().field("id_from").value().toInt() - 1;
        weight = queryResult.record().field("distance").value().toInt();

        int index = 0;
        bool found = false;
        while(index < numVertices && !found)
        {
            // If the the starting id of the edge matches the id of the vertex that it is
            //	current at create an edge object and add it to the adjacency list of the
            //	current vertex.
            if(vertexList.at(index).getId()== fromId)
            {
                edge.idFrom = fromId;
                edge.idTo = toId;
                edge.weight = weight;
                found = true;
                vertexList[index].addEdge(edge);
            }
            index++;
        }

        // Assign the weight of the edge to the adjacency matrix of the from id and the
        //	to id of th each vertex respectively.
        adjacencyMatrix[fromId][toId] = weight;
    }
}

/**
 * @brief Graph::getVertices
 * This method will return a copy of the list of vertices in the graph.
 * @return List of Vertices
 */
QList<Vertex> Graph::getVertices() const
{
    return this->vertexList;
}

/**
 * @brief Graph::edgeWeight
 * This method will return the weight between the given indices.
 * @param v1 vertex index 1
 * @param v2 vertex index 2
 * @return weight / distance between the 2 given vertices. Will return a value less than 0 if no edge exists.
 */
int Graph::edgeWeight(int v1, int v2)
{
    int returnWeight;
    // Error checking for if the vertices given are within the bounds of existing vertices in the adjacency matrix
    if(v1 > -1 && v2 > -1 && v1 < vertexList.size() && v2 < vertexList.size())
    {
        returnWeight = adjacencyMatrix[v1][v2];
    }
    else
    {
        // Else return -1
        returnWeight = -1;
    }
    return returnWeight;
}

/**
 * @brief Graph::initialize_single_source
 * For v = s, which is the source vertex that the single shortest path will begin at.
 * Initializes the label D[v] to 0 and all other D[u] to 9999 for each vertex
 * which u != v. Clears previously found distance and the list of previous parent ids.
 * @param s - source vertex which the single shortest path will begin at.
 */
void Graph::initialize_single_source(Vertex s)
{
    for(int vertex = 0; vertex < numVertices;vertex++)
    {
        vertexList[vertex].setDistance(INF);
        vertexList[vertex].setParent(-1);
    }
    vertexList[s.getId()].setDistance(0);
}

/**
 * @brief Graph::clearGraph
 * This method will go through and clear the adjacency matrix and the vertex list.
 */
void Graph::clearGraph()
{
    // ID From
    for(int i = 0; i < numVertices; i++)
    {
        // ID To
        for(int j = 0; j < numVertices; j++)
        {
            // Set the weight of edge to -1
            this->adjacencyMatrix[i][j] = 0;
        }
    }
    // Clear the list of vertices
    vertexList.clear();
}

/**
 * @brief Graph::debug_printAdjMatrix
 * This method is used for debugging purposes and printing the adjacency matrix when needed.
 * Will output the index pair and the represented edge weight between the vertices.
 */
void Graph::debug_printAdjMatrix() const
{
    std::ofstream myFile;
    myFile.open("matrix-output.txt");
    // ID From
    for(int i = 0; i < numVertices; i++)
    {
        // ID To
        myFile << "{ ";
        for(int j = 0; j < numVertices; j++)
        {
            // Output to the console the weight between the vertices
            qDebug() << "i : " << i << " " << vertexList.at(i).getName() << " - j : " << j << " "  << vertexList.at(j).getName() << " - weight : " << adjacencyMatrix[i][j];
            //            myFile << "{ " << i << ", " << j << ", " << adjacencyMatrix[i][j] << "}, ";
            myFile << adjacencyMatrix[i][j] << ", ";
        }
        myFile << "}\n";
    }
}

/**
 * @brief Graph::shortestPath
 * Given a source vertex find the shortest path to all other vertices available on the
 * graph. The function performs Dijkstra's algorithm to compute each of the distances.
 * Utilizes a Vertex Set, and a Priority Queue as data structures to improve the
 * performance of the search.
 * @param source
 */
void Graph::shortestPath(Vertex source)
{
    Heap<Vertex, vertexComp> vertexPQ;// Min-Heap (priority queue) containing all the
                            //	vertices in the graph, ordered by the weight. Smallest
                            //	weight is root
    VertexSet T;			// Contains the set of vertices to which the shortest path
                            //	has been found.
    Vertex u;
    Vertex v;
    Edge adjEdge;
    int distanceSum;

    for(int i = 0; i < numVertices; i++)
    {
        vertexList[i].setDistance(0);
    }

    source = vertexList.at(source.getId());
    // Initialize all edges, and vertices to infinity
    initialize_single_source(source);

    T.clear();
    // Initialize the priority queue to start with the given source vertex as the first
    //	vertex to explore.
    vertexPQ.insert(vertexList[source.getId()]);

    while(!vertexPQ.isEmpty())
    {
        u = vertexPQ.removeMin();
        // While the current vertex u has an adjacent edge available.
        while(vertexList.at(u.getId()).hasEdges() )
        {
            // Get the adjacent edge to the vertex. It will be the edge with the shortest
            //	path currently available
            adjEdge = vertexList[u.getId()].getNearestEdge();
            v = vertexList.at(adjEdge.idTo);
            // checks to see if a path between vertex u and vertex v exists. A path
            //	exists if the value in the adjacency matrix is not 0
            if(adjacencyMatrix[u.getId()][adjEdge.idTo] != 0 )
            {
                // Calculate the total distance between the vertex u and the weight
                //	between the vertex u and vertex v
                distanceSum = u.getDistance() + adjacencyMatrix[u.getId()][v.getId()];

                // If the current distance to vertex v is greater than the sum of u's
                //	current distance plus the weight in the adj matrix set the distance
                //	to v to the new distance sum because it is a shorter path to that
                //	vertex.
                if(v.getDistance() > distanceSum )
                {
                    v.setDistance(distanceSum);
                    v.setParent(u.getId());
                    vertexList[v.getId()] = v;
                }

                // If the set T of found vertices does not contain the vertex v add the
                //	vertex v to the priority queue to see the shorter path.
                if(!T.contains(v))
                {
                    vertexPQ.insert(v);
                }
            }
        }
    }
    // Once the algorithm is complete, clear the VertexSet T of all vertices.
    T.clear();
}

/**
 * @brief Graph::getTotalDistance
 * This method will the take the distances stored in each of the vertices after a search
 * for the shortest path has been performed.
 * @return
 */
long Graph::getTotalDistance() const
{
    long totalDistance = 0;
    for(int v = 0; v < numVertices; v++)
    {
        // Sum the total distance given at the vertex v to the total sum distance
        totalDistance += vertexList.at(v).getDistance();
    }
    return totalDistance;
}
/**
 * @brief Graph::getNumberVertices
 * Methd returns the number of vertices that are stored in the graph
 * @return Integer # of vertices in the graph
 */
int Graph::getNumberVertices() const
{
    return this->numVertices;
}

/**
 * @brief Graph::debug_outputDistances
 * Debugging function for output the name and the distance calculated after performing a
 * search.
 */
void Graph::debug_outputDistances() const
{
    for(int v = 0; v < numVertices; v++)
    {
        qDebug() << "Distance to [ " << vertexList.at(v).getName() << " ] is [ " << vertexList.at(v).getDistance() << " ]";
    }
}

/**
 * @brief Graph::debug_printPath
 * Debugging method for printing the path found to the given vertex. This will only work
 * after a search for the shortest path has been found.
 * @param vertex
 */
void Graph::debug_printPath(Vertex vertex) const
{
    int parentId;

    vertex = vertexList[vertex.getId()];
    parentId = vertex.getParent();

    qDebug() << "Ending stadium is " << vertex.getName();
    while(parentId > -1)
    {
        qDebug() << "Previous stadium is " << vertexList[parentId].getName();
        parentId = vertexList[parentId].getParent();
    }

}

/**
 * @brief Graph::findShortestPathTo
 * This is an overloaded method for find the shortest path between 2 vertices. It calls
 * on other methods such as creating the graph, finding the shortest path to all vertices
 * then getting the target vertex from the vertex list. After the algorithm has found
 * the shortest path, it will return a QList of vertices in which it is required to
 * traverse to get to the target vertex. The list will contain the starting vertex and
 * ending vertex. Each vertex will have a distance value it takes to get to that vertex
 * given the starting the vertex.
 * @param db
 * @param source
 * @param target
 * @return
 */
QList<Vertex> Graph::findShortestPathTo(Database *db, int source, int target)
{
    Vertex vertex;

    vertex = vertexList.at(source);
    createGraph(db);
    shortestPath(vertex);
    vertex = vertexList.at(target);
    return getVertexPath(vertex);

}
/**
 * @brief Graph::findShortestPathTo
 * This is an overloaded method for find the shortest path between a starting vertex,
 * and a list of vertices. It calls on other methods such as creating the graph,
 * finding the shortest path to all vertices then getting the target vertex from the
 * vertex list. After the algorithm has found the shortest path, it will return a
 * QList of vertices in which it is required to traverse to get to the target vertex.
 * The list will contain the starting vertex and ending vertex. Each vertex will have
 * a distance value it takes to get to that vertex given the starting the vertex.
 * @param db
 * @param source
 * @param stops
 * @return
 */
QList<Vertex> Graph::findShortestPathTo(Database *db, int source, QList<int> stops)
{
    QList<Vertex> foundPath;
    QList<Vertex> completePath;
    QList<Vertex>::iterator iter;

    // For every vertex (index) given that a path is wished to be taken.
    for(int i = 0; i < stops.size();i++)
    {
        createGraph(db);
        // Find the shortest path from the starting point currently at
        foundPath = findShortestPathTo(db, source, stops.at(i));

        // Within the path that was found
        for(int j = 0; j < foundPath.size();j++)
        {
            // Add each vertex in that path to the overall path to be returned.
            completePath.push_back(foundPath[j]);
        }

        // Set the new starting vertex as the previous ending vertex index.
        source = stops.at(i);
    }

    iter = completePath.begin();
    qDebug() << "Erasing vertices";
    iter++;
    for(int i = 1; i < completePath.size() ; i++)
    {
        if(completePath.at(i).getDistance() == 0)
        {
            qDebug() << "Erasing " << completePath.at(i).getName() << " with distance " << completePath.at(i).getDistance();
            completePath.erase(iter);
            --iter;
            --i;
        }
        iter++;
    }

    long nextDistance;
    long currentDistance;

    for(int index = 0; index < completePath.size() - 1; index++)
    {
        currentDistance = completePath.at(index).getDistance();
        nextDistance = completePath.at(index + 1).getDistance();
        qDebug() << "Current Distance " << currentDistance << " next distance " << nextDistance;

        if(currentDistance > nextDistance )
        {
            completePath[index + 1].setDistance(nextDistance + currentDistance);
        }
    }

    // Return the complete path found.
    return completePath;
}

/**
 * @brief Graph::getVertexPath
 * Function will take a given vertex and traverse up the path of the given parent ids
 * to construct the path that was taken to arrive at the target vertex. This method
 * will return a QList of vertices, where index 0 is the starting vertice and the last
 * vertex in the list is the given target vertex.
 * @param target Vertex
 * @return QList of Vertices
 */
QList<Vertex> Graph::getVertexPath(Vertex target)
{
    QList<Vertex> path;
    Vertex vertex;
    int parentId;

    vertex = vertexList[target.getId()];
    parentId = vertex.getParent();

    path.push_front(vertex);
    while(parentId > -1)
    {
        path.push_front(vertexList[parentId]);
        parentId = vertexList[parentId].getParent();
    }
    return path;
}

/**
 * @brief Graph::malik_minimumSpanningTree
 * This method will generate the minimum spanning tree given a starting vertex. It is
 * recommended not to start at index 0, 1, 22, or 29 to guarantee the most minimum
 * spanning tree possible in the given graph. Each vertex will store the parent of the
 * vertex that it had to traverse to get to.
 * @param source
 * @return long minimum distance between all vertices
 */
long Graph::minimumSpanningTree(int source)
{
    long *parent; 	// Array to store construted MST
    long *key;		// Key values used to pick minumum weight edge in cut
    bool *mstSet;	// To represent set of vertices not yet included MST


    mstSet = new bool[numVertices];
    parent = new long[numVertices];
    key = new long[numVertices];


    // Initialize all keys as INFINITE
    for(int i = 0; i < numVertices; i++)
    {
        key[i] = INF;
        mstSet[i] = false;
    }

    // Always include first lst vertex in MST.
    key[source] = 0;		// Make key 0 so that this vertex is picked as first vertex include first lst vertex in MST.
    parent[source] = -1;	// First node is always root of MST

    // The MST will have V vertices
    for(int count = 0; count < numVertices; count++)
    {
        // Pick the minimum key vertex from the set of vertices not yet included
        //	in the MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of the adjacent vertices of the picked
        //	vertex. Consider only those vertices which are not yet included in MST
        for(int v = 0; v < numVertices; v++)
        {
            // Graph[u][v] is non zero only for adjacent vertices of m
            //	mstSet[v] is false for vertices not yet included in MST
            // 	Update the key only if graph[u][v] is smaller than key[v]
            if (adjacencyMatrix[u][v] > 0 && mstSet[v] == false && adjacencyMatrix[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = adjacencyMatrix[u][v];
            }
        }
    }
    // A utility function to print the constructed MST stored in parent[]
//    printf("Edge   Weight\n");
    long sum = 0;
    long weight;
    for (int i = 0; i < numVertices; i++)
    {
//        printf("%d - %d    %d \n", parent[i], i, adjacencyMatrix[i][parent[i]]);
        vertexList[i].setParent(parent[i]);
        weight = adjacencyMatrix[i][parent[i]];
        vertexList[i].setDistance(weight);
//        qDebug() << "i - " << i << " Weight - " << weight << " key - " << key[i];
        sum += weight;
    }
//    qDebug() <<"Total distance is : " << sum;

    delete [] key;
    delete [] parent;
    delete [] mstSet;
    return sum;
}

/**
 * @brief Graph::minKey
 * Utility function to find the vertex with minimum key value, from the set of vertices
 * not yet included in the minimum spanning tree.
 * @param key
 * @param mstSet
 * @return long - the minimum key value
 */
long Graph::minKey(long key[], bool mstSet[])
{
    long min = INF;
    long min_index;
    for(int v = 0; v < numVertices; v++)
    {
        if(mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}
