#include "graph.h"

Graph::Graph()
{
    this->numVertices = 0;
}


void Graph::createGraph(Database *db)
{
    QSqlQuery queryResult;
    queryResult =  db->getDistances();

    qDebug() <<    "Query Result : " << queryResult.value(0);
}
