/*
 * Filename   : LoginModel.cpp
 * Description: This file is intentionally left empty.
 * Reason     : No implementation is required for this class at this time.
 */

#include "DBLoginMdl.hpp"
#include "DBManager.hpp"
#include "utils.hpp"

#include <Config.hpp>
#include <QMap>
#include <QString>
#include <filesystem>

DBLoginMdl::DBLoginMdl(){

    dBManager = DBManager::getInstance();

}

const QString &DBLoginMdl::database() const {return m_database;}
void DBLoginMdl::set_database(const QString &database) { m_database=database;}

const QString &DBLoginMdl::user() const {return m_user;}
void DBLoginMdl::set_user(const QString &user){m_user = user;}

const QString &DBLoginMdl::host() const {return m_host;}
void DBLoginMdl::set_host(const QString &host){m_host = host;}

const QString &DBLoginMdl::port() const {return m_port;}
void DBLoginMdl::set_port(const QString &port){ m_port = port; }

const QString &DBLoginMdl::password() const {return m_password;}
void DBLoginMdl::set_password(const QString &password){
    m_password = password;
}

const Qt::CheckState &DBLoginMdl::rememberPassword() const { return m_rememberPassword; }
void DBLoginMdl::set_rememberPassword(const Qt::CheckState &rememberPassword){
    m_rememberPassword = rememberPassword;
}


void DBLoginMdl::test_database_connection(){

    dBManager->test_database_connection( database(), user(), host(), port(), password() );
}

void DBLoginMdl::save_database_connection(){
    dBManager->save_database_connection_settings(database(), user(), host(), port(), password());
}

