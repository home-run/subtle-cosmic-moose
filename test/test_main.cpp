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

    void createGraph();

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

void Test_Main::createGraph()
{

    QVERIFY(db->open());
    if(db->isOpen())
    {
        db->getDistances();
    }
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Main)
#include "test_main.moc"
