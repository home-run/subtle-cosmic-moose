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

    /**
     * @brief getDistance
     * This distance is not the distance representing a single vertex but the distance
     * between this vertex and another a 'source' vertex during a single shortest path
     * search
     * @return the distance stored in the vertex
     */
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

    void setDistance(int d)
    {
        this->distance = d;
    }

    bool operator==(const Vertex& v)
    {
        return (v.getDistance() == this->getDistance()
                && v.getId() == this->getId()
                && v.getName() == this->getName());
    }

    Vertex* operator=(const Vertex& v)
    {
        this->distance = v.getDistance();
        this->id = v.getId();
        this->name = v.getName();
        return this;
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
    void shortestPath(Vertex source);

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

    QList<Vertex> vertexList;	// Stores the complete list of vertices in the graph
    int adjacencyMatrix[50][50];// Adjacency Matrix that stores the weidghts between
                                // 	all the vertices in the graph
    int numVertices;			// Stores the number of total vertices in the graph
    Heap<Edge, comp> edges;		// A min-heap to store all edges by priority
                                // 	TODO: May need to remove this.
    QVector<int> distance;		// Vector of costs of the shortest path from vertex v to the source s
    QVector<int> previous;		// Vector of ids of each previous vertex traveled


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


class VertexSet
{
public:
    VertexSet()
    {
        this->size = 0;
        this->bucketSize = 0;
    }

//    ~VertexSet()
//    {
//        delete [] buckets;
//    }

    /**
     * @brief insert
     * Method takes a vertex v and will insert it into the set.
     * @param v
     */
    void insert(Vertex v)
    {
        int hashKey;
        int index;
        // If inserting into an empty set
        qDebug() << "Inserting vertex " << v.getId();
        if(this->bucketSize == 0)
        {
            if(v.getId() != 0 )
            {
                this->buckets = new Vertex[v.getId()*50];
                this->bucketSize = v.getId()*50;
            }
            else
            {
                this->buckets = new Vertex[50];
                this->bucketSize = 50;
            }
            for(int i =0; i < this->bucketSize; i++)
            {
                this->buckets[i].setName("empty");
            }
        }
        hashKey = this->hash(v);
        index = 0;
        while(this->buckets[hashKey].getName() != "empty")
        {
            hashKey = (this->hash(v) + index * this->doubleHash(v)) % this->bucketSize;
            index++;
        }

        // Insert vertex v into the set.
        this->buckets[hashKey] = v;
        this->size++;
    }

    /**
     * @brief remove
     * This method will call on the search function that returns the hashed key value of
     * the vertex. If the key is not -1 it will clear the vertex at that index.
     * @param v
     */
    void remove(Vertex v)
    {
        int hashKey;
        hashKey = search(v);
        if(hashKey != -1)
        {
            this->buckets[hashKey].setDistance(INFINITY);
            this->buckets[hashKey].setName("empty");
            this->buckets[hashKey].setId(-1);
            this->size--;
        }
    }
    /**
     * @brief contains
     * Searches through the set to see if the element exists in the set.
     * @param v
     * @return true if found; otherwise return false if not found
     */
    bool contains(Vertex v)
    {
        bool found = false;
        int index = 0;
        int hashKey;
        while(!found && index < this->size)
        {
            hashKey = (this->hash(v) + index * this->doubleHash(v)) % this->bucketSize;
            index++;
            found = this->buckets[hashKey] == v;
        }
        return found;
    }

    /**
     * @brief isEmpty
     * @return true if set is empty; otherwise return false if not empty
     */
    bool isEmpty() const
    {
        return this->size == 0;
    }

    /**
     * @brief debugOutput
     * This is a debugging method used for outputting the names and the index at which
     * a vertex is located at. Serves no other purpose than to output to the console.
     */
    void debugOutput() const
    {
        for(int i = 0; i < this->bucketSize; i++)
        {
            qDebug() << "Index : " << i << " [ " << this->buckets[i].getName() << " ]";
        }
    }
    void clear();
private:
    Vertex *buckets;		// Stores the individual buckets of the set
    int bucketSize;			// The number of buckets in the set
    int size;				// Number of vertices stored in the set

    /**
     * @brief hash
     * Performs a hash involving a single prime number and modding the resulting value
     * by the number of buckets in the set.
     * @param v
     * @return hashed key value
     */
    int hash(Vertex v)
    {
        return (v.getId()*13) % this->bucketSize;
    }

    /**
     * @brief doubleHash
     * Performs hash involving two prime numbers and modulos by the number of buckets
     * @param v
     * @return hashed key value
     */
    int doubleHash(Vertex v)
    {
        return (v.getId() * 7 + 13 * v.getId() % this->bucketSize);
    }

    /**
     * @brief search
     *	Searches through the set
     * @param v
     * @return hashed key value representing the index placement of the vertex in the
     * bucket
     */
    int search(Vertex v)
    {
        bool found = false;
        int index = 0;
        int hashKey;
        while(!found && index < this->size)
        {
            hashKey = (this->hash(v) + index * this->doubleHash(v)) % this->bucketSize;
            index++;
            found = this->buckets[hashKey] == v;
        }
        if(found == false)
        {
            hashKey = -1;
        }
        return hashKey;
    }
};

#endif // GRAPH_H
