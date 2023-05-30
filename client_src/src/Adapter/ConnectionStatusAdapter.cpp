#include <QApplication>
#include "Adapter/ConnectionStatusAdapter.hpp"
#include "Window/NotificationWindow.hpp"
#include "SharedObjects.hpp"

ConnectionStatusAdapter::ConnectionStatusAdapter(QWidget *parent)
    : AbstractAdapter(parent)
    , window(new NotificationWindow(parent))
{
    Transport* socket = SharedObjects::getPointer()
        ->getTransport();

    connect(
        socket->getSocket(), &QTcpSocket::errorOccurred,
        this, &ConnectionStatusAdapter::connectionError
    );

    connect(
        socket->getSocket(), &QTcpSocket::connected,
        this, &ConnectionStatusAdapter::connected
    );
}

ConnectionStatusAdapter::~ConnectionStatusAdapter()
{
    delete window;
}

void ConnectionStatusAdapter::connectionError(
    QAbstractSocket::SocketError socketError
) {
    window->updateText("Unable to connect to the server");
    window->show();

    connect(
        window, &NotificationWindow::ConfirmClicked,
        this, [=]() { QApplication::quit(); }
    );
}

void ConnectionStatusAdapter::connected()
{
    window->hide();
}
