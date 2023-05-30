#ifndef TEACHERSTATSWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QJsonObject>

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
};

#endif // TEACHERSTATSWINDOW_H
