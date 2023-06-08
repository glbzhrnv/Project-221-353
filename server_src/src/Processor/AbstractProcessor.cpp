#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include "Processor/AbstractProcessor.hpp"

AbstractProcessor::AbstractProcessor()
{
}

AbstractProcessor::~AbstractProcessor()
{
}

QByteArray AbstractProcessor::createResponse(
    int32_t code,
    QJsonObject *response,
    std::string text
) {
    QJsonObject midResponse;
    if (response != nullptr) {
        midResponse = *response;
    }

    QJsonObject result = {
        {"code", code},
        {"text", text.c_str()},
        {"response", midResponse},
        {"stamp", QDateTime::currentSecsSinceEpoch()}
    };

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

QByteArray AbstractProcessor::process(QJsonObject params, ClientCore *client)
{
    return "{\"code\":-1}";
}
