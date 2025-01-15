/*
* Project    : BinanceTradeCpp
* Filename   : DBLoginVw.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-28 10:47 (UTC+3)
* Updated    : 2024-10-28 10:47 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/


#include "DBLoginVw.hpp"
#include <QDialog>

DBLoginVw::DBLoginVw(QWidget *parent)
    : QDialog(parent)
    , ui( new Ui::DBLoginDialog )
{
    ui->setupUi(this);
}

DBLoginVw::~DBLoginVw(){
    delete ui;
}

int DBLoginVw::exec_view(){
    return this->exec();
    // show_window(true);
    // QEventLoop loop;
    // QObject::connect(this->get_login_button(), &QPushButton::clicked, &loop, [&](std::function<void()> callback){});
    // loop.exec();

}


void DBLoginVw::connectLoginButton(std::function<void()> callback) {

    connect(ui->btn_login , &QPushButton::clicked, this,
        [callback](){ callback(); }
    );
}

void DBLoginVw::connectTestButton(std::function<void()> callback) {
    connect(ui->btn_test_connection, &QPushButton::clicked, this, 
    [callback](){ callback();}
    );
}


void DBLoginVw::show_database_test_result(bool result, std::exception e){

    if(result){
        ui->btn_test_connection->setIcon(QIcon(":/icons/check_mark"));
        ui->label_connection_test_result->setText( "connected to database successfully" );

    }else{
        ui->btn_test_connection->setIcon(QIcon(":/icons/cross_mark"));
        ui->label_connection_test_result->setText( QString("failure connection to database:%1").arg( e.what() ) );
    }
}

// void DBLoginVw::on_btn_login_clicked()
// {

// }

