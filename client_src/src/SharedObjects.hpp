/**
 * @file
 * @brief Хранилище разделённых объектов клиента
*/
#ifndef SHAREDOBJECTS_HPP
#define SHAREDOBJECTS_HPP

#include "Adapter/AbstractAdapter.hpp"
#include <memory>
#include <map>
#include <QTcpSocket>
#include <QJsonObject>
#include <QWidget>

/**
 * @brief Хранилище разделённых объектов сервера
 */
class SharedObjects
{
public:
    ~SharedObjects();

    /**
     * @brief Устанавливает путь до файла с конфигурацией
     * @param path Путь до конфигурации
     *
     * @note Файл конфигурации должен иметь json тип.
     * @attention Путь можно изменить только до получения первого указателя
     *
     * Пример конфигурации можно найти здесь: /examples/configuration.json
     */
    static void setSettingsFilePath(std::string path);

    /**
     * @brief Возвращает указатель  на общий экземпляр класса SharedObjects
     * @return std::shared_ptr<SharedObjects> Указатель на общий экземпляр класса
     *
     * @note При первом получении ссылки происходит инициализация класса
     */
    static std::shared_ptr<SharedObjects> getPointer();

    /**
     * @brief Возвращает настройки сервера
     * @return const QJsonObject
     */
    const QJsonObject getSettings();

    /**
     * @brief Возвращает экземпляр сокета
     * @return QTcpSocket Экземпляр сокета
     */
    std::shared_ptr<QTcpSocket> getSocket();

    uint64_t windowIdGet(uint32_t name, uint32_t copy);

    bool windowExists(uint32_t name, uint32_t copy);

    bool windowExists(uint64_t windowId);

    void windowSet(QWidget* window, uint32_t name, uint32_t copy = 0);

    std::shared_ptr<QWidget> windowGet(uint32_t name, uint32_t copy = 0);

    void adapterAdd(AbstractAdapter*);

protected:
    /**
     * @brief Узакатель на общий экзмпляр класса
     */
    static std::shared_ptr<SharedObjects> self;

    /**
     * @brief Путь до конфигурации
     */
    static std::string settingsFilePath;

    /**
     * @brief Объект, содержащий параметры конфигурации
     */
    QJsonObject settings;

    /**
     * @brief Экземпляр сокета
     */
    std::shared_ptr<QTcpSocket> socket;

    std::map<uint64_t, std::shared_ptr<QWidget>>* windowsHeap;

    std::vector<std::unique_ptr<AbstractAdapter>>* adaptersHeap;

    /**
     * @brief Защищённый конструктор
     *
     * Предотвращает создание нескольких объектов класса SharedObjects
     */
    SharedObjects();

    /**
     * @brief Удаление копирующего конструктора
     */
    SharedObjects(const SharedObjects&) = delete;

    /**
     * @brief Удаление копирующего конструктора
     */
    SharedObjects& operator= (SharedObjects&) = delete;

    void setupSettings();
};

#endif // SHAREDOBJECTS_HPP
