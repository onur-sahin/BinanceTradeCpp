/*
* Project    : BinanceTradeCpp
* Filename   : UserLoginMdl.cpp
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

#include "UserLoginMdl.hpp"
#include "utils.hpp"
#include "CryptoManager.hpp"
#include "HashManager.hpp"
#include "Config.hpp"
#include <DBManager.hpp>
#include <QDebug>
#include <QMap>
#include <filesystem>

UserLoginMdl::UserLoginMdl(QObject *parent)
    : QObject(parent)
    , dBManager( new DBManager() )
{
}

UserLoginMdl::~UserLoginMdl(){
}

UserLoginMdl &UserLoginMdl::getInstance(){
    static UserLoginMdl instance;
    return instance;
}

void UserLoginMdl::set_user(const QString user){
        m_user = user;
}

void UserLoginMdl::set_password(const QString password){
        m_password = password;
}

void UserLoginMdl::set_hashedPassword(const QString hashedPassword){
    m_hashedPassword = hashedPassword;
}

void UserLoginMdl::set_rememberPassword(const Qt::CheckState rememberPassword){
    m_rememberPassword = rememberPassword;
}


void UserLoginMdl::set_userList(const QMap<QString, QString> &&userList){
    m_userList = std::move(userList);
    emit userListChanged();
    qDebug()<<"test:"<< "emit userListChanged() in UserLoginMdl";
}

const QMap<QString, QString> &UserLoginMdl::get_user_list() const {
    return m_userList;
}

void UserLoginMdl::update_userList(){

    QMap<QString, QString> userList;

    try
    {
        filesystem::path path =  utils::get_current_working_dir().parent_path() / "share" / "users.json";
        userList =  utils::read_QMap_from_json_file( QString::fromStdString( path.string() ) ) ; 

    }
    catch(const std::exception &e)
    {
        qDebug() << "failure in UserLoginMdl::update_userList() error: " << e.what();
        return;
    }

    set_userList( std::move(userList) );

};

void UserLoginMdl::create_database_for_new_user(){
    // DBManager &databaseManager = DBManager::get_connection();
}

void UserLoginMdl::save_user_info_to_file(){

}



bool UserLoginMdl::user_name_in_use(){

    Config *config = Config::get_instance();

    QMap<QString, QString> user_list = utils::read_QMap_from_json_file( config->get_user_json_path().string() );

    if( user_list.contains( get_user() )){
        return true;
    }

    return false;
    
}



void UserLoginMdl::create_new_user(){

    Config      *config      = Config::get_instance();
    HashManager &hashManager = HashManager::get_instance();

    QString password = QString("");

    if ( user_name_in_use() ){
        throw std::runtime_error("User name already in use");
    }

    if ( get_rememberPassword() == Qt::Checked ){
        password = hashManager.hash( get_password() );

    }

    utils::append_QMap_to_json_file(
        QMap<QString, QString>{ {get_user(), password} },
        QString::fromStdString( config->get_user_json_path().string() )
    );




}
