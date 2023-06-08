#include <QDialog>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <memory>
#include "ClientCredentialsWindow.hpp"
#include "ui_ClientCredentialsWindow.h"
#include "Model/UserStateModel.hpp"
#include "Window/StudentGetTaskWindow.hpp"
#include "Window/TeacherStatsWindow.hpp"
#include "SharedObjects.hpp"
#include "Transport.hpp"

ClientCredentialsWindow::ClientCredentialsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientCredentialsWindow)
{
    ui->setupUi(this);

    ptr = SharedObjects::getPointer();

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
    QJsonObject response = ptr->getUserState()->login(
        ui->AuthEmail->text().toStdString(),
        ui->AuthPassword->text().toStdString()
    );

    if (response["code"].toInt(-1) != 0) {
        QMessageBox::information(this, "Login", "Invalid login or password");

        return;
    }

    setupNextWindow(
        response["response"].toObject()
    );
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

    if (response["code"].toInt(-1) != 0) {
        QMessageBox::information(this, "Registration", "Unable to register");

        return;
    }

    setupNextWindow(
        response["response"].toObject()
    );
    //Aiyohg6a
}

void ClientCredentialsWindow::setupNextWindow(QJsonObject value)
{
    qDebug() << value["is_teacher"].toBool(false);

    QWidget *window;
    int32_t windowId;
    if (value["is_teacher"].toBool(false)) {
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
