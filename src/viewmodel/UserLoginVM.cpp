/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginVM.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-23 01:43 (UTC+3)
* Updated    : 2024-10-23 01:43 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#include "UserLoginMdl.hpp"
#include "UserLoginVM.hpp"
#include <QDebug>
#include <QString>
#include <QMessageBox>

UserLoginVM::UserLoginVM(QObject *parent)
    :QObject(parent),
    m_model( new UserLoginMdl() )
{
    connect(m_model, &UserLoginMdl::userChanged,     this, &UserLoginVM::userChanged );
    connect(m_model, &UserLoginMdl::passwordChanged, this, &UserLoginVM::passwordChanged);
}

UserLoginVM::~UserLoginVM(){
    delete m_model;
}

void UserLoginVM::set_user(const QString &user){
    if (m_model->get_user() != user){
        m_model->set_user(user);
        emit userChanged();
        qDebug()<<"test:"<< "emit userChanged() in UserLoginVM";
    }
}

void UserLoginVM::set_password(const QString &password){
    if ( m_model->get_password() != password ){
        m_model->set_password(password);
        emit passwordChanged();
        qDebug()<<"test:"<<"emit passwordChanged() in UserLoginVM";
    }
}

void UserLoginVM::set_hashedPassword(const QString &hashedPassword){
    if ( m_model->get_hashedPassword() != hashedPassword ){
        m_model->set_hashedPassword( hashedPassword );
        emit hashedPasswordChanged();
        qDebug()<<"test:"<<"emit hashedPasswordChanged() in UserLoginVM";
    }
}

void UserLoginVM::set_rememberPassword(const Qt::CheckState rememberPassword){
    if ( m_model->get_rememberPassword() != rememberPassword ){
        m_model->set_rememberPassword( rememberPassword );
        emit rememberPasswordChanged();
        qDebug()<<"test:"<<"emit rememberPasswordChange() in UserLoginVM";
    }
}

void UserLoginVM::set_userList(const QMap<QString, QString> &&userList){
    if (m_model->get_user_list() != userList){
        m_model->set_userList( std::move(userList) );
        emit userListChanged();
        qDebug()<<"test:"<<"emit userListChanged() in UserLoginVM";
    }
}

void UserLoginVM::update_userList(){
    m_model->update_userList();
}

void UserLoginVM::create_new_user(){
    // updated model in userLoginCoord file
    if ( m_model->get_user() == "" or m_model->get_password() == "")
    {
        throw std::invalid_argument("username and password couldn't be empty!");


    }


    m_model->create_new_user();

    
    // m_model->create_database_for_new_user();

    // m_model->save_user_info_to_file();
    
}
