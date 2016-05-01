#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include "database.h"

struct vertex
{
    QString stadiumName;
    int		id;
};

class Graph
{
public:
    Graph();
    void createGraph(Database *db);

private:
    int* adjacencyMatrix;
    int numVertices;

};

#endif // GRAPH_H
