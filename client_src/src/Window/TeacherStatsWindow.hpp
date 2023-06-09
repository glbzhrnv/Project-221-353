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

private slots:
    void changeSortOrder(uint32_t col);

private:
    Ui::TeacherStatsWindow *ui;

    std::shared_ptr<SharedObjects> ptr;

    uint32_t currentLastRow = 0;

    uint32_t offset = 1; // login
    uint32_t scoreOffset = offset + 5; // число всех задач

    bool sortOrder = false;
};

#endif // TEACHERSTATSWINDOW_H
