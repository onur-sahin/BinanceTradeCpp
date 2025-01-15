#pragma once

#include <QCheckBox>
#include <QString>


class DBManager;

class DBLoginMdl{

public:
    DBLoginMdl();

    const QString &database() const ;
    void           set_database(const QString &database);

    const QString &user() const;
    void           set_user(const QString &user);

    const QString &host() const;
    void           set_host(const QString &host);

    const QString &port() const;
    void           set_port(const QString &port);

    const QString &password() const;
    void           set_password(const QString &password);

    const Qt::CheckState &rememberPassword() const;
    void                  set_rememberPassword(const Qt::CheckState &rememberPassword);

    void test_database_connection();
    void save_database_connection();

private:

    QString        m_database;
    QString        m_user;
    QString        m_host;
    QString        m_port;
    QString        m_password;
    Qt::CheckState m_rememberPassword;


    DBManager      *dBManager;

};

