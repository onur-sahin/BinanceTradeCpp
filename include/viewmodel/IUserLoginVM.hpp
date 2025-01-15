/*
* Project    : BinanceTradeCpp
* Filename   : IUserLoginVM.hpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 10:17 (UTC+3)
* Updated    : 2024-10-23 10:17 (UTC+3)
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

class QString;

class IUserLoginVM {

public:
     ~IUserLoginVM () = default;

    virtual const QString                &get_user            () const = 0;
    virtual const QString                &get_password        () const = 0;
    virtual const QString                &get_hashedPassword  () const = 0;
    virtual const Qt::CheckState         &get_rememberPassword() const = 0;
    virtual const QMap<QString, QString> &get_userList        () const = 0;

    virtual void set_user            (const QString &user)                     = 0;
    virtual void set_password        (const QString &password)                 = 0;
    virtual void set_hashedPassword  (const QString &hashedPassword)           = 0;
    virtual void set_rememberPassword(const Qt::CheckState rememberPassword)   = 0;
    virtual void set_userList        (const QMap<QString, QString> &&userList) = 0;

 
    virtual void update_userList             () = 0;
    virtual void create_new_user             () = 0;

};