#ifndef STUDENTGETTASKWINDOW_HPP
#define STUDENTGETTASKWINDOW_HPP

#include <memory>
#include <QWidget>
#include "SharedObjects.hpp"

namespace Ui
{
    class StudentGetTaskWindow;
}

class StudentGetTaskWindow: public QWidget
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 2;

    StudentGetTaskWindow(QWidget *parent = nullptr);

    ~StudentGetTaskWindow();

private slots:
    void on_GetMealyMachine_clicked();

    void on_GetMooreMachine_clicked();

private:
    Ui::StudentGetTaskWindow *ui;

    std::shared_ptr<SharedObjects> ptr;
};

#endif // STUDENTGETTASKWINDOW_HPP
