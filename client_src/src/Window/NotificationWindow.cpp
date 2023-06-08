#include "Window/NotificationWindow.hpp"
#include "ui_NotificationWindow.h"

NotificationWindow::NotificationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NotificationWindow)
{
    ui->setupUi(this);
}

NotificationWindow::~NotificationWindow()
{
    delete ui;
}

void NotificationWindow::on_Confirm_clicked()
{
    this->hide();

    emit ConfirmClicked();
}

void NotificationWindow::updateText(std::string text)
{
    ui->Text->setText(text.c_str());
}
