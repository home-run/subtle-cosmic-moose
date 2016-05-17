# Big-O Analysis
##Team: ~/run

### Group Members
* Jesse Mazzella
* Sepher Raissaian
* Daniel Phan
* Dan Karlsson

### Algorithms
* Dijkstra’s Algorithm
* Minimum Spanning Tree - Prims

### Data Structures
* Graph [Adjacency List – Priority Queue]
* Graph [Adjacency Matrix]
* Heap [Priority Queue]
* VertexSet [Set]
* QStack
* QVector
* QList
* QMap

## Algorithms

### Dijkstra's Algorithm

-----

Dijkstra's Algorithm is used for finding the shortest paths between vertices stored within a graph. The implementation of Dijsktra's algorithm is a variant of the original and finds the shortest path between a source node and all other nodes within a graph. It uses a minimum-heap priority queue to improve the efficiency of the algorithm when determining the path.


__Algorithm__: void Graph::shortestPath(Vertex source)

```cpp

source = vertexList.at(source.getId());
// Initialize all edges, and vertices to infinity
initialize_single_source(source);


```

Function: void Graph::initialize_single_source(Vertex source)

This runs in __O(n)__ because `initialize_single_source(source)` will iterate through each vertex in the graph and initialize each vertex with a distance of _INFINITY_ and the parent to _-1_. Then it sets the source vertex to have a distance of 0 to represent it as being the starting vertex.


```cpp


for(int vertex = 0; vertex < numVertices;vertex++)  // O(n) performance
    vertexList[vertex].setDistance(INF);
    vertexList[vertex].setParent(-1);

vertexList[s.getId()].setDistance(0);
```
This process is then

> __Initialize each vertex in the graph => O(n)__

Then it will initial a vertex set class to be empty and insert the starting vertex into the priority queue of vertices to grab from. This operation is done in __O(1)__ time since the priority queue is empty at this point.

```cpp
T.clear();
vertexPQ.insert(vertexList[source.getId()]);    // O(1) performance
```

> __Insert into an empty priority queue => O(1)__

Dijkstra's algorithm will run for as many vertices that there are in the graph what there are __n__ number of vertices. This gives __O(n)__ performance because the algorithm has the check __n__ number of vertices.



The removal of a vertex from the priority queue is __O(logn)__ because the removal itself takes __O(1)__ but the _bubble down_ / _min-heapify_ process after the remove of a node from priority queue will take __O(logn)__. 

```cpp
while(!vertexPQ.isEmpty()){

    u = vertexPQ.removeMin();   // O(logn)

```

>__Removal of a node => O(1 + logn) ==> O(logn)__ but is only done for each vertex in the graph => O(n)


Next the algorithm will check each vertex to see the adjacent edges have a distance sum of the current vertex plus the weight of the edge is smaller than the distance currently found for the next vertex. Each edge to that vertex is stored within its own priority queue which gives it __O(1)__ access for retrieving the smallest weighted edge to that vertex, but calling `getNearestEdge()` also removes the edge from the priority queue there for producing a __O(logn)__ performance and allowing the next smallest edge being readily accessible.

```cpp
while(vertexList.at(u.getId()).hasEdges()){

    adjEdge = vertexList[u.getId()].getNearestEdge();                               // <= O(logn)
    v = vertexList.at(adjEdge.idTo);                                                // <= O(1)

    if(adjacencyMatrix[u.getId()][adjEdge.idTo] != 0){

        distanceSum = u.getDistance() + adjacencyMatrix[u.getId()][v.getId()];      // <= O(1)

        if(v.getDistance() > distanceSum )                                          // <= O(1)
            v.setDistance(distanceSum);                                             // <= O(1)
            v.setParent(u.getId());                                                 // <= O(1)
            vertexList[v.getId()] = v;                                              // <= O(1)

        // If the set T of found vertices does not contain the vertex v add the
        //  vertex v to the priority queue to see the shorter path.
        if(!T.contains(v))          // <= Expected O(1) worst case O(n)
            vertexPQ.insert(v);     // <= O(logn)
            T.insert(v);            // <= Expected O(1) worst case O(n)

```
The removal and checking of edges is a O(e) [Edge per node] process since it has to check each adjacent edge for each vertex and each edge has to be checked.
Therefore,

> Removal and checking of each edge ==> O(e)

Since it utilizes a priorty queue to sort the vertices by its current distance it allows the checking off vertices from __O(n)__ to __O(logn)__ for each adjacent vertex.

> Checking adjacent vertices for each vertex in the priority queue => O(nlogn) but since it only needs to check the vertices 


> __Initialize each vertices => O(n) + Insert into priority queue => O(1) + Removal of a node => O(n) + Removal and checking of each edge ==> O(e) + Checking adjacent vertices for each vertex => O(nlogn)__
>
> __O(n) + O(1) + O(n) + O(e) + O(nlogn)__

#### The resulting performance is :

> __O(2n + 1 +  e + nlogn) = O(e + nlogn)__


### MST prim’s

-----

The time complexity of Prim's algorithm depends on the data structures used for the graph and for ordering the edges by weight.Using an adjacency matrix or an adjacency list graph representation and linearly searching an array of weights to find the minimum weight edge, to add requires O(|V|2) running time. However, this running time can be greatly improved further by using heaps to implement finding minimum weight edges in the algorithm's inner loop. 
A first improved version uses a heap to store all edges of the input graph, ordered by their weight. This leads to an O(|E| log |E|) worst-case running time. But storing vertices instead of edges can improve it still further. The heap should order the vertices by the smallest edge-weight that connects them to any vertex in the partially constructed minimum spanning tree (MST) (or infinity if no such edge exists). Every time a vertex v is chosen and added to the MST, a decrease-key operation is performed on all vertices w outside the partial MST such that v is connected to w, setting the key to the minimum of its previous value and the edge cost of (v,w).


__Algorithm__: long Graph::minimumSpanningTree(int source)

Initialize each vertex in the list, key, and mstSet to INFINITY and not found;

```cpp
    for(int i = 0; i < numVertices; i++)        // <== O(n)
        key[i] = INF;
        mstSet[i] = false;
        vertexList[i].setParent(-1);
        vertexList[i].setDistance(INF);
    key[source] = 0;                            // <== O(1)
    parent[source] = -1;                        // <== O(1)
```

> __Initialization takes O(n)__

for each vertex in the graph find the minimum weight adjacent edge and set it as discovered
```cpp
    for(int count = 0; count < numVertices; count++) // <== O(n)
        int u = minKey(key, mstSet);
        mstSet[u] = true;
```

__Algorithm__: long Graph::minKey(long key[], bool mstSet[])
```cpp
    long min = INF;
    long min_index;
    for(int v = 0; v < numVertices; v++)            // <== O(n)
        if(mstSet[v] == false && key[v] < min)
            min = key[v];
            min_index = v;

    return min_index;
```

> __Process to find the minimum edge is O(n*n) => O(n^2)__

Checking every edge that is adjacent to the current edge and to see if it has already been visited is a __O(n)__ process.
```cpp
        for(int v = 0; v < numVertices; v++)         // <== O(n)

            if (adjacencyMatrix[u][v] > 0 && mstSet[v] == false && adjacencyMatrix[u][v] < key[v])
                parent[v] = u;
                vertexList[v].setParent(u);
                key[v] = adjacencyMatrix[u][v];
                vertexList[v].setDistance(key[v]);
```

> __Process to find the vertex with the smallest possible weight which has not been discovered for each vertex is O(n*n)__

> __Since the process takes n + n^2 + n^2__

> __O(n + n^2 + n^2) = O(n^2)__

### Heap

Heap worst case,best case and average case are __O(nlogn)__
The buildMaxHeap() operation is run once, and is __O(n)__ in performance. The bubbleDown() function is __O(log(n))__, and is called __n__ times. Therefore, the performance of this algorithm is __O(n + n * log(n))__ which evaluates to __O(n log n)__.
Also, the bubbleDown version of heapify has __O(n)__ time complexity, while the bubbleUp version given below has __O(n log n)__ time complexity due to its equivalence with inserting each element, one at a time, into an empty heap.

