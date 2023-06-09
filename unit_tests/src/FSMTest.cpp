#include <QDebug>
#include <string>
#include <QtTest>
#include <time.h>
#include "Task/MealyGen.hpp"
#include "Task/MealySolve.hpp"
#include "Task/MealyState.hpp"
#include "Task/MealySuperposition.hpp"
#include "Task/MealyToMoore.hpp"
#include "Task/MooreGen.hpp"
#include "Task/MooreSolve.hpp"
#include "Task/MooreState.hpp"
#include "Task/MooreSuperposition.hpp"
#include "qtestcase.h"

class FSMTest : public QObject
{
    Q_OBJECT

public:
    FSMTest();
    ~FSMTest();

private slots:
    void MealySolveTest();

    void MealySuperpositionTest();

    void MealyToMooreTest();

    void MooreSolveTest();

    void MooreSuperpositionTest();
};

FSMTest::FSMTest()
{
    srand(time(NULL));
}

FSMTest::~FSMTest()
{
}

void FSMTest::MealySolveTest()
{
    std::string testCase = "2|3|A|B|C|1|0|0|1|1|2|0|1|1|1|1|1|0";
    std::string request = "010101";
    std::string expectedResult = "101111";

    MealyState *machineState = MealyGen::parseTable(testCase);
    MealySolve *solver = new MealySolve(machineState);
    std::string realResult = solver->run(request);

    delete solver;
    delete machineState;

    QVERIFY(realResult == expectedResult);
}

void FSMTest::MealySuperpositionTest()
{
    std::string testCaseM1 = "2|3|A|B|C|1|1|1|1|1|1|0|0|1|1|0|1|0";
    std::string testCaseM2 = "2|3|X|Y|Z|0|1|1|1|0|0|0|1|1|2|1|0|0";
    std::string request = "010101";
    std::string expectedResult = "100010011001";

    MealyState *machineStateM1 = MealyGen::parseTable(testCaseM1);
    MealyState *machineStateM2 = MealyGen::parseTable(testCaseM2);
    MealySuperposition *solver = new MealySuperposition(machineStateM1, machineStateM2);
    std::string realResult = solver->run(request);

    delete solver;
    delete machineStateM1;
    delete machineStateM2;

    QVERIFY(realResult == expectedResult);
}

void FSMTest::MealyToMooreTest()
{

    std::string testCase = "2|3|A|B|C|0|1|0|2|1|2|1|0|1|0|1|0|0";
    std::string expectedResult = "2|4|3|2|1|0|3|3|2|1|2|1|0|0|0";

    MealyToMoore *solver = new MealyToMoore();
    std::string realResult = solver->run(testCase);

    delete solver;

    QVERIFY(realResult == expectedResult);
}

void FSMTest::MooreSolveTest()
{
    std::string testCase = "2|3|A|B|C|0|1|0|1|1|1|0";
    std::string request = "010101";
    std::string expectedResult = "ABABAB";

    MooreState *machineState = MooreGen::parseTable(testCase);
    MooreSolve *solver = new MooreSolve(machineState);
    std::string realResult = solver->run(request);

    delete solver;
    delete machineState;

    QVERIFY(realResult == expectedResult);
}

void FSMTest::MooreSuperpositionTest()
{
    std::string testCaseM1 = "2|3|A|B|C|1|1|0|1|2|1|0";
    std::string testCaseM2 = "2|3|X|Y|Z|1|0|0|1|2|1|0";
    std::string request = "010101";
    std::string expectedResult = "AXBYBYAXBXAY";

    MooreState *machineStateM1 = MooreGen::parseTable(testCaseM1);
    MooreState *machineStateM2 = MooreGen::parseTable(testCaseM2);
    MooreSuperposition *solver = new MooreSuperposition(machineStateM1, machineStateM2);
    std::string realResult = solver->run(request);

    delete solver;
    delete machineStateM1;
    delete machineStateM2;

    QVERIFY(realResult == expectedResult);
}

QTEST_APPLESS_MAIN(FSMTest)

#include "FSMTest.moc"
