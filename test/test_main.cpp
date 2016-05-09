#include <QtTest/QtTest>
#include "../../src/header/database.h"
#include "../../src/header/graph.h"

class Test_Main : public QObject
{
    Q_OBJECT
private slots:
    // Put testing slots here
    void initTest();

    // Database tests
    void testOpenDB();

    void testNumberStadiums();

    void createGraph();

    void testShortestPath();

    void testVertexSet();

    void testHeap();

private:
    // Put testing variables here
    Database *db;
};

void Test_Main::initTest()
{
    QVERIFY(true);
}

/**
 * @brief Test_Main::testOpenDB
 * Test to see if the test database successfully opens upon instantiation.
 */
void Test_Main::testOpenDB()
{
    db = new Database("test.db", "QSQLITE");
    QVERIFY(db->open());
}

void Test_Main::testNumberStadiums()
{
    QVERIFY(db->open());
    if(db->isOpen())
    {
        qDebug() << "Number of stadiums : " << db->getNumberOfStadiums();
        QVERIFY(db->getNumberOfStadiums() == 30);
    }

}

/**
 * @brief Test_Main::createGraph
 * This test will create a graph object containing the edges and vertices representing
 * the stadiums stored in the database. Once the graph has been created it will check to
 * see that the number of vertices and the number of stadiums match.
 */
void Test_Main::createGraph()
{
    QSqlQuery query;
    Graph testGraph;
    QList<Vertex> vertexList;
    Vertex vertex;
    QString name;
    int id;

    QVERIFY(db->open());
    if(db->isOpen()) {

        qDebug() << "Creating the graph";
        testGraph.createGraph(db);
    }

    // This will test to see if the number of vertices in the graph match the number of
    //	stadiums stored in the database and that both have more than 0 elements stored.
    QVERIFY(testGraph.getNumberVertices() > 0 && db->getNumberOfStadiums() > 0);

    if(testGraph.getNumberVertices() > 0)
    {
        QVERIFY(testGraph.getNumberVertices() == db->getNumberOfStadiums());
        vertexList = testGraph.getVertices();

        for(int index = 0 ;index < vertexList.size(); index++)
        {
            name = vertexList.at(index).getName();
            id = vertexList.at(index).getId();
            query.prepare("select id, name from stadiums where id = :id and name = :name");
            query.bindValue(":name", name);
            query.bindValue(":id", id);
            query.exec();

            while(query.next())
            {
                QVERIFY(query.record().field("id").value().toInt() == id);
                QVERIFY(query.record().field("name").value().toString() == name);
            }
        }
    }
}

/**
 * @brief Test_Main::testVertexSet
 * This will test the vertex set class. It will graph a temporary graph object that will
 * return a list of vertices and assign it into a Vertex set. Then it will iterate through
 * the vertex list and grab every vertex from the list and see if the vertex exists in the
 * vertex set.
 */
void Test_Main::testVertexSet()
{
    VertexSet set;				// Stores a set of vertices
    VertexSet secondSet;		// Secondary set of vertices
    QList<Vertex> vertexList;	// Stores a list of vertices
    Graph graph;				// A graph of vertices
    Vertex vertex;				// Utility vertex object to be used to compare the set,
                                // 	list and graph.

    // Create the graph based on vertices in the database
    graph.createGraph(db);

    // Verify the size is greater than 0
    QVERIFY(graph.getNumberVertices() > 0);

    // Create a set of vertices and a list of vertices
    set = graph.getVertices();
    vertexList = graph.getVertices();

    // Tests to see that the set is not empty and that the number of vertices in the
    //	vertex list is greater than 0.
    QVERIFY(!set.isEmpty() && vertexList.size() > 0);
    QVERIFY(secondSet.isEmpty()); // Test to see that the secondary set is empty

    // This will make sure that the number of vertices in the set matches the number
    //	of vertices represented in the graph.
    QVERIFY(set.getSize() == graph.getNumberVertices());

    for(int i = 0; i < vertexList.size(); i++)
    {
        vertex = vertexList.at(i);
        QVERIFY(set.contains(vertex));
        // Test a secondary set to make sure it does not contain any vertices
        QVERIFY(!secondSet.contains(vertex));
    }
}

void Test_Main::testShortestPath()
{
    Graph testGraph;
    QList<Vertex> vList;
    Vertex v;

    testGraph.createGraph(db);

    v.setId(21);
    testGraph.shortestPath(v);
//    vList = testGraph.getVertices();

//    for(int i =0;i< vList.size();i++)
//    {
//        qDebug() << "Vertex " << vList.at(i).getName() << " with distance cost " << vList.at(i).getDistance();
//    }

//    testGraph.maliks_shortestPath(v);

}

void Test_Main::testHeap()
{
    Graph graph;
    QList<Vertex> list;
    Heap<Vertex, vertexComp> heap;
    Vertex vertex;

    graph.createGraph(db);
    list = graph.getVertices();
    for(int vIndex = 0; vIndex< list.size(); vIndex++)
    {
        vertex = list.at(vIndex);
        vertex.setDistance(vIndex * 50);
        vertex.setId(vIndex);
        heap.insert(vertex);
        list[vIndex] = vertex;
    }

    while(!heap.isEmpty())
    {
        vertex = heap.removeMin();
//        qDebug() << "Removing " << vertex.getId() << " with weight "<<  vertex.getDistance();
        QVERIFY(vertex.getDistance() == list.at(vertex.getId()).getDistance());
    }

}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Main)
#include "test_main.moc"
