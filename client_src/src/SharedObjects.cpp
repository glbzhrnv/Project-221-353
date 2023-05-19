#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QJsonDocument>
#include <memory>
#include "Adapter/AbstractAdapter.hpp"
#include "Exception/ConfigurationException.hpp"
#include "Window/NotificationWindow.hpp"
#include "SharedObjects.hpp"

SharedObjects::SharedObjects()
    : socket(std::shared_ptr<QTcpSocket>(new QTcpSocket()))
    , windowsHeap(new std::map<uint64_t, std::shared_ptr<QWidget>>)
    , adaptersHeap(new std::vector<std::unique_ptr<AbstractAdapter>>)
{
    setupSettings();

    windowSet(new NotificationWindow, NotificationWindow::WINDOW_ID);

    socket->connectToHost("127.0.0.1", 33333);
}

SharedObjects::~SharedObjects()
{
}

void SharedObjects::setSettingsFilePath(std::string path)
{
    settingsFilePath = path;

    if (self == nullptr) {
        self->setupSettings();
    }
}

std::shared_ptr<SharedObjects> SharedObjects::getPointer()
{
    if (self == nullptr) {
        self = std::shared_ptr<SharedObjects>(
            new SharedObjects()
        );
    }

    return self;
}

std::shared_ptr<QTcpSocket> SharedObjects::getSocket()
{
    return socket;
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
    return windowsHeap->count(windowId) == 0;
}

void SharedObjects::windowSet(QWidget* window, uint32_t name, uint32_t copy)
{
    uint64_t windowId = windowIdGet(name, copy);

    (*windowsHeap)[windowId] = std::shared_ptr<QWidget>(window);
}

std::shared_ptr<QWidget> SharedObjects::windowGet(uint32_t name, uint32_t copy)
{
    uint64_t windowId = windowIdGet(name, copy);

    if (!windowExists(windowId)) {
        return nullptr;
    }

    return (*windowsHeap)[windowId];
}

void SharedObjects::adapterAdd(AbstractAdapter* adapter)
{
    adaptersHeap->push_back(std::unique_ptr<AbstractAdapter>(adapter));
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
