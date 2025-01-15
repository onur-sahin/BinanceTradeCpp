#pragma once

#include <QObject>
#include <QString>

class IDBLoginVM: public QObject {
    Q_OBJECT

public:
    explicit IDBLoginVM(QObject *parent=nullptr):QObject(parent){}
    
    virtual ~IDBLoginVM() = default;

    virtual const QString        &get_database() const = 0;
    virtual const QString        &get_user()     const = 0;
    virtual const QString        &get_host()     const = 0;
    virtual const QString        &get_port()     const = 0;
    virtual const QString        &get_password() const = 0;
    virtual const Qt::CheckState &get_rememberPassword() const = 0;
    
    virtual void    set_database(const QString &database       ) = 0;
    virtual void    set_user    (const QString &user           ) = 0;
    virtual void    set_host    (const QString &host           ) = 0;
    virtual void    set_port    (const QString &port           ) = 0;
    virtual void    set_password(const QString &password       ) = 0;
    virtual void    set_rememberPassword(const Qt::CheckState &remember) = 0;

    virtual void    show_window(bool status) = 0;
    virtual void    attempt_login() = 0;


signals:
    void databaseChanged         ();
    void userChanged             ();
    void hostChanged             ();
    void portChanged             ();
    void passwordChanged         ();
    void rememberPasswordChanged ();

    void showWindowRequested       (bool status);
    void connection_test_result    (bool result, std::exception e );

};


