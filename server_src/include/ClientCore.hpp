/**
 * @file
 * @brief Хранилище соединения клиента
 */
#ifndef CLIENT_CORE_HPP
#define CLIENT_CORE_HPP

#include <QObject>
#include <QtGlobal>
#include <QTcpSocket>

/**
 * @brief Хранилище соединения клиента
 */
class ClientCore: public QObject
{
    Q_OBJECT

signals:
    /**
     * @brief Сигнал удаления пользовательского сокета
     * @param id Идентификатор сокета
     */
    void signalClientClose(quint64 id);

public:
    explicit ClientCore(QTcpSocket* connection, quint64 id);

    ~ClientCore();

    /**
     * @brief Возвращает пользовательский сокет
     * @return QTcpSocket* Указатель на пользовательский сокет
     */
    QTcpSocket* getSocket();

    /**
     * @brief Возвращает идентификатор сокета
     * @return quint64 Идентификатор сокета
     */
    quint64 getSocketId();

public slots:
    /**
     * @brief Слот для чтения доступных данных из сокета
     */
    void slotReadData();

    /**
     * @brief Слот для закрытия сокета
     */
    void slotDisconnect();

protected:
    /**
     * @brief Состояние объекта
     *
     * 0 - Состояние по умолчанию
     * 1 - Сокет закрыт
     */
    int state = 0;

    /**
     * @brief Указатель на пользовательский сокет
     */
    QTcpSocket* socket;

    /**
     * @brief Идентификатор сокета
     */
    quint64 socketId;
};

#endif // CLIENT_CORE_HPP
