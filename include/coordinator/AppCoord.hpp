
#pragma once

#include <QObject>

class Config;
class DBManagerCoord;
class UserLoginCoord;
class DBLoginCoord;
class MainCoord;
class CreateModelCoord;
class DBManager;

class AppCoord : public QObject {

    Q_OBJECT

public:
    AppCoord(QObject *parent=nullptr);
    ~AppCoord();
    void startApplication();



private slots:


private:


    Config              *config;
    DBManagerCoord      *dBManagerCoord;
    // UserLoginCoord      *userLoginCoord;
    MainCoord           *mainCoord;
    DBLoginCoord        *dBLoginCoord;

    DBManager           *dBManager;



};
