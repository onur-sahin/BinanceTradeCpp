
#pragma once

#include <QCheckBox>
class QLineEdit;

class IUserLoginView {

public:
    virtual                      ~IUserLoginView()             = default;
    virtual const QString         get_user()             const = 0;
    virtual const QString         get_password()         const = 0;
    virtual const Qt::CheckState  get_rememberPassword() const = 0;

    virtual void set_user            (const QString &user    )                = 0;
    virtual void set_password        (const QString &password)                = 0;
    virtual void set_rememberPassword(const Qt::CheckState rememeberPassword) = 0;

    virtual void show_window            (bool status                   ) = 0;
    virtual void connectCreateUserButton(std::function<void()> callback) = 0;


};