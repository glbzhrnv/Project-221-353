#ifndef STATMODEL_HPP
#define STATMODEL_HPP

#include <stdint.h>
#include <QJsonObject>
#include "Model/TaskModel.hpp"
#include "Model/UserModel.hpp"

class StatModel
{
public:
    /**
     * @brief Давить решение задания в БД
     * @param task - Данные задания
     * @param user - Данные пользователя
     * @param answer - Решение
     * @param isCorrect - Корректность решения
     */
    static void add(
        taskData &task,
        Model::UserModel::userData *user,
        std::string answer,
        bool isCorrect
    );

    /**
     * @brief Возвращает количество решённых заданий
     * @param user - Данные пользователя
     * @param correct - Фильтр корректности решения
     * @return Число заданий
     */
    static int32_t getCount(Model::UserModel::userData *user, bool correct);

    /**
     * @brief Извлекает данные статистики из БД
     * @param limit - Ограничение количества заданий
     * @param offset - Отступ
     * @return Данные статистики
     */
    static QJsonObject getData(int32_t limit, int32_t offset = 0);
};

#endif // STATMODEL_HPP
