#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include "Tools/TaskTools.hpp"
#include "Model/UserModel.hpp"
#include "SharedObjects.hpp"

taskData TaskTools::taskCreate(ENUM::FSMTypeEnum type)
{
    return {
        .id = 0,
        .type = type,
        .data = "",
        .solution = "",
        .is_solved = true
    };
}

bool TaskTools::taskSolve(taskData &task, bool resolve)
{
    if (!resolve && task.is_solved) {
        return true;
    }

    task.solution = "";
    task.is_solved = true;

    return true;
}

bool TaskTools::taskCheckSolution(taskData &task, Model::UserModel::userData *data)
{
    if (data != nullptr) {

    }
}
