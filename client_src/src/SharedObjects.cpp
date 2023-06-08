#include <QFile>
#include <QFileInfo>
//#include <QIODevice>
#include <QJsonDocument>
#include <memory>
#include "Adapter/AbstractAdapter.hpp"
#include "Exception/ConfigurationException.hpp"
#include "SharedObjects.hpp"
#include "Transport.hpp"

SharedObjects::SharedObjects()
{
    setupSettings();

    userState.setTransport(&transport);
}

SharedObjects::~SharedObjects()
{
}

void SharedObjects::setSettingsFilePath(std::string path)
{
    settingsFilePath = path;
}

std::shared_ptr<SharedObjects> SharedObjects::getPointer()
{
    if (!self) {
        self = std::shared_ptr<SharedObjects>(
            new SharedObjects
        );
    }

    return self;
}

Transport* SharedObjects::getTransport()
{
    return &transport;
}

UserStateModel* SharedObjects::getUserState()
{
    return &userState;
}

uint64_t SharedObjects::windowIdGet(uint32_t name, uint32_t copy)
{
    return copy << 31 | name;
}

bool SharedObjects::windowExists(uint32_t name, uint32_t copy)
{
    return windowExists(windowIdGet(name, copy));
}

bool SharedObjects::windowExists(uint64_t windowId)
{
    return windowsHeap.count(windowId) == 0;
}

void SharedObjects::windowSet(QWidget* window, uint32_t name, uint32_t copy)
{
    uint64_t windowId = windowIdGet(name, copy);

    windowsHeap[windowId] = std::shared_ptr<QWidget>(window);
}

void SharedObjects::adapterAdd(AbstractAdapter* adapter)
{
    adaptersHeap.push_back(std::unique_ptr<AbstractAdapter>(adapter));
}

void SharedObjects::setupSettings()
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
}
