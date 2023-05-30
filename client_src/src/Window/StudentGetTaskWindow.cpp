#include <memory>
#include <QJsonObject>
#include "Enum/FSMType.hpp"
#include "Model/UserStateModel.hpp"
#include "Window/StudentGetTaskWindow.hpp"
#include "Window/StudentTaskWindow.hpp"
#include "ui_StudentGetTaskWindow.h"
#include "SharedObjects.hpp"

StudentGetTaskWindow::StudentGetTaskWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentGetTaskWindow)
{
    ui->setupUi(this);

    ptr = SharedObjects::getPointer();
    ptr->windowSet(new StudentTaskWindow, StudentTaskWindow::WINDOW_ID);

    connect(
        ptr->getUserState(), &UserStateModel::taskComplete,
        this, [=]() { this->show(); }
    );
}

StudentGetTaskWindow::~StudentGetTaskWindow()
{
    delete ui;
}

void StudentGetTaskWindow::on_GetMealyMachine_clicked()
{
    std::shared_ptr<StudentTaskWindow> window = ptr->windowGet<StudentTaskWindow>(
        StudentTaskWindow::WINDOW_ID
    );

    window->setTask(
        ptr->getUserState()->getTask(ENUM::MEALY)
    );
    window->show();

    this->hide();
}

void StudentGetTaskWindow::on_GetMooreMachine_clicked()
{
    std::shared_ptr<StudentTaskWindow> window = ptr->windowGet<StudentTaskWindow>(
        StudentTaskWindow::WINDOW_ID
    );

    window->setTask(
        ptr->getUserState()->getTask(ENUM::MOORE)
    );
    window->show();

    this->hide();
}
