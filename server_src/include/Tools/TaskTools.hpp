#ifndef TASKTOOLS_HPP
#define TASKTOOLS_HPP

#include <QJsonObject>
#include "Model/TaskModel.hpp"
#include "Enum/FSMTypeEnum.hpp"

class TaskTools
{
public:
    /**
     * @brief Создаёт задание на основе переданного типа
     * @param type Тип задания
     * @return Структура с данными задания
     */
    static taskData create(ENUM::FSMTypeEnum type);
};

#endif // TASKTOOLS_HPP
