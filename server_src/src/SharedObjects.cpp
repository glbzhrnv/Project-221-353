#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include "Exception/ConfigurationException.hpp"
#include "Migration/MigrationsIndex.hpp"
#include "SharedObjects.hpp"

SharedObjects::SharedObjects()
{
    if (settingsFilePath == "") {
        throw new ConfigurationException("Configuration file path is not set");
    }

    QFile settingsFile(settingsFilePath.c_str());
    settingsFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if (!settingsFile.isReadable()) {
        throw new ConfigurationException("Unable to read settings file");
    }
    QString rawSettings = settingsFile.readAll();
    settingsFile.close();

    QJsonDocument settingsDoc = QJsonDocument::fromJson(rawSettings.toUtf8());
    if (!settingsDoc.isObject()) {
        throw new ConfigurationException("Settings file is empty");
    }
    settings = settingsDoc.object();

    setupDatabaseConnection();
}

SharedObjects::~SharedObjects()
{
    dbConnection.close();
}

void SharedObjects::setSettingsFilePath(std::string path)
{
    if (!self) {
        settingsFilePath = path;
    }
}

std::shared_ptr<SharedObjects> SharedObjects::getPointer()
{
    if (!self) {
        self = std::shared_ptr<SharedObjects>(
            new SharedObjects()
        );
    }

    return self;
}

const QJsonObject SharedObjects::getSettings()
{
    return settings;
}

const QSqlDatabase SharedObjects::getDatabase()
{
    return dbConnection;
}

void SharedObjects::setupDatabaseConnection()
{
    QString dbFileName = settings["db_location"].toString();
    dbFileName = dbFileName == "" ? ":memory:" : dbFileName;

    bool setupMigrations = !QFileInfo::exists(dbFileName);

    QSqlDatabase connection = QSqlDatabase::addDatabase("QSQLITE");
    connection.setDatabaseName(dbFileName);

    if (!connection.open()) {
        throw new ConfigurationException("Unable to connect to the database");
    }

    if (setupMigrations) {
        MigrationsIndex::setup(connection);
    }

    dbConnection = connection;
}
