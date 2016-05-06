#include "graph.h"

Graph::Graph()
{
    // Initialze the number of vertices in the graph to be 0
    this->numVertices = 0;

    // Initializes every weight in the adjacency matrix to be -1
    for(int i = 0; i < this->numVertices; i++)
    {
        for(int j = 0; j < this->numVertices; j++)
        {
            this->adjacencyMatrix[i][j] = -1;
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
                                //	Integer values to store temporary To, From, Weight and Current IDs
    int toId, fromId, weight, id;
    QString stadiumName;		// Stores the name of the stadium for inserting into the
                                // 	graph

    numVertices = db->getNumberOfStadiums();

//    vertexList.reserve(numVertices);
    // TODO: Clear graph in case that a new graph is needed when more stadiums have been added to the graph.

    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            adjacencyMatrix[i][j] = -1;
        }
    }

    // Calls on the database method that retrieves the SQL Query for access the stadium
    //	names and ids within the SQLite datbase
    queryResult = db->getStadiumsNameId();
    // While there still is a query record left within the query...
    while(queryResult.next())
    {
        // Get the ID field and convert it to int then store it in id
        id = queryResult.record().field("id").value().toInt();
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

#if DEBUG
        {
            qDebug() << "To ID : " << toId << " From ID : " << fromId << " weight " << weight;
        }
#endif
        for(int i = 0; i < numVertices; i++)
        {
            if(vertexList.at(i).getId()== fromId)
            {
                edge.idFrom = fromId;
                edge.idTo = toId;
                edge.weight = weight;
            }
        }

        adjacencyMatrix[fromId][toId] = weight;
    }
#if DEBUG
{
        for(int i = 0; i < numVertices; i++){
            for(int j = 0; j < numVertices; j++){
                qDebug() << "The distance from " << i + 1 << " to " << j + 1 << " is " << adjacencyMatrix[i][j];
            }
        }
        qDebug() << "Printing Vertex List";
        for(int i = 0; i < vertexList.size(); i++){
            qDebug() << "ID [ " << vertexList.at(i).getId() << " ] - Name [ " << vertexList.at(i).getName() << " ]";
        }
    }
#endif

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

void Graph::initialize_single_source(Vertex s)
{
    distance.clear();
    previous.clear();
    distance.reserve(numVertices);
    previous.reserve(numVertices);

    for(int vertex = 0; vertex < numVertices;vertex++)
    {
        distance.push_back(INFINITY);
        previous.push_back(-1);
    }
    //    vertexList[s.id].distance = 0;
//    distance[s.getId()] = 0;
    distance[s.getId()] = 0;
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
    //    if(v.distance > u.distance + adjacencyMatrix[u][v])
    if(v.getDistance() > u.getDistance() + edgeWeight(u.getId(),v.getId()))
    {
        distance[v.getId()] = u.getDistance() + edgeWeight(u.getId(),v.getId());
        previous[v.getId()] = u.getId();
    }
}

/**
 * @brief Graph::clearGraph
 * This method will go through and clear the adjacency matrix and the vertex list.
 */
void Graph::clearGraph()
{
    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            this->adjacencyMatrix[i][j] = -1;
        }
    }
    vertexList.clear();

}

/**
 * @brief Graph::debug_printAdjMatrix
 * This method is used for debugging purposes and printing the adjacency matrix when needed.
 */
void Graph::debug_printAdjMatrix() const
{
    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            qDebug() << "i : " << i << " - j : " << j << " - weight : " << adjacencyMatrix[i][j];
        }
    }
}

void Graph::shortestPath(Vertex source)
{
    VertexSet T;
    VertexSet V;
    Heap<Edge, comp> vertexPQ;
    Edge edge;

#if DEBUG
    qDebug() << "Initializing Single Source";
#endif
    // Initialize all edges, and vertices to infinity
    initialize_single_source(source);

    // Create a set T of all vertices in the graph
    for(int numV = 0; numV < numVertices; numV++)
    {
        T.insert(vertexList.at(numV));
    }
    T.debugOutput();
    // Let a priority queue contain all the vertices (edges in this case) of G Using
    //	the Distances (weights) as keys
    for(int i = 0; i < this->numVertices;i++)
    {
        for(int j = 0; j < this->numVertices;j++)
        {
            edge.weight = this->adjacencyMatrix[i][j];
            // If the weight is not -1 then insert it into the priority queue.
            if(edge.weight != -1 && edge.weight != INFINITY)
            {
                edge.idFrom = i;
                edge.idTo = j;
//                qDebug() << "ID From [ " << edge.idFrom << " ] id to [ " << edge.idTo << " ] weight [ " << edge.weight <<" ]";
                vertexPQ.insert(edge);
            }
        }
    }
    while(!vertexPQ.isEmpty())
    {
        edge = vertexPQ.root();
        vertexPQ.remove(1);
        for(int i = 0; i < numVertices; i++)
        {
        }
    }
}
