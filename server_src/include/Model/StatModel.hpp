#ifndef STATMODEL_HPP
#define STATMODEL_HPP

#include <stdint.h>
#include <QJsonObject>
#include "Model/TaskModel.hpp"
#include "Model/UserModel.hpp"

class StatModel
{
public:
    static void add(
        taskData &task,
        Model::UserModel::userData *user,
        std::string answer,
        bool isCorrect
    );

    static int32_t getCount(Model::UserModel::userData *user, bool correct);

    static QJsonObject getData(int32_t limit, int32_t offset = 0);
};

#endif // STATMODEL_HPP
