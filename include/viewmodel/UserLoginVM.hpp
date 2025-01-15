
/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginVM.hpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 01:51 (UTC+3)
* Updated    : 2024-10-23 01:51 (UTC+3)
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

#include "IUserLoginVM.hpp"
#include <QObject>

class QString;
#include  <UserLoginMdl.hpp>

class UserLoginVM : public QObject, public IUserLoginVM {
    Q_OBJECT
public:
    UserLoginVM(QObject * parent = nullptr);

    ~UserLoginVM();
    
    void set_user             (const QString &user) override;
    void set_password         (const QString &password) override;
    void set_hashedPassword   (const QString &hashedPassword) override;
    void set_rememberPassword (const Qt::CheckState rememberPassword) override;
    void set_userList         (const QMap<QString, QString> &&userList) override;

    const QString        &get_user()             const override { return m_model->get_user(); }
    const QString        &get_password()         const override { return m_model->get_password(); }
    const QString        &get_hashedPassword()   const override { return m_model->get_hashedPassword(); }
    const Qt::CheckState &get_rememberPassword() const override { return m_model->get_rememberPassword(); }
    
    const QMap<QString, QString> &get_userList() const override {return m_model->get_user_list(); }

    void create_new_user() override;
    
    void update_userList() override;

signals:
    void userChanged();
    void passwordChanged();
    void hashedPasswordChanged();
    void rememberPasswordChanged();
    void userListChanged();
    void showDatabaseLoginWindow();

private:
    UserLoginMdl *m_model;


};


