/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginCoord.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 01:45 (UTC+3)
* Updated    : 2024-10-23 01:45 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/


#include "UserLoginCoord.hpp"
#include "UserLoginVM.hpp"
#include "UserLoginVw.hpp"
#include <QMessageBox>

UserLoginCoord::UserLoginCoord(QObject *parent)
    :QObject(parent),
    m_view     ( new UserLoginVw() ),
    m_viewmodel( new UserLoginVM() )
{
    connectViewmodelToView();



}

UserLoginCoord::~UserLoginCoord(){
}

void UserLoginCoord::show_window(bool status){
    m_view->show_window(status);
}

int UserLoginCoord::exec_view(){
    return m_view->exec();
}

void UserLoginCoord::create_new_user(){
    m_viewmodel->create_new_user();
}

void UserLoginCoord::update_model(){
    m_viewmodel->set_user             ( m_view->get_user()     );
    m_viewmodel->set_password         ( m_view->get_password() );
    m_viewmodel->set_rememberPassword ( m_view->get_rememberPassword() );
}


void UserLoginCoord::connectViewmodelToView(){

    m_view->connectCreateUserButton(

        [this](){
            update_model();
            emit newUserCreationRequested();  //this signal will be catch by AppCoord
        }
    );

    connect(m_viewmodel, &UserLoginVM::userChanged, [this](){

        m_view->set_user( m_viewmodel->get_user() );
    });

    connect(m_viewmodel, &UserLoginVM::passwordChanged, [this](){
        m_view->set_password( m_viewmodel->get_password() );
    });

    connect(m_viewmodel, &UserLoginVM::rememberPasswordChanged, [this](){
        m_view->set_rememberPassword(m_viewmodel->get_rememberPassword() );
    });

} //connectViewmodelToView