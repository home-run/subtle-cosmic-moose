#ifndef GRAPH_H
#define GRAPH_H
#ifndef DEBUG
#define DEBUG 0
#endif

#include <QString>
#include <QList>
#include "database.h"

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

class Graph
{
public:

    Graph();

    /// Deconstructor, deallocates the memory set by the Adjacency Matrix
    ~Graph();

    void createGraph(Database *db);

    /// @brief Edge Weight
    int edgeWeight(int v1, int v2);

    /// @brief Get Vertex List
    QList<Vertex> getVertices() const;

    QList<Edge> shortestPath(int startingId);
private:
    QList<Vertex> vertexList;
    int** adjacencyMatrix;
    int numVertices;

    void initialize_single_source();
    void relax(Vertex &u, Vertex &v);
    QList<Edge> Graph::sortedEdges();
};

#endif // GRAPH_H
