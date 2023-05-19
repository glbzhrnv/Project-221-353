#include <QTcpSocket>
#include "ClientCredentialsWindow.hpp"
#include "ui_ClientCredentialsWindow.h"
#include "SharedObjects.hpp"

ClientCredentialsWindow::ClientCredentialsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientCredentialsWindow)
{
    ui->setupUi(this);

    std::shared_ptr<QTcpSocket> socket = SharedObjects::getPointer()
        ->getSocket();

    connect(
        socket.get(), &QTcpSocket::connected,
        this, [=]() { this->setEnabled(true); }
    );
}

ClientCredentialsWindow::~ClientCredentialsWindow()
{
    delete ui;
}

void ClientCredentialsWindow::on_Login_clicked()
{

}

void ClientCredentialsWindow::on_Register_clicked()
{

}
