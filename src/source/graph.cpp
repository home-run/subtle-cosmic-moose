#include "graph.h"

Graph::Graph()
{
    this->numVertices = 0;

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
    QSqlQuery queryResult;
    Vertex vertex;
    Edge edge;
    int toId, fromId, weight, id;
    QString stadiumName;

    numVertices = db->getNumberOfStadiums();

    vertexList.reserve(numVertices);
    // TODO: Clear graph in case that a new graph is needed when more stadiums have been added to the graph.

    for(int i = 0; i < numVertices; i++)
    {
        for(int j = 0; j < numVertices; j++)
        {
            adjacencyMatrix[i][j] = -1;
        }
    }


    queryResult = db->getStadiumsNameId();
    while(queryResult.next())
    {
        id = queryResult.record().field("id").value().toInt();
        stadiumName = queryResult.record().field("name").value().toString();
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
        for(int i = 0; i < numVertices; i++)
        {
            for(int j = 0; j < numVertices; j++)
            {
                qDebug() << "The distance from " << i + 1 << " to " << j + 1 << " is " << adjacencyMatrix[i][j];
            }
        }
        qDebug() << "Printing Vertex List";
        for(int i = 0; i < vertexList.size(); i++)
        {
            qDebug() << "ID [ " << vertexList.at(i).id << " ] - Name [ " << vertexList.at(i).stadiumName << " ]";
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
    for(int vertex = 0; vertex < vertexList.size(); vertex++)
    {
        //        vertexList[vertex].distance = INFINITY;
        //        vertexList[vertex].parentId = -1;
        distance[vertex] = INFINITY;
        previous[vertex] = -1;
    }
    //    vertexList[s.id].distance = 0;
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

QList<Edge> Graph::shortestPath(Vertex source)
{
    QList<Vertex> shortestVerticesFound;
    Heap<Edge, comp> vertexPQ;
    Vertex u;

#if DEBUG
    qDebug() << "Initializing Single Source";
#endif
    initialize_single_source(source);


}
