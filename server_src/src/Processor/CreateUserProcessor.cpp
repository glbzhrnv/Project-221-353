#include "../../include/Processor/CreateUserProcessor.hpp"

void CreateUserProcessor::process(QJsonValue params, ClientCore* client)
{
    client->getSocket()->write("\nCreating user\n");
}
