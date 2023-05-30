#ifndef STUDENTTASKWINDOW_HPP
#define STUDENTTASKWINDOW_HPP

#include <QWidget>
#include <QJsonObject>

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
};

#endif // STUDENTTASKWINDOW_HPP
