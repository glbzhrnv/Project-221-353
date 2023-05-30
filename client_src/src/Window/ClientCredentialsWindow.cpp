#include <QDialog>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <memory>
#include "ClientCredentialsWindow.hpp"
#include "ui_ClientCredentialsWindow.h"
#include "Model/UserStateModel.hpp"
#include "Window/NotificationWindow.hpp"
#include "Window/StudentGetTaskWindow.hpp"
#include "Window/TeacherStatsWindow.hpp"
#include "SharedObjects.hpp"
#include "Transport.hpp"

ClientCredentialsWindow::ClientCredentialsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientCredentialsWindow)
{
    ui->setupUi(this);

    Transport *socket = SharedObjects::getPointer()
        ->getTransport();

    connect(
        socket->getSocket(), &QTcpSocket::connected,
        this, [=]() { this->setEnabled(true); }
    );
}

ClientCredentialsWindow::~ClientCredentialsWindow()
{
    delete ui;
}

void ClientCredentialsWindow::on_Login_clicked()
{
    std::shared_ptr<SharedObjects> ptr = SharedObjects::getPointer();

    UserStateModel *user = ptr->getUserState();

    std::shared_ptr<NotificationWindow> notification = ptr->windowGet<NotificationWindow>(
        NotificationWindow::WINDOW_ID
    );



    std::string login = ui->AuthEmail->text().toStdString();
    std::string password = ui->AuthPassword->text().toStdString();

    QJsonObject response = user->login(login, password);

    if (response["code"] != 0) {
        notification->updateText("Invalid login or password");

        return;
    }

    QJsonObject result = response["result"].toObject();

    QWidget *window;
    int32_t windowId;
    if (result["is_teacher"].toBool()) {
        window = new TeacherStatsWindow;
        windowId = TeacherStatsWindow::WINDOW_ID;
    } else {
        window = new StudentGetTaskWindow;
        windowId = StudentGetTaskWindow::WINDOW_ID;
    }

    ptr->windowSet(window, windowId);
    window->show();

    this->hide();
}

void ClientCredentialsWindow::on_Register_clicked()
{
    std::shared_ptr<SharedObjects> ptr = SharedObjects::getPointer();

    if (ui->RegPassword->text() != ui->RegPasswordRep->text()) {
        QMessageBox::information(this, "Reg", "Passwords must be the same");

        return;
    }

    QJsonObject response = ptr->getUserState()->reg(
        ui->RegEmail->text().toStdString(),
        ui->RegPassword->text().toStdString()
    );

    if (response["code"].toInt() != 0) {
        QMessageBox::information(this, "Reg", "Unable to register");
    }
}
