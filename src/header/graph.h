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
#include "vertexqueue.h"

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
     * This method clears the current graph
     * TODO: Needs to be updated for the current implementation of the graph search.
     */
    void clearGraph();

    /**
     * @brief getNumberVertices
     * This method returns the number of vertices that are inserted in the graph
     * @return int number of vertices
     */
    int getNumberVertices() const;

    /**
     * @brief getTotalDistance
     * Calculates the total distance going to all vertices starting at dodger stadium
     * each time.
     * @return
     */
    long getTotalDistance() const;

    QList<Vertex> getVertexPath(Vertex target);

    QList<Vertex> findShortestPathTo(Database *db, int source, int target);

    long minimumSpanningTree(int source);

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
     * Method for outputting all the distances found after performing dijkstra's
     * 	algorithm for finding the shortest path to all vertices.
     */
    void debug_outputDistances() const;

    void debug_printPath(Vertex vertex) const;

    long malik_minimumSpanningTree(int source);

    long minKey(long key[], bool mstSet[]);

private:

    QList<Vertex> vertexList;	// Stores the complete list of vertices in the graph
    int adjacencyMatrix[50][50];// Adjacency Matrix that stores the weidghts between
                                // 	all the vertices in the graph
    int numVertices;			// Stores the number of total vertices in the graph
    Heap<Edge, comp> edges;		// A min-heap to store all edges by priority
                                // 	TODO: May need to remove this.


    /**
     * @brief initialize_single_source
     * Initialization function before performing the shortest path algorithm
     * Uses dijkstra's algorithm
     * @param s
     */
    void initialize_single_source(Vertex s);

};


#endif // GRAPH_H
