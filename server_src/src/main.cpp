#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "ServerCore.hpp"
#include "SharedObjects.hpp"
#include "Tools/PasswordTools.hpp"

int32_t main(int32_t argc, char *argv[])
{
    if (argc < 2) {
        qFatal("Settings file is not set");

        return 1;
    }

    std::cout << PasswordTools::passwordHash("asd") << std::endl;

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
