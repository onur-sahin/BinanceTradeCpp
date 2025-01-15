/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginMdl.hpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 02:05 (UTC+3)
* Updated    : 2024-10-23 02:05 (UTC+3)
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

#include <QCheckBox>
#include <QMap>
#include <QObject>
#include <QString>

class DBManager;

class UserLoginMdl: public QObject {
    Q_OBJECT
public:
    
    UserLoginMdl(QObject *parent = nullptr);
    ~UserLoginMdl();

    static UserLoginMdl &getInstance();


    void set_user            (const QString user);
    void set_password        (const QString password);
    void set_hashedPassword  (const QString hashedPassword);
    void set_rememberPassword(const Qt::CheckState rememberPassword);
    void set_userList        (const QMap<QString, QString> &&userList);

    const QString        &get_user            () const { return m_user; }
    const QString        &get_password        () const { return m_password; }
    const QString        &get_hashedPassword  () const { return m_hashedPassword; }
    const Qt::CheckState &get_rememberPassword() const { return m_rememberPassword; }

    const QMap<QString, QString> &get_user_list() const;

    void update_userList             ();
    void create_database_for_new_user();
    void save_user_info_to_file      ();

    bool user_name_in_use();
    void create_new_user ();

signals:
    void userChanged();
    void passwordChanged();
    void userListChanged();

private:

    UserLoginMdl(const UserLoginMdl &) = delete;
    UserLoginMdl &operator=(const UserLoginMdl &) = delete;

    QString                m_user;
    QString                m_password;
    QString                m_hashedPassword;
    Qt::CheckState         m_rememberPassword;
    QMap<QString, QString> m_userList;

    DBManager *dBManager;

};