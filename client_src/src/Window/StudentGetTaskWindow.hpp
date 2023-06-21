#ifndef STUDENTGETTASKWINDOW_HPP
#define STUDENTGETTASKWINDOW_HPP

#include <memory>
#include <QWidget>
#include "Enum/FSMType.hpp"
#include "Window/StudentTaskWindow.hpp"
#include "SharedObjects.hpp"

namespace Ui
{
    class StudentGetTaskWindow;
}

/**
 * @brief Окно получения задания
 */
class StudentGetTaskWindow: public QWidget
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 2;

    StudentGetTaskWindow(QWidget *parent = nullptr);

    ~StudentGetTaskWindow();

private slots:
    void on_GetSolveMealy_clicked();

    void on_GetSuperMealy_clicked();

    void on_GetMealyToMoore_clicked();

    void on_GetSuperMoore_clicked();

    void on_GetSolveMoore_clicked();

protected:
    /**
     * @brief Обновляет статистику выполненных, пользователем, заданий
     */
    void updateStat();

    /**
     * @brief Запрашивает с сервера новое задание
     * @param type - Тип задания
     * @param msg - Дополнительный текст задания
     */
    void setupTask(ENUM::FSMType type, std::string msg);

private:
    Ui::StudentGetTaskWindow *ui;

    std::shared_ptr<SharedObjects> ptr;

    StudentTaskWindow *taskWindow;
};

#endif // STUDENTGETTASKWINDOW_HPP
