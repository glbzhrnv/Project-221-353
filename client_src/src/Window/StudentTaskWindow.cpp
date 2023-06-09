#include <sstream>
#include <QMessageBox>
#include "Model/UserStateModel.hpp"
#include "Window/StudentTaskWindow.hpp"
#include "ui_StudentTaskWindow.h"
#include "SharedObjects.hpp"

StudentTaskWindow::StudentTaskWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentTaskWindow)
{
    ui->setupUi(this);

    ptr = SharedObjects::getPointer();
}

StudentTaskWindow::~StudentTaskWindow()
{
    delete ui;
}

void StudentTaskWindow::setTask(QJsonObject params, std::string msg)
{
    std::stringstream finalText;
    finalText << msg << "\n\n" << params["data"].toString().toStdString();

    taskId = params["id"].toInt();
    ui->Content->setText(finalText.str().c_str());
}

void StudentTaskWindow::on_Send_clicked()
{
    QString answer = ui->Answer->text();
    if (answer == "") {
        return;
    }

    QJsonObject result = ptr->getUserState()->sendTask(taskId, answer);

    std::string message;
    if (result["code"] == 0) {
        message = "Ответ верный";
    } else {
        message = "Ответ неверный";
    }

    this->hide();

    QMessageBox::information(this, "Login", message.c_str());
}
