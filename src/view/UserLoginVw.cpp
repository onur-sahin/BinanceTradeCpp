
/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginVw.cpp
* Description: -
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-22 09:23 (UTC+3)
* Updated    : 2024-10-22 09:23 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#include "utils.hpp"

#include "UserLoginVw.hpp"
#include "ui_UserLoginWindow.h"


UserLoginVw::UserLoginVw(QWidget *parent)
    : QDialog(parent)
    , ui( new Ui::UserLoginWindow )
{   
    ui->setupUi(this);

}

UserLoginVw::~UserLoginVw(){
        delete ui;
}

void UserLoginVw::show_window(bool status){
    if (status == true){
        this->show();

    } else {
        this->hide();
    }
}   


void UserLoginVw::connectCreateUserButton(std::function<void()> callback){

    connect(ui->btn_create_new_user, &QPushButton::clicked, this,
    [callback](){callback();}
    );

}