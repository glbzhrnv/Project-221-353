#ifndef TASKMODEL_HPP
#define TASKMODEL_HPP

#include <stdint.h>
#include <string>
#include "Enum/FSMTypeEnum.hpp"
#include "Model/UserModel.hpp"

/**
 * @brief Данные задания
 */
struct taskData {
    int32_t id;
    ENUM::FSMTypeEnum type;
    std::string data;
    std::string solution;
    bool is_solved;
};

/**
 * @brief Данные решения
 */
struct taskResult {
    int32_t id;
    int32_t type;
    std::string answer;
    bool is_correct;
};

/**
 * @brief Класс, предоставляющий возможность управлять заданиями пользователя
 */
class TaskModel
{
public:
    /**
     * @brief Регистрирует задание с базе данных
     * @param task - Данные задания
     * @param data - Данные пользователя
     */
    static void reg(taskData &task, Model::UserModel::userData *data);

    /**
     * @brief Получает даныне задания
     * @param id - Идентификатор задания
     * @param owner - Идентификатор владельца задания
     * @param data - Указатель на данные задания
     * @return Результат извлечения данных из БД
     */
    static bool getData(int32_t id, int32_t owner, taskData &data);

    /**
     * @brief Проверяет существование задания в БД
     * @param owner - Идентификатор владельца
     * @param type - Тип задания
     * @return - Статус задания
     */
    static int32_t isRegistered(int32_t owner, int32_t type);

    /**
     * @brief Проверяет текущий статус задания
     * @param owner - Идентификатор владельца
     * @param type - Тип задания
     * @param result - Указатель на данные решения
     * @return - Статус задания
     */
    static int32_t isSolved(
        int32_t owner,
        int32_t type,
        taskResult &result
    );
};

#endif // TASKMODEL_HPP
