#ifndef TASKMODEL_HPP
#define TASKMODEL_HPP

#include <stdint.h>
#include "Enum/FSMTypeEnum.hpp"
#include "Model/UserModel.hpp"

struct taskData {
    int32_t id;
    ENUM::FSMTypeEnum type;
    std::string data;
    std::string solution;
    bool is_solved;
};

struct taskResult {
    int32_t id;
    int32_t type;
    std::string answer;
    bool is_correct;
};

class TaskModel
{
public:
    static void reg(taskData &task, Model::UserModel::userData *data);

    static bool getData(int32_t id, int32_t owner, taskData &data);

    static int32_t isRegistered(int32_t owner, int32_t type);

    static int32_t isSolved(
        int32_t owner,
        int32_t type,
        taskResult &result
    );
};

#endif // TASKMODEL_HPP
