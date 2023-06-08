#ifndef STUDENTTASKWINDOW_HPP
#define STUDENTTASKWINDOW_HPP

#include <memory>
#include <QWidget>
#include <QJsonObject>
#include "SharedObjects.hpp"

namespace Ui
{
    class StudentTaskWindow;
}

class StudentTaskWindow: public QWidget
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 3;

    StudentTaskWindow(QWidget *parent = nullptr);
    ~StudentTaskWindow();

    void setTask(QJsonObject params);

private slots:
    void on_Send_clicked();

private:
    int32_t taskId;

    Ui::StudentTaskWindow *ui;

    std::shared_ptr<SharedObjects> ptr;
};

#endif // STUDENTTASKWINDOW_HPP
