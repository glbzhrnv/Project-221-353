#include <QCoreApplication>
#include <QDebug>
#include "../include/ServerCore.hpp"
#include "../include/SharedObjects.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        qFatal("Settings file is not set");

        return 1;
    }

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
