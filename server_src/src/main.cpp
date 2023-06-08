#include <QCoreApplication>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ServerCore.hpp"
#include "SharedObjects.hpp"

int32_t main(int32_t argc, char *argv[])
{
    if (argc < 2) {
        qFatal("Settings file is not set");

        return 1;
    }

    srand(time(NULL));
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
