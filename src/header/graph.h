#ifndef GRAPH_H
#define GRAPH_H
#ifndef DEBUG
#define DEBUG 0
#endif

#include <QString>
#include <QList>
#include "database.h"
#include "Heap.h"
#include "vertex.h"



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
    void shortestPath(Vertex source);

    /**
     * @brief clearGraph
     */
    void clearGraph();

    int getNumberVertices() const;

    long getTotalDistance() const;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Debug Methods
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    /**
     * @brief debug_printAdjMatrix
     * Method for debugging the adjacency matrix, will only output to the console,
     * nothing else.
     */
    void debug_printAdjMatrix() const;

    /**
     * @brief debug_outputDistances
     * Method for outputting all the distances found after performing dijkstra's algorithm
     * for finding the shortest path to all vertices.
     */
    void debug_outputDistances() const;

private:

    QList<Vertex> vertexList;	// Stores the complete list of vertices in the graph
    int adjacencyMatrix[50][50];// Adjacency Matrix that stores the weidghts between
                                // 	all the vertices in the graph
    int numVertices;			// Stores the number of total vertices in the graph
    Heap<Edge, comp> edges;		// A min-heap to store all edges by priority
                                // 	TODO: May need to remove this.
    QVector<int> distance;		// Vector of costs of the shortest path from vertex v to the source s
    QVector<int> previous;		// Vector of ids of each previous vertex traveled
    int smallestWeight[50];
    VertexSet T;			// Contains a set of vertices that have not been visited


    /**
     * @brief initialize_single_source
     * Initialization function before performing the shortest path algorithm
     * Uses dijkstra's algorithm
     * @param s
     */
    void initialize_single_source(Vertex s);

    /**
     * @brief relax
     * Relaxation method between 2 vertices
     * @param u
     * @param v
     */
    void relax(Vertex &u, Vertex &v);
};


#endif // GRAPH_H
