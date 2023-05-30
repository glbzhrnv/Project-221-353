#ifndef TASKMODEL_HPP
#define TASKMODEL_HPP

#include <stdint.h>
#include "Tools/TaskTools.hpp"

class TaskModel
{
public:
    static void reg(taskData &task, Model::UserModel::userData *data);

    static bool isExists(taskData &task);

    static bool isOwnedBy(taskData &task, Model::UserModel::userData *data);
};

#endif // TASKMODEL_HPP
