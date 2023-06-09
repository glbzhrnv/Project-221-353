#include <QJsonObject>
#include "Enum/StatType.hpp"
#include "Enum/UserAuthStateEnum.hpp"
#include "Model/StatModel.hpp"
#include "Model/UserModel.hpp"
#include "Model/UserStateModel.hpp"
#include "Processor/GetStatProcessor.hpp"

GetStatProcessor::GetStatProcessor()
{
}

QByteArray GetStatProcessor::process(QJsonObject params, ClientCore *client)
{
    Model::UserStateModel *userState = client->userStateGet();

    if (userState->authStatusGet() != ENUM::LOGGED_IN) {
        return createResponse(ResponseCode::MUST_BE_LOGGED_ID);
    }

    ENUM::StatType type = static_cast<ENUM::StatType>(
        params["type"].toInt()
    );

    QJsonObject response;

    switch (type) {
    case ENUM::TEACHER:
        if (!userState->dataGet()->is_teacher) {
            return createResponse(ResponseCode::MUST_BE_TEACHER);
        }
        response = StatModel::getData(10, 0);
        break;
    case ENUM::USER:
        response["correct"] = StatModel::getCount(userState->dataGet(), true);
        response["incorrect"] = StatModel::getCount(userState->dataGet(), false);
        break;
    }

    return createResponse(ResponseCode::SUCCESS, &response);
}
