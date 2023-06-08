#include <string>
#include <unordered_map>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "Window/TeacherStatsWindow.hpp"
#include "ui_TeacherStatsWindow.h"

TeacherStatsWindow::TeacherStatsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeacherStatsWindow)
{
    ui->setupUi(this);
    ptr = SharedObjects::getPointer();

    QJsonObject response = ptr->getUserState()->getStat(ENUM::TEACHER);

    updateStats(response);
}

TeacherStatsWindow::~TeacherStatsWindow()
{
    delete ui;
}

void TeacherStatsWindow::updateStats(QJsonObject data)
{
    if (data["code"].toInt(-1) != 0) {
        QMessageBox::critical(this, "Statistics", "Unable to retrive stats");

        return;
    }

    std::unordered_map<int32_t, std::string> possibleMsg = {
        {-1, "Не начато"},
        {0, "Не верно"},
        {1, "Верно"},
    };

    QTableWidget* tbl = ui->TasksTable;
    for (auto row : data["response"].toObject()) {
        QJsonObject rowObj  = row.toObject();

        std::unordered_map<int32_t, int32_t> currentRes = {
            {-1, -1},
            {ENUM::MEALY_SOLVE, -1},
            {ENUM::MEALY_SUPER, -1},
            {ENUM::MEALY_TO_MOORE, -1},
            {ENUM::MOORE_SOLVE, -1},
            {ENUM::MOORE_SUPER, -1},
        };

        for (auto res : rowObj["results"].toObject()) {
            QJsonObject resObj = res.toObject();

            qDebug() << resObj;
            currentRes[resObj["type"].toInt(-1)] = (int32_t)resObj["is_correct"].toBool();
        }

        tbl->insertRow(currentLastRow);
        QTableWidgetItem *loginItem = new QTableWidgetItem(
            rowObj["login"].toString()
        );
        tbl->setItem(currentLastRow, 0, loginItem);

        uint32_t offset = 1;
        for (uint32_t i = 0; i < 5; i++) {
            QTableWidgetItem *msgItem = new QTableWidgetItem(
                possibleMsg[currentRes[i]].c_str()
            );

            tbl->setItem(currentLastRow, i + offset, msgItem);
        }
        currentLastRow++;
    }



}
