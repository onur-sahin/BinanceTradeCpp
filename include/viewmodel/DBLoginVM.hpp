#pragma once

#include <QDebug>
#include <QObject>

#include "DBLoginMdl.hpp"
#include "IDBLoginVM.hpp"

class QString;

class DBLoginVM : public IDBLoginVM
{
    Q_OBJECT

public:
    explicit DBLoginVM       ( QObject *parent = nullptr);
    void     show_window     (bool status);
    void     test_connection ();
    void     save_connection ();
    void     attempt_login   ();

public:
    std::function<void()>  updateViewmodelFromView;

private:
    DBLoginMdl            *m_model;


// GETTER AND SETTERS
public:
    const QString        &get_database()         const { return m_model->database(); }
    const QString        &get_user()             const { return m_model->user(); }
    const QString        &get_host()             const { return m_model->host(); }
    const QString        &get_port()             const { return m_model->port(); }
    const QString        &get_password()         const { return m_model->password(); }
    const Qt::CheckState &get_rememberPassword() const { return m_model->rememberPassword(); }


    void set_database(const QString &database){

        if(m_model->database() != database){
            m_model->set_database( database );
            emit databaseChanged();
            qDebug()<<"test:" << "emit databaseChanged();" ;
        }
    }

    void set_user(const QString &user){

        if(m_model->user() != user){
            m_model->set_user(user);
            emit userChanged();
            qDebug()<<"test:" << "emit userChanged();" ;
        }
    }

    void set_host(const QString &host){

        if(m_model->host() != host){
            m_model->set_host(host);
            emit hostChanged();
            qDebug()<<"test:" << "emit hostChanged();" ;
        }
    }

    void set_port(const QString &port){

        if(m_model->port() != port){
            m_model->set_port(port);
            emit portChanged();
            qDebug()<<"test:" << "emit portChanged();" ;
        }
    }

    void set_password(const QString &password){

        if(m_model->password() != password){
            m_model->set_password(password);
            emit passwordChanged();
            qDebug()<<"test:" << "emit passwordChanged();";
        }
    }

    void set_rememberPassword(const Qt::CheckState &rememberPassword) {

        if(m_model->rememberPassword() != rememberPassword){
            m_model->set_rememberPassword(rememberPassword);
            emit rememberPasswordChanged();
            qDebug()<<"test:" << "emit rememberPasswordChanged();" ;
        }
    }



    
};

