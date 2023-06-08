#include <string>
#include <QJsonObject>
#include "Model/UserModel.hpp"
#include "Processor/SendTaskProcessor.hpp"
#include "Model/StatModel.hpp"
#include "Model/TaskModel.hpp"

SendTaskProcessor::SendTaskProcessor()
{
}

QByteArray SendTaskProcessor::process(QJsonObject params, ClientCore *client)
{
    taskData task = {};
    Model::UserModel::userData *user = client->userStateGet()->dataGet();

    if (
        !TaskModel::getData(
            params["id"].toInt(),
            user->id,
            task
        )
    ) {
        return createResponse(ResponseCode::INVALID_TASK);
    }

    std::string answer = params["answer"].toString().toStdString();
    bool isCorrect = answer == task.solution;

    StatModel::add(task, user, answer, isCorrect);

    if (isCorrect) {
        return createResponse(ResponseCode::SUCCESS);
    } else {
        return createResponse(ResponseCode::INVALID_ANSWER);
    }
}
