#include <QCoreApplication>
#include "../include/ServerCore.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ServerCore server;

    return app.exec();
}
