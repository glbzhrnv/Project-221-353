/**
 * @file
 * @brief Хранилище разделённых объектов сервера
*/
#ifndef SHAREDOBJECTS_HPP
#define SHAREDOBJECTS_HPP

#include <memory>
#include <QJsonObject>
#include <QSqlDatabase>

/**
 * @brief Хранилище разделённых объектов сервера
 */
class SharedObjects
{
public:
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
     * @brief Возвращает объект соединения с БД
     * @return const QSqlDatabase Соединение с БД
     */
    const QSqlDatabase getDatabase();
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
     * @brief Соединение с БД
     */
    QSqlDatabase dbConnection;

    /**
     * @brief Защищённый конструктор
     *
     * Предотвращает создание нескольких объектов класса SharedObjects
     */
    SharedObjects();

    /**
     * @brief Удаление копирующего конструктора
     */
    SharedObjects(const SharedObjects& ) = delete;

    /**
     * @brief Удаление копирующего конструктора
     */
    SharedObjects& operator= (SharedObjects&) = delete;

    /**
     * @brief Метод создания соединения
     */
    void setupDatabaseConnection();
};

#endif // SHAREDOBJECTS_HPP
