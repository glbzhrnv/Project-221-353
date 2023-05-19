#ifndef TEACHERSTATSWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

namespace Ui
{
    class TeacherStatsWindow;
}

class TeacherStatsWindow: public QMainWindow
{
    Q_OBJECT

public:
    TeacherStatsWindow(QWidget *parent = nullptr);
    ~TeacherStatsWindow();

private:
    Ui::TeacherStatsWindow *ui;
};

#endif // TEACHERSTATSWINDOW_H
