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

    /**
     * @brief Graph::getVertexPath
     * Function will take a given vertex and traverse up the path of the given parent ids
     * to construct the path that was taken to arrive at the target vertex. This method
     * will return a QList of vertices, where index 0 is the starting vertice and the last
     * vertex in the list is the given target vertex.
     * @param target Vertex
     * @return QList of Vertices
     */
    QList<Vertex> getVertexPath(Vertex target);

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
    QList<Vertex> findShortestPathTo(Database *db, int source, int target);

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
    QList<Vertex> findShortestPathTo(Database *db, int source, QList<int> stops);

    /**
     * @brief minimumSpanningTree
     * This method will generate the minimum spanning tree given a starting vertex. It is
     * recommended not to start at index 0, 1, 22, or 29 to guarantee the most minimum
     * spanning tree possible in the given graph. Each vertex will store the parent of the
     * vertex that it had to traverse to get to.
     * @param source
     * @return long minimum distance between all vertices
     */
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

    long minKey(long key[], bool mstSet[]);

private:

    QList<Vertex> vertexList;       // Stores the complete list of vertices in the graph
    int adjacencyMatrix[50][50];    // Adjacency Matrix that stores the weidghts between
                                    // 	all the vertices in the graph
    int numVertices;                // Stores the number of total vertices in the graph
    Heap<Edge, comp> edges;         // A min-heap to store all edges by priority
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
