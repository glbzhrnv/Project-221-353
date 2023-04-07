#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include "Processor/AbstractProcessor.hpp"

QByteArray AbstractProcessor::createResponse(
    int32_t code,
    QJsonObject* response
) {
    QJsonObject midResponse;
    if (response != nullptr) {
        midResponse = *response;
    }

    QJsonObject result = {
        {"code", code},
        {"response", midResponse},
        {"stamp", QDateTime::currentSecsSinceEpoch()}
    };

    return QJsonDocument(result).toJson();
}
