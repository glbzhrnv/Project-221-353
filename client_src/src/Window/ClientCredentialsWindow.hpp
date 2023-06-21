#ifndef CLIENTCREDENTIALSWINDOW_H
#define CLIENTCREDENTIALSWINDOW_H

#include <memory>
#include <QDialog>
#include <QWidget>
#include <QJsonObject>
#include "SharedObjects.hpp"

namespace Ui
{
    class ClientCredentialsWindow;
};

/**
 * @brief Окно авторизации
 */
class ClientCredentialsWindow: public QDialog
{
    Q_OBJECT

public:
    static const uint32_t WINDOW_ID = 0;

    ClientCredentialsWindow(QWidget *parent = nullptr);
    ~ClientCredentialsWindow();

protected:
    /**
     * @brief Производит переход к следующему окну
     * @param response Ответ сервера
     */
    void setupNextWindow(QJsonObject response);

private slots:
    void on_Login_clicked();

    void on_Register_clicked();

private:
    std::shared_ptr<SharedObjects> ptr;
    Ui::ClientCredentialsWindow *ui;
};

#endif // CLIENTCREDENTIALSWINDOW_H
