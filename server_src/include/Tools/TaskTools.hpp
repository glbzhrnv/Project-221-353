#ifndef TASKTOOLS_HPP
#define TASKTOOLS_HPP

#include <QJsonObject>
#include "Model/TaskModel.hpp"
#include "Enum/FSMTypeEnum.hpp"

class TaskTools
{
public:
    static taskData create(ENUM::FSMTypeEnum type);
};

#endif // TASKTOOLS_HPP
