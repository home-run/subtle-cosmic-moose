#include <QtTest/QtTest>
#include "../../src/header/database.h"

class Test_Main : public QObject
{
    Q_OBJECT
private slots:
    // Put testing slots here
    void initTest();

    // Database tests
    void testOpenDB();

private:
    // Put testing variables here
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
    Database *db = new Database("test.db", "QSQLITE");
    QVERIFY(db->open());
}

//#endif //TEST_DATABASE_H

QTEST_MAIN(Test_Main)
#include "test_main.moc"
