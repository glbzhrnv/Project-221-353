#include <QCoreApplication>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ServerCore.hpp"
#include "SharedObjects.hpp"
#include "Task/MealyState.hpp"
#include "Task/MealyGen.hpp"
#include "Task/MealySolve.hpp"

int32_t main(int32_t argc, char *argv[])
{
    if (argc < 2) {
        qFatal("Settings file is not set");

        return 1;
    }
    srand(time(NULL));

    char *states = new char[3] {
        'A', 'B', 'C'
    };
    std::string table = MealyGen::genTable(states, 3, 2, 0);
    qDebug() << table.c_str();

    MealyState* machine = MealyGen::parseTable(table);

//    qDebug() << (machine == nullptr);

//    for (auto transition : *machine->getTransitions()) {
//        if (transition.second == nullptr) {
//            qDebug() << "Blyat";

//            continue;
//        }
//        qDebug() << transition.second->getOutput();
//    }

    MealySolve *ms = new MealySolve(machine);
    qDebug() << ms->run("010101").c_str();
    delete ms;

    QCoreApplication app(argc, argv);

    SharedObjects::setSettingsFilePath(argv[1]);
    SharedObjects::getPointer();

    ServerCore server;
    try {
        server.setupSocket();
    } catch (std::runtime_error &e) {
        qInfo("Server setup failed");

        return 1;
    }

    qInfo("Server is setted up");

    return app.exec();
}
