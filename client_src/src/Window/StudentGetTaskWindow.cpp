#include <memory>
#include <sstream>
#include <QJsonObject>
#include <QMessageBox>
#include "Enum/FSMType.hpp"
#include "Enum/StatType.hpp"
#include "Model/UserStateModel.hpp"
#include "Window/StudentGetTaskWindow.hpp"
#include "qjsonobject.h"
#include "ui_StudentGetTaskWindow.h"
#include "SharedObjects.hpp"

StudentGetTaskWindow::StudentGetTaskWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudentGetTaskWindow)
{
    ui->setupUi(this);

    ptr = SharedObjects::getPointer();

    taskWindow = new StudentTaskWindow;

    connect(
        ptr->getUserState(), &UserStateModel::taskComplete,
        this, [=]() { this->show(); }
    );

//    connect(
//        ptr->getUserState(), &UserStateModel::taskComplete,
//        this, [=]() { updateStat(); }
//    );

    updateStat();
}

StudentGetTaskWindow::~StudentGetTaskWindow()
{
    delete ui;
}

void StudentGetTaskWindow::on_GetSolveMealy_clicked()
{
    setupTask(ENUM::MEALY_SOLVE, "Решите автомат Мили");
}

void StudentGetTaskWindow::on_GetSuperMealy_clicked()
{
    setupTask(ENUM::MEALY_SUPER, "Найдите суперпозицию двух автоматов Мили");
}

void StudentGetTaskWindow::on_GetMealyToMoore_clicked()
{
    setupTask(ENUM::MEALY_TO_MOORE, "Преобразуйте данный автомат Мили в автомат Мура");
}

void StudentGetTaskWindow::on_GetSuperMoore_clicked()
{
    setupTask(ENUM::MOORE_SUPER, "Найдите суперпозицию двух автоматов Мура");
}

void StudentGetTaskWindow::on_GetSolveMoore_clicked()
{
    setupTask(ENUM::MOORE_SOLVE, "Решите автомат Мура");
}

void StudentGetTaskWindow::updateStat()
{
    QJsonObject response = ptr->getUserState()->getStat(ENUM::USER);

    std::string text;
    if (response["code"].toInt(-1) != 0) {
        text = "Unable to retrive data";
    } else {
        QJsonObject data = response["response"].toObject();
        std::stringstream ss;
        ss << "Results:\n"
           << "\tCorrect: " << data["correct"].toInt(0) << "\n"
           << "\tIncorrect: " << data["incorrect"].toInt(0) << "\n";
        text = ss.str();
    }

    ui->Stats->setText(text.c_str());
}

void StudentGetTaskWindow::setupTask(ENUM::FSMType type, std::string msg)
{
    QJsonObject data = ptr->getUserState()->getTask(type);
    if (data["code"].toInt(-1) != 0) {
        QMessageBox::information(this, "Task", "Unable to get task");

        return;
    }

    taskWindow->setTask(data["response"].toObject(), msg);
    taskWindow->show();

    this->hide();
}
