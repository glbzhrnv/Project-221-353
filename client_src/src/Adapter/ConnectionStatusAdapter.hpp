#ifndef CONNECTIONSTATUSADAPTER_HPP
#define CONNECTIONSTATUSADAPTER_HPP

#include <QAbstractSocket>
#include "Adapter/AbstractAdapter.hpp"
#include "Window/NotificationWindow.hpp"

class ConnectionStatusAdapter: public AbstractAdapter
{
public:
    ConnectionStatusAdapter(QWidget *parent = nullptr);
    ~ConnectionStatusAdapter();

public slots:
    void connectionError(QAbstractSocket::SocketError socketError);

    void connected();

protected:
    NotificationWindow* window;
};

#endif // CONNECTIONSTATUSADAPTER_HPP
