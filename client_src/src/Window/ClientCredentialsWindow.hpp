#ifndef CLIENTCREDENTIALSWINDOW_H
#define CLIENTCREDENTIALSWINDOW_H

#include <QDialog>
#include <QWidget>

namespace Ui
{
    class ClientCredentialsWindow;
};

class ClientCredentialsWindow: public QDialog
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 0;

    ClientCredentialsWindow(QWidget *parent = nullptr);
    ~ClientCredentialsWindow();

private slots:
    void on_Login_clicked();

    void on_Register_clicked();

private:
    Ui::ClientCredentialsWindow *ui;
};

#endif // CLIENTCREDENTIALSWINDOW_H
