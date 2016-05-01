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
        QVERIFY(db->getNumberOfStadiums() == 30);
    }

}

void Test_Main::createGraph()
{
    QSqlQuery query;
    Graph testGraph;

    QVERIFY(db->open());
    if(db->isOpen()) {

        qDebug() << "Creating the graph";
        testGraph.createGraph(db);
    }

}

void Test_Main::testShortestPath()
{
    Graph testGraph;
    QList<Edge> edges;

    testGraph.createGraph(db);

    edges = testGraph.shortestPath(26);

    for(int i = 0; i < edges.size(); i++)
    {
        qDebug() << "From [ " << edges.at(0).idFrom
        << " ] to [ " << edges.at(0).idTo
        << " ] distance : " << edges.at(i).weight;
    }
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Main)
#include "test_main.moc"
