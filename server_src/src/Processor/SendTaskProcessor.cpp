#include <QJsonObject>
#include "Processor/SendTaskProcessor.hpp"
#include "Enum/FSMTypeEnum.hpp"
#include "Tools/TaskTools.hpp"

SendTaskProcessor::SendTaskProcessor()
{
}

QByteArray SendTaskProcessor::process(QJsonObject params, ClientCore *client)
{
    return "\"code\":0";
}
