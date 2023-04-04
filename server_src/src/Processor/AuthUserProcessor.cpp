#include "../../include/Processor/AuthUserProcessor.hpp"

void AuthUserProcessor::process(QJsonValue params, ClientCore* client)
{
    client->getSocket()->write("\nLogining in\n");
}
