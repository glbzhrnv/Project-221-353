#ifndef CLIENT_CONTAINER_HPP
#define CLIENT_CONTAINER_HPP

#include <QObject>
#include <QTcpSocket>

class ClientContainer: public QObject
{
    Q_OBJECT

public slots:
    void slotReadCommand();

public:
    explicit ClientContainer();
    ~ClientContainer();

protected:
    QTcpSocket* connection;
    int state = 0;
};

#endif // CLIENT_CONTAINER_HPP
