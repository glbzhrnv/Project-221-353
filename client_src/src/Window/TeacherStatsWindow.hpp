#ifndef TEACHERSTATSWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QWidget>
#include <QJsonObject>
#include "SharedObjects.hpp"

namespace Ui
{
    class TeacherStatsWindow;
}

class TeacherStatsWindow: public QMainWindow
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 4;

    TeacherStatsWindow(QWidget *parent = nullptr);

    ~TeacherStatsWindow();

    void updateStats(QJsonObject data);

private:
    Ui::TeacherStatsWindow *ui;

    std::shared_ptr<SharedObjects> ptr;

    uint32_t currentLastRow = 0;
};

#endif // TEACHERSTATSWINDOW_H
