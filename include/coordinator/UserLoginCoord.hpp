
/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginCoord.hpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 01:58 (UTC+3)
* Updated    : 2024-10-23 01:58 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#include <QObject>

class UserLoginVw;
class UserLoginVM;

class UserLoginCoord : public QObject{
    Q_OBJECT

public:

    UserLoginCoord(QObject *parent = nullptr);
    ~UserLoginCoord();

    void show_window(bool status=true);
    int  exec_view();
    void update_model();
    void create_new_user();
    void connectViewmodelToView();

signals:
    void newUserCreationRequested();
    void showDBLoginWindowRequested();

private:

    UserLoginVw *m_view;
    UserLoginVM *m_viewmodel;

};