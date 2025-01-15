/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginVw.hpp
* Description: -
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-22 09:16 (UTC+3)
* Updated    : 2024-10-22 09:16 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#pragma once

#include <QDialog>

#include "IUserLoginView.hpp"
#include "ui_UserLoginWindow.h"
#include <QCheckBox>
#include <QObject>

// namespace Ui {          //forward declaration #include "ui_UserLoginWindow.h" kullanıldığı zaman gereksizdir
// class UserLoginWindow;
// }

class QLineEdit;

class UserLoginVw: public QDialog, public IUserLoginView{
    Q_OBJECT

public:
    UserLoginVw(QWidget *parent = nullptr);
    ~UserLoginVw();
    void show_window(bool status);
    void connectCreateUserButton(std::function<void()> callback);

    const QString get_user() const {
        return ui->le_user->text();
    }

    const QString get_password() const {
        return ui->le_password->text();
    }

    const Qt::CheckState get_rememberPassword() const {
        return ui->cb_remember->checkState();
    }

    void set_user(const QString &user){
        ui->le_user->setText(user);
    }

    void set_password(const QString &password){
        ui->le_password->setText(password);
    }
    
    void set_rememberPassword(const Qt::CheckState rememberPassword){
        ui->cb_remember->setCheckState(rememberPassword);
    }

private:
    Ui::UserLoginWindow *ui;

};
