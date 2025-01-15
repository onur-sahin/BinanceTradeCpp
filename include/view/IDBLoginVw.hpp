#pragma once

#include <QCheckBox>
#include <QPushButton>

class DatabaseLoginWindow;
class QString;
class QWidget;


class IDBLoginVw{

public:

    virtual ~IDBLoginVw() = default;
    
    virtual const QString                    get_database()            const = 0;
    virtual const QString                    get_user()                const = 0;
    virtual const QString                    get_host()                const = 0;
    virtual const QString                    get_port()                const = 0;
    virtual const QString                    get_password()            const = 0;
    virtual       void                       set_enabled(bool enabled) const = 0;
    virtual const Qt::CheckState             get_rememberPassword()    const = 0;
    // virtual       QPushButton              &*get_login_button()        const = 0;


    virtual void  set_database (const QString &database)          = 0;
    virtual void  set_user     (const QString &user)              = 0;
    virtual void  set_host     (const QString &host)              = 0;
    virtual void  set_port     (const QString &port)              = 0;
    virtual void  set_password (const QString &password)          = 0;
    virtual void  set_remember (const Qt::CheckState &remember)   = 0;

    virtual int   exec_view() = 0;
    virtual void  set_connection_test_result(const QString &test_result) = 0;

    virtual void  connectLoginButton(std::function<void()> callback) = 0;
    virtual void  connectTestButton (std::function<void()> callback) = 0;
    virtual void  show_window(bool status) const = 0;

};