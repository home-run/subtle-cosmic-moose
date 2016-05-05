#ifndef GRAPH_H
#define GRAPH_H
#ifndef DEBUG
#define DEBUG 0
#endif

#include <QString>
#include <QList>
#include "database.h"
#include "Heap.h"

struct Edge
{
    int idFrom;
    int idTo;
    int weight;
};

struct comp
{
    bool operator()(const Edge& e1, const Edge& e2)const
    {
        return e1.weight < e2.weight;
    }
};

class Vertex
{
public:
    /**
     * @brief Vertex
     * Default Vertex constructor
     */
    Vertex(){
        this->id = INT16_MAX;
        this->name = "";
        this->parent = NULL;
        this->distance = 0;
    }

    /**
     * @brief Vertex
     * Non-default Vertex Constructor. Takes in the ID and name of the vertex as it is
     * being instatiated.
     * @param id
     * @param name
     */
    Vertex(int id, QString name, int distance)
    {
        this->id = id;
        this->name = name;
        this->parent = NULL;
        this->distance = distance;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Accessors
    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /**
     * @brief getId
     * @return The id of the vertex
     */
    int getId() const
    {
        return this->id;
    }

    /**
     * @brief getName
     * @return The name of the vertex
     */
    QString getName() const
    {
        return this->name;
    }

    int getDistance() const
    {
        return this->distance;
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Mutators
    // - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void setId(int id)
    {
        this->id = id;
    }

    void setName(QString name)
    {
        this->name = name;
    }

    void setParent(Vertex*p)
    {
        this->parent = p;
    }

private:
    int id;
    QString name;
    Vertex *parent;
    int distance;
    Heap<Edge, comp> edges;
};

class Graph
{
public:

    Graph();

    /// Deconstructor, deallocates the memory set by the Adjacency Matrix
    ~Graph();


    /**
     * @brief edgeWeight
     * Method provides a safe way to access the adjacency matrix.
     */
    int edgeWeight(int v1, int v2);

    /**
     * @brief getVertexList
     *  This will return a QList of vertices in the graph.
     */
    QList<Vertex> getVertices() const;

    /**
     * @brief createGraph
     *  This method will call in the database and generate the graph that includes edges,
     *  	and vertices. These represent the stadiums and the paths a baseball fan is
     *  	able to
     */
    void createGraph(Database *db);
    /**
     * @brief shortestPath
     * Returns the shortest path given the starting ID of a vertex.
     */
    QList<Edge> shortestPath(Vertex source);

    /**
     * @brief clearGraph
     */
    void clearGraph();

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Debug Methods
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /**
     * @brief debug_printAdjMatrix
     * Method for debugging the adjacency matrix, will only output to the console,
     * nothing else.
     */
    void debug_printAdjMatrix() const;
private:

    QList<Vertex> vertexList;
    int adjacencyMatrix[50][50];
    int numVertices;

    int distance[1000];
    int previous[1000];

    void initialize_single_source(Vertex s);
    void relax(Vertex &u, Vertex &v);
};




#endif // GRAPH_H
