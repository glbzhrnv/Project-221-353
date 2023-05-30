#include "Window/TeacherStatsWindow.hpp"
#include "ui_TeacherStatsWindow.h"

TeacherStatsWindow::TeacherStatsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeacherStatsWindow)
{
    ui->setupUi(this);
}

TeacherStatsWindow::~TeacherStatsWindow()
{
    delete ui;
}

void TeacherStatsWindow::updateStats(QJsonObject data)
{

}
