#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include "../../include/Processor/AbstractProcessor.hpp"

QByteArray AbstractProcessor::createResponse(
    int code,
    QJsonObject* response
) {
    QJsonObject result, midResponse;
    if (response != nullptr) {
        midResponse = *response;
    }

    result["code"] = code;
    result["response"] = midResponse;
    result["stamp"] = QDateTime::currentSecsSinceEpoch();

    return QJsonDocument(result).toJson();
}
