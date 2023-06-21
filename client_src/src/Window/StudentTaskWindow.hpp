#ifndef STUDENTTASKWINDOW_HPP
#define STUDENTTASKWINDOW_HPP

#include <string>
#include <memory>
#include <QWidget>
#include <QJsonObject>
#include "SharedObjects.hpp"

namespace Ui
{
    class StudentTaskWindow;
}

/**
 * @brief Окно с заданием
 */
class StudentTaskWindow: public QWidget
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 3;

    StudentTaskWindow(QWidget *parent = nullptr);
    ~StudentTaskWindow();

    /**
     * @brief Устанавливает содержимое задания
     * @param params - Данные задания
     * @param msg - Дополнительный текст
     */
    void setTask(QJsonObject params, std::string msg);

private slots:
    void on_Send_clicked();

private:
    int32_t taskId;

    Ui::StudentTaskWindow *ui;

    std::shared_ptr<SharedObjects> ptr;
};

#endif // STUDENTTASKWINDOW_HPP
