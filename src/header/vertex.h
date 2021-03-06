#ifndef VERTEX_H
#define VERTEX_H
#ifndef INF
#define INF INT_MAX - 10000
#endif

#include <QList>
#include "Heap.h"
struct Edge
{
    int idFrom;
    int idTo;
    int weight;
};

/**
 * @brief The comp struct
 * Comparator struct used for comparing the weights of two edges
 */
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
        this->id = INT_MAX;
        this->name = "";
        this->parent = -1;
        this->distance = 0;
        this->queuePosition = -1;
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
        this->parent = -1;
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
    /**
     * @brief setId
     * Set the ID of the vertex
     * @param id
     */
    void setId(int id)
    {
        this->id = id;
    }

    /**
     * @brief setName
     * Set the name of the vertex
     * @param name
     */
    void setName(QString name)
    {
        this->name = name;
    }

    /**
     * @brief setParent
     * Set the parent of the current vertex to p
     * @param p
     */
    void setParent(int p)
    {
        this->parent = p;
    }

    /**
     * @brief setDistance
     * Set the distance of the vertex traveled between 2 vertices
     * @param d
     */
    void setDistance(int d)
    {
        this->distance = d;
    }

    /**
     * @brief operator ==
     * Overloaded comparison operator. Compares the distance, ID and the name over the 2
     * 	vertices. Returns true if they are equal, false otherwise.
     * @param v
     * @return true if they are equal, false otherwise.
     */
    bool operator==(const Vertex& v) const
    {
        return (v.getId() == this->getId()
                && v.getName() == this->getName());
    }

    /**
     * @brief operator !=
     * Overloaded comparison operator to see if the two vertices are not the same vertex.
     * Compares the ID and the name of the vertex as its determining factors of equality.
     * @param v
     * @return true if they don't match; otherwise return false if they do.
     */
    bool operator!=(const Vertex& v) const
    {
        return (v.getId() != this->getId() && v.getName() != this->getName());
    }


    /**
     * @brief operator <
     * Overloaded less than operator to compare this vertex distance
     * 	and the given vertex v
     * @param v
     * @return
     */
    bool operator<(const Vertex &v) const
    {
        return this->distance < v.getDistance();
    }

    /**
     * @brief operator >
     * Overloaded greater than operator to compare this vertex distance
     * 	and the given vertex v
     * @param v
     * @return
     */
    bool operator>(const Vertex &v) const
    {
        return this->distance > v.getDistance();
    }
    /**
     * @brief operator >=
     * Overloaded greater than or equal operator to compare this vertex distance
     * 	and the given vertex v
     * @param v
     * @return
     */
    bool operator>=(const Vertex &v) const
    {
        return this->distance >= v.getDistance();
    }
    /**
     * @brief operator <=
     * Overloaded less than or equal operator to compare this vertex distance
     * 	and the given vertex v
     * @param v
     * @return
     */
    bool operator<=(const Vertex &v) const
    {
        return this->distance <= v.getDistance();
    }
    /**
     * @brief operator =
     * Overloaded assignment operator to assign the values of the given vertex v to this
     *  vertex. Assigns the distance, id and name this vertex then returns 'this' to the
     * 	calling object.
     * @param v
     * @return
     */
    Vertex* operator=(const Vertex& v)
    {
        this->distance = v.getDistance();
        this->id = v.getId();
        this->name = v.getName();
        this->parent = v.getParent();
        return this;
    }

    /**
     * @brief addEdge
     * Takes the given edge and insert it into an internal adjacency list.
     * @param edge
     */
    void addEdge(Edge edge)
    {
        this->edges.insert(edge);
        this->numEdges++;
    }

    /**
     * @brief getNearestEdge
     * Method will grab the edge with the least amount of weight (distance) the current
     * vertex. It removes the edge for the min-heap stored in the vertex and appends it
     * to a list of edges that has been removed.
     * @return
     */
    Edge getNearestEdge()
    {
        Edge root;
        try
        {
            root = this->edges.removeMin();
            numEdges--;
            backupEdges.push_back(root);
        } catch(...)
        {
            qDebug() << "NO MORE EDGES!";
        }

        return root;
    }

    /**
     * @brief getNumEdges
     * This method will return the number of adjacent edges that exsists between this
     * vertex and other vertices.
     * @return int val of number of adjacent edges
     */
    int getNumEdges() const
    {
        return this->edges.size();
    }

    /**
     * @brief hasEdges
     * Returns a boolean value if the current vertex has adjacent edges left in it's
     * priority queue adjacency list.
     * @return
     */
    bool hasEdges() const
    {
        return !edges.isEmpty();
    }

    /**
     * @brief getParent
     * Method returns the ID integer value of the it's parent vertex. This is only
     * established after a path has been taken using Dijkstra's algorithm or calculating
     * the minimum spanning tree.
     * @return int ID of the parent vertex
     */
    int getParent() const
    {
        return this->parent;
    }

    /**
     * @brief reinitializeEdges
     * This method iterates the vertex's current edges and places them back into it's
     * own priority queue (adjacency list).
     */
    void reinitializeEdges()
    {
        Edge edge;
        while(!backupEdges.isEmpty())
        {
            edge = backupEdges.front();
            edges.insert(edge);
            backupEdges.pop_front();
        }
    }

    /**
     * @brief getNextEdge
     * this will return the next edge available in verticee adjacency list.
     * @return edge object of the adj list
     */
    Edge getNextEdge()
    {
        return edges.root();
    }

    /**
     * @brief setQueuePosition
     * Sets the vertex index that is relative to its position in the stored object that
     * it is located in, such as a map, queue or a vector.
     * @param pos
     */
    void setQueuePosition(int pos)
    {
        this->queuePosition = pos;
    }

    /**
     * @brief getQueuePosition
     * This returns the vertices index of the position / location that it is located in
     * a container object.
     * @return int
     */
    int getQueuePosition() const
    {
        return this->queuePosition;
    }

private:
    int id;
    QString name;
    int parent;
    int distance;
    Heap<Edge, comp> edges;
    int numEdges;
    QList<Edge> backupEdges;
    int queuePosition;
};

/**
 * @brief The vertexComp struct
 * Comparator to be used when inserting vertices into a heap
 */
struct vertexComp
{
    bool operator()(const Vertex& v1, const Vertex& v2)
    {
        return v1.getDistance() < v2.getDistance();
    }
};


class VertexSet
{
public:
    VertexSet()
    {
        this->size = 0;
        this->bucketSize = 0;
    }

    ~VertexSet()
    {
        // Need to figure out why this crashes the program....
        // delete [] buckets;
    }

    /**
     * @brief insert
     * Method takes a vertex v and will insert it into the set.
     * @param v
     */
    void insert(Vertex &v)
    {
        int hashKey;
        int index;
        // If inserting into an empty set
        if(this->bucketSize == 0)
        {
            if(v.getId() != 0 )
            {
                // Changed the sizes to be a prime number
                //	may need to be made bigger...
//                this->buckets = new Vertex[v.getId()*100];
//                this->bucketSize = v.getId()*100;
                this->buckets = new Vertex[v.getId()*31];
                this->bucketSize = v.getId()*31;
            }
            else
            {
                // Changed the sizes to be a prime number
                //	may need to be made bigger...
//                this->buckets = new Vertex[100];
//                this->bucketSize = 100;
                this->buckets = new Vertex[31];
                this->bucketSize = 31;
            }
            for(int i =0; i < this->bucketSize; i++)
            {
                this->buckets[i].setName("empty");
            }
        }
        hashKey = this->hash(v);
        index = 0;
        while(this->buckets[hashKey].getName() != "empty" && this->buckets[hashKey] != v)
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
     * @brief getSize
     * This method returns the size of the set, number of vertices in the set.
     * @return int value of number of vertices in set
     */
    int getSize() const
    {
        return this->size;
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

    /**
     * @brief operator =
     * Overloaded assignment operator for taking a list of vertices and converting into
     * a set of vertices.
     * @param vertexList
     * @return this as a new set of vertices
     */
    VertexSet* operator=(const QList<Vertex> &vertexList)
    {
        Vertex vertex;
        // Create a set T of all vertices in the graph
        for(int numV = 0; numV < vertexList.size(); numV++)
        {
            vertex = vertexList[numV];
            this->insert(vertex);
        }
        return this;
    }


    /**
     * @brief clear
     * This method will clear the current set of vertices and reinitialze them to being
     * 'empty'.
     */
    void clear()
    {
        Vertex vertex;	// Temp vertex to override any vertex in the set.
        // Set the distance, name, id and parent back to original values.
        vertex.setDistance(INF);
        vertex.setName("empty");
        vertex.setId(-1);
        vertex.setParent(-1);
        for(int index = 0; index < this->size;index++)
        {
            buckets[index] = vertex;
        }
        size = 0;
    }

    /**
     * @brief outputSet
     * This is primarly a debugging method for testing the vertex set. It will iterate
     * through the set and output the entire set.
     */
    void outputSet() const
    {
        int count = 0;
        for(int vertexIndex = 0; vertexIndex < bucketSize; vertexIndex++)
        {
            if(buckets[vertexIndex].getName() != "empty")
            {
                ++count;
                qDebug() << "Vertex count : " << count << " Name [ " << buckets[vertexIndex].getName() << " ] Distance [ " <<
                            buckets[vertexIndex].getDistance() << " ]";
            }
        }
    }

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
        return ((v.getId() + 1)*13) % this->bucketSize;
    }

    /**
     * @brief doubleHash
     * Performs hash involving two prime numbers and modulos by the number of buckets
     * @param v
     * @return hashed key value
     */
    int doubleHash(Vertex v)
    {
        return ((v.getId()+1) * 7 + 13 * (v.getId()+1) % this->bucketSize);
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

#endif // VERTEX_H
