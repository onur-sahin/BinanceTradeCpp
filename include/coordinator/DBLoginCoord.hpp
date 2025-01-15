#pragma once

#include <QObject>

class DBLoginVw;
class DBLoginVM;
class QString;

class DBLoginCoord : public QObject{

    Q_OBJECT

public:
    DBLoginCoord( QObject *parent = nullptr );

    bool authenticate(const QString &database);

    void connectViewmodelToView();

    void initiliaze_model_default_values_from_view();

    void show_window(bool status=true);

    int  exec_view();

    void set_enabled(bool enabled);

    void test_connection();
    void save_connection();

signals:
    void connectedToDatabase();

public slots:

private:
    DBLoginVw             *m_view;
    DBLoginVM             *m_viewmodel;
};
