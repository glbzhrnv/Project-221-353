#ifndef CLIENT_CORE_HPP
#define CLIENT_CORE_HPP

#include <QObject>
#include <QtGlobal>
#include <QTcpSocket>

class ClientCore: public QObject
{
    Q_OBJECT

public slots:
    void slotReadData();
    void slotDisconnect();

signals:
    void signalClientClose(quint64 id);

public:
    explicit ClientCore(QTcpSocket* connection, quint64 id);
    ~ClientCore();

protected:
    int state = 0;
    QTcpSocket* socket;
    quint64 socketId;
};

#endif // CLIENT_CORE_HPP
