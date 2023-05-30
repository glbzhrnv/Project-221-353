#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H

#include <QDialog>
#include <string>

namespace Ui {
    class NotificationWindow;
}

class NotificationWindow : public QDialog
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 1;

    NotificationWindow(QWidget *parent = nullptr);
    ~NotificationWindow();

    void updateText(std::string text);

private:
    Ui::NotificationWindow *ui;

signals:
    void ConfirmClicked();

private slots:
    void on_Confirm_clicked();
};

#endif // NOTIFICATIONWINDOW_H
