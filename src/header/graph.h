#ifndef GRAPH_H
#define GRAPH_H
#ifndef DEBUG
#define DEBUG 0
#endif

#include <QString>
#include <QList>
#include "database.h"
#include "Heap.h"

struct Vertex
{
    QString stadiumName;
    int 	distance;
    int		id;
    int		parentId;
};

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

class Graph
{
public:

    Graph();

    /// Deconstructor, deallocates the memory set by the Adjacency Matrix
    ~Graph();

    /// @brief createGraph
    /// This method will call in the database and generate the graph that includes edges,
    /// 	and vertices. These represent the stadiums and the paths a baseball fan is
    /// 	able to
    void createGraph(Database *db);

    /// @brief edgeWeight
    /// Method provides a safe way to access the adjacency matrix.
    int edgeWeight(int v1, int v2);

    /// @brief getVertexList
    /// This will return a QList of vertices in the graph.
    QList<Vertex> getVertices() const;

    /// @brief shortestPath
    /// Returns the shortest path given the starting ID of a vertex.
    QList<Edge> shortestPath(int startingId);
private:

    QList<Vertex> vertexList;
    int adjacencyMatrix[50][50];
    int numVertices;
    void initialize_single_source();
    void relax(Vertex &u, Vertex &v);
    QList< Heap<Edge, comp> > sortedEdges;
};

#endif // GRAPH_H
