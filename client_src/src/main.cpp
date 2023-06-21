#include <QApplication>
#include <memory>
#include "Adapter/ConnectionStatusAdapter.hpp"
#include "Window/ClientCredentialsWindow.hpp"
#include "SharedObjects.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        qFatal("Settings file is not set");

        return 1;
    }

    QApplication app(argc, argv);

    SharedObjects::setSettingsFilePath(argv[1]);

    std::shared_ptr<SharedObjects> ptr = SharedObjects::getPointer();

    ClientCredentialsWindow *loginWindow = new ClientCredentialsWindow;

    ptr->windowSet(loginWindow, ClientCredentialsWindow::WINDOW_ID);
    ptr->adapterAdd(new ConnectionStatusAdapter(loginWindow));

    loginWindow->show();

    return app.exec();
}
