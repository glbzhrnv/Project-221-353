#include <QApplication>
#include "Adapter/ConnectionStatusAdapter.hpp"
#include "Window/NotificationWindow.hpp"
#include "SharedObjects.cpp"

ConnectionStatusAdapter::ConnectionStatusAdapter(QWidget *parent)
    : AbstractAdapter(parent)
    , window(new NotificationWindow(parent))
{
    std::shared_ptr<QTcpSocket> socket = SharedObjects::getPointer()
        ->getSocket();

    connect(
        socket.get(), &QTcpSocket::errorOccurred,
        this, &ConnectionStatusAdapter::connectionError
    );

    connect(
        socket.get(), &QTcpSocket::connected,
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
