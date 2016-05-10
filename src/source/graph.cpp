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

Graph::~Graph()
{

    // TODO: Figure out how to deallocate the memory for the distance and previous
    //	list. Currently throws a 'malloc' error.
    // test(65779,0x7fff7eb36000) malloc: *** error for object 0x7: pointer being freed was not allocated
    // *** set a breakpoint in malloc_error_break to debug
    // The program has unexpectedly finished.

    //    if(distance != NULL)
    //    {
    //        try
    //        {
    //            delete distance;
    //        } catch(...)
    //        {
    //            qDebug() << "No memory allocated to delete";
    //        }
    //    }
    //    if(previous != NULL)
    //    {
    //        try
    //        {
    //            delete previous;
    //        } catch(...)
    //        {
    //            qDebug() << "No memory allocated to delete";
    //        }
    //    }
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

    // TODO: Clear graph in case that a new graph is needed when more stadiums have
    //	been added to the graph.

    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            adjacencyMatrix[i][j] = 0;
//            adjacencyMatrix[i][j] = INT_MAX - 100000;
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
        vertexList[vertex].setParent(NULL);
    }
    vertexList[s.getId()].setDistance(0);
}

/**
 * @brief Graph::relax
 * The process of relaxing an edge (u,v) consists of testing whether we can improve the
 * 	shortest path to v found so far by going through u and, if so, updating v.d and
 *  v.parentId.
 * @param u - Vertex
 * @param v - Vertex
 */
void Graph::relax(Vertex &u, Vertex &v)
{
    qDebug() << " ";
    qDebug() <<" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    qDebug() <<" Relax - Don't do it - When you want to come to it";
    qDebug() <<" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    int distanceSum;
    distanceSum = u.getDistance() + adjacencyMatrix[u.getId()][v.getId()];
    qDebug() << "Comparing V Distance to U distance + Adj[u][v]";
    qDebug() << v.getName() << " > " << u.getName() << " + Adj-Weight";
    qDebug() << v.getDistance() << " > " << distanceSum;
    if(v.getDistance() > distanceSum )
    {
    qDebug() << " ";
        v.setDistance(distanceSum);
        v.setParent(&u);
        vertexList[v.getId()] = v;
        qDebug() << "- - - Changed V [ " << v.getName() << " ] Distance to " << v.getDistance() << " - - -";
    }
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
            this->adjacencyMatrix[i][j] = 9999;
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
 * Given a source vertex
 * @param source
 */
void Graph::shortestPath(Vertex source)
{
    Heap<Vertex, vertexComp> vertexPQ;// Min-Heap (priority queue) containing all the vertices in
                            // the graph, ordered by the weight. Smallest weight is root
    VertexSet V;			// Contains the set of vertices to which the shortest path
                            //	has been found.
    Vertex u;
    Edge adjEdge;
    source = vertexList.at(source.getId());
    // Initialize all edges, and vertices to infinity
    initialize_single_source(source);

    T.clear();
    // Initially the source vertex s is in T of those whose cost has been found.

    // Let a priority queue contain all the vertices (edges in this case) of G Using
    //	the Distances (weights) as keys
    for(int i = 0; i < this->numVertices;i++)
    {
        vertexPQ.insert(vertexList[i]);
    }

    qDebug() << "------------------ Output Vertices w/ Distances before search ------------------";
    for(int i = 0; i < vertexList.size(); i++)
    {
        qDebug () << "Name [ " << vertexList.at(i).getName() << " ] - Distance : " << vertexList.at(i).getDistance();
    }

//    qDebug() << "------------------ Adjacency Matrix before search ------------------";
//    this->debug_printAdjMatrix();

    while(!vertexPQ.isEmpty())
    {
        u = vertexPQ.removeMin();

        qDebug() << "===================== NEW U =====================";
        qDebug() << "U : " << u.getName();

        while(vertexList.at(u.getId()).hasEdges())
        {
            adjEdge = vertexList[u.getId()].getNearestEdge();
            qDebug() << "Edge between [ " << vertexList.at(adjEdge.idFrom).getName() << " ] to [ " <<vertexList.at(adjEdge.idTo).getName() << " ]";
            qDebug() << "Edge with Weight : " << adjacencyMatrix[u.getId()][adjEdge.idTo];
            if(adjacencyMatrix[u.getId()][adjEdge.idTo] != 0 )
            {
                relax(u,vertexList[adjEdge.idTo]);
                qDebug() << "V distance is : " << vertexList[adjEdge.idTo].getDistance();
            }
        }
        T.insert(vertexList[u.getId()]);
    }
    T.outputSet();
}

void Graph::maliks_shortestPath(Vertex source)
{
//    int *smallestWeight;
//    smallestWeight = new int[numVertices];

    int v;
    int minWeight = INT_MAX;

    for(int j =0; j< numVertices;j++)
    {
        smallestWeight[j] = adjacencyMatrix[source.getId()][j];
    }
    bool *weightFound;
    weightFound = new bool[numVertices];

    weightFound[source.getId()] = true;
    smallestWeight[source.getId()] = 0;

    for(int i =0; i < numVertices; i++)
    {
        minWeight = INT_MAX;
        v = 0;

        for(int j = 0; j <numVertices; j++)
        {
            if(!weightFound[j])
            {
                if(smallestWeight[j] < minWeight)
                {
                    v = j;
                    minWeight = smallestWeight[j];
                    qDebug() << "Min weight : " << minWeight;
                }
            }
        }
        weightFound[v] = true;

        for(int j = 0; j <numVertices; j++)
        {
            if(!weightFound[j])
            {
                if(minWeight + adjacencyMatrix[v][j] < smallestWeight[j])
                {
                    smallestWeight[j] = minWeight + adjacencyMatrix[v][j];
                }
            }
        }
    }
    for(int i = 0; i < numVertices;i++)
    {
        qDebug() << "From "<< vertexList.at(source.getId()).getName() <<" to [ " << vertexList.at(i).getName() << " ] is " << smallestWeight[i] ;
    }
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
