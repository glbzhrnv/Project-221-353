/**
 * @file
 * @brief Ядро сервера
 */
#ifndef SERVER_CORE_HPP
#define SERVER_CORE_HPP

#include <map>
#include <memory>
#include <QtGlobal>
#include <QObject>
#include <QTcpServer>
#include "ClientCore.hpp"

/**
 * @brief Ядро сервера
 *
 * Обеспечивает инкапсулирование сокетов клиентов в экземпляры класса ClientCore
 */
class ServerCore : public QObject
{
    Q_OBJECT

public slots:
    /**
     * @brief Слот, реагирующий на подключение нового клиента
     *
     * В данном слоте и происходит сам процесс инкапсуляции
     */
    void slotAddConnection();

    /**
     * @brief Производит удаление закрытых сокетов
     * @param id Идентификатор сокета, подележащего удалению
     */
    void slotDeleteConnection(quint64 id);

public:
    /**
     * @brief Конструктор, открывающий сокет сервера
     * @param parent Родственный объект
     */
    ServerCore(QObject *parent = nullptr);

    /**
     * @brief Деструктор, закрывающий открытые клиентские сокеты
     */
    ~ServerCore();

    /**
     * @brief Производит создание серверного сокета
     */
    void setupSocket();

protected:
    /**
     * @brief Сокет сервера, к которому производятся подключения
     */
    QTcpServer* mTcpServer;

    /**
     * @brief Структура, хранящая в себе ссылки на все открыты клиентские сокеты
     */
    std::map<quint64, std::unique_ptr<ClientCore>> clientsMap;
};
#endif // SERVER_CORE_HPP
