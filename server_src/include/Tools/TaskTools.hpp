#ifndef TASKTOOLS_HPP
#define TASKTOOLS_HPP

#include <QJsonObject>
#include "Enum/FSMTypeEnum.hpp"
#include "Model/UserModel.hpp"

struct taskData {
    int32_t id;
    ENUM::FSMTypeEnum type;
    std::string data;
    std::string solution;
    bool is_solved;
};

class TaskTools
{
public:
    static taskData taskCreate(ENUM::FSMTypeEnum type);

    static bool taskSolve(taskData &data, bool resolve = false);

    static bool taskCheckSolution(taskData &task, Model::UserModel::userData *data = nullptr);
};

#endif // TASKTOOLS_HPP
