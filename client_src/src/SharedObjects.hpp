/**
 * @file
 * @brief Хранилище разделённых объектов клиента
*/
#ifndef SHAREDOBJECTS_HPP
#define SHAREDOBJECTS_HPP

#include <memory>
#include <map>
#include <string>
#include <QJsonObject>
#include <QWidget>
#include "Adapter/AbstractAdapter.hpp"
#include "Model/UserStateModel.hpp"
#include "Transport.hpp"

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
     * @brief Возвращает экземпляр соединения
     * @return Соединение
     */
    Transport* getTransport();

    /**
     * @brief Возвращает объект с данными пользователя
     * @return Данные пользователя
     */
    UserStateModel* getUserState();

    /**
     * @brief Формирует идентификатор окна, подходящий под стандарты хранилища
     * @param name - Идентификатор окна
     * @param copy - Идентификатор копии
     * @return Сформированный идентификатор
     */
    uint64_t windowIdGet(uint32_t name, uint32_t copy);

    /**
     * @brief Проверяет существование окна в хранилище
     * @param windowId - Идентификатор окна
     * @param copy - Идентификатор копии
     * @return Результат проверки
     */
    bool windowExists(uint32_t name, uint32_t copy);

    /**
     * @brief Проверяет существование окна в хранилище
     * @param windowId - Идентификатор окна
     * @return Результат проверки
     */
    bool windowExists(uint64_t windowId);

    /**
     * @brief Добавляет окно в хранилище
     * @param window - Экземпляр окна
     * @param name - Идентификатор окна
     * @param copy - Идентификатор копии
     */
    void windowSet(QWidget* window, uint32_t name, uint32_t copy = 0);

    template <class T = QWidget>
    std::shared_ptr<T> windowGet(uint32_t name, uint32_t copy = 0)
    {
        uint64_t windowId = windowIdGet(name, copy);

        if (!windowExists(windowId)) {
            return nullptr;
        }

        return std::static_pointer_cast<T>(windowsHeap[windowId]);
    }

    /**
     * @brief Добавляет адаптер в хранилище
     */
    void adapterAdd(AbstractAdapter*);

protected:
    /**
     * @brief Узакатель на общий экзмпляр класса
     */
    inline static std::shared_ptr<SharedObjects> self;

    /**
     * @brief Путь до конфигурации
     */
    inline static std::string settingsFilePath;

    /**
     * @brief Объект, содержащий параметры конфигурации
     */
    QJsonObject settings;

    /**
     * @brief Экземпляр сокета
     */
    Transport transport;

    std::map<uint64_t, std::shared_ptr<QWidget>> windowsHeap;

    std::vector<std::unique_ptr<AbstractAdapter>> adaptersHeap;

    UserStateModel userState;

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
