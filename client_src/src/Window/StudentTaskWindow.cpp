#include <string>
#include <memory>
#include "Model/UserStateModel.hpp"
#include "Window/NotificationWindow.hpp"
#include "Window/StudentTaskWindow.hpp"
#include "ui_StudentTaskWindow.h"
#include "SharedObjects.hpp"

StudentTaskWindow::StudentTaskWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentTaskWindow)
{
    ui->setupUi(this);
}

StudentTaskWindow::~StudentTaskWindow()
{
    delete ui;
}

void StudentTaskWindow::setTask(QJsonObject params)
{
    taskId = params["task_id"].toInt();
    ui->Content->setText(params["data"].toString());
}

void StudentTaskWindow::on_Send_clicked()
{
    QString answer = ui->Answer->text();
//    if (answer == "") {
//        return;
//    }

    std::shared_ptr<SharedObjects> ptr = SharedObjects::getPointer();
    std::shared_ptr<NotificationWindow> window = ptr->windowGet<NotificationWindow>(
        NotificationWindow::WINDOW_ID
    );

    QJsonObject result = ptr->getUserState()->sendTask(taskId, answer);

    std::string message;
    if (result["code"] == 0) {
        message = "Ответ верный";
    } else {
        message = "Ответ неверный";
    }

    window->updateText(message);
    window->show();

    this->hide();
}
