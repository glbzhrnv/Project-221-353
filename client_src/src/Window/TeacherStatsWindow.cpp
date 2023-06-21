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

    QHeaderView *header = ui->TasksTable->horizontalHeader();

    connect(
        header, &QHeaderView::sectionClicked,
        this, &TeacherStatsWindow::changeSortOrder
    );

    updateStats(response);

    header->setSortIndicator(scoreOffset, Qt::SortOrder::AscendingOrder);
}

TeacherStatsWindow::~TeacherStatsWindow()
{
    delete ui;
}

void TeacherStatsWindow::changeSortOrder(uint32_t col)
{
    if (col != scoreOffset) {
        return;
    }

    ui->TasksTable->sortItems(
        col,
        (sortOrder
            ? Qt::SortOrder::AscendingOrder
            : Qt::SortOrder::DescendingOrder
        )
    );

    sortOrder = !sortOrder;
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

        int score = 0;
        for (auto res : rowObj["results"].toObject()) {
            QJsonObject resObj = res.toObject();

            qDebug() << resObj;
            if (resObj["is_correct"].toBool()) {
                currentRes[resObj["type"].toInt(-1)] = 1;
               score++;
            } else {
                currentRes[resObj["type"].toInt(-1)] = 0;
            }
        }

        tbl->insertRow(currentLastRow);
        QTableWidgetItem *loginItem = new QTableWidgetItem(
            rowObj["login"].toString()
        );
        tbl->setItem(currentLastRow, 0, loginItem);


        for (uint32_t i = 0; i < 5; i++) {
            QTableWidgetItem *msgItem = new QTableWidgetItem(
                possibleMsg[currentRes[i]].c_str()
            );

            tbl->setItem(currentLastRow, i + offset, msgItem);
        }

        tbl->setItem(
            currentLastRow,
            scoreOffset,
            new QTableWidgetItem(
                QString::number(score)
            )
        );

        currentLastRow++;
    }

    changeSortOrder(scoreOffset);
}
