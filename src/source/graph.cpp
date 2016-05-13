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

void Graph::findShortestPathTo(Vertex source, Vertex target)
{
    Heap<Vertex, vertexComp> vertexPQ;// Min-Heap (priority queue) containing all the
                            //	vertices in the graph, ordered by the weight. Smallest
                            //	weight is root
    VertexSet T;			// Contains the set of vertices to which the shortest path
                            //	has been found.
    QList<Vertex> S;
//    bool *visited;
    Vertex u;
    Vertex v;
    Edge adjEdge;
    int distanceSum;

    source = vertexList.at(source.getId());
    target = vertexList.at(target.getId());
    // Initialize all edges, and vertices to infinity
    initialize_single_source(source);
//    visited = new bool[numVertices];

//    for(int v = 0; v < numVertices; v++)
//    {
//        visited[v] = false;
//    }

    T.clear();
    // Initialize the priority queue to start with the given source vertex as the first
    //	vertex to explore.
    vertexPQ.insert(vertexList[source.getId()]);
//    visited[source.getId()] = true;

    while(!vertexPQ.isEmpty())
    {
        u = vertexPQ.removeMin();
        if(target.getId() == u.getId())
        {
            break;
        }
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
//                    T.insert(vertexList[u.getId()]);
                    T.insert(v);
                }
            }
        }
        // Once all the adjacent vertices have been explored, add the the vertex U to the
        //	set T of found shortest paths.
    }
    // Once the algorithm is complete, clear the VertexSet T of all vertices.
//    T.clear();

    while(u.getParent() != -1)
    {
        S.push_front(vertexList[u.getParent()]);
        u = vertexList.at(u.getParent());
    }
    S.push_front(u);
//    delete [] visited;
    for(int i = 0; i < S.size(); i++)
    {
        qDebug() << "At i " << i << " is " << S.at(i).getName();
    }

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

void Graph::minimumSpanningTree(int source)
{
    Heap<Vertex, vertexComp> Q;
    long *key;
    long *parent;
    Vertex root;
    VertexSet T;
    Vertex vertex;
    Edge edge;
    long weight;

    key = new long[numVertices];
    parent = new long[numVertices];

    // For each vertex u in the Graph G with Vertices V
    for(int u = 0; u < numVertices; u++)
    {
        key[u] = INF;
        parent[u] = -1;
        vertexList[u].setDistance(INF);
        T.insert(vertexList[u]);

    }
    key[source] = 0;
    vertexList[source].setDistance(0);

    root = vertexList[source];
    Q.insert(root);
    while(!Q.isEmpty())
    {
        vertex = Q.removeMin();
        while(vertexList[vertex.getId()].hasEdges())
        {
            edge = vertexList[vertex.getId()].getNearestEdge();
            weight = adjacencyMatrix[vertex.getId()][edge.idTo];
            if(T.contains(vertexList[edge.idTo]) && weight < vertexList[edge.idTo].getDistance())
            {
                vertexList[edge.idTo].setParent(vertex.getId());
                vertexList[edge.idTo].setDistance(weight);
                T.remove(vertexList[edge.idTo]);
            }
            Q.insert(vertexList[edge.idTo]);
        }
    }
}
