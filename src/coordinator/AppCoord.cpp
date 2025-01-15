/*
* Project    : BinanceTradeCpp
* Filename   : MainCoord.cpp
* Description: manage other coordinators in project
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-16 02:52 (UTC+3)
* Updated    : 2024-10-16 02:52 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/
// TO-DO Silinecek
#include <iostream>

#include "AppCoord.hpp"
#include "Config.hpp"
#include "DBLoginCoord.hpp"
#include "DBManager.hpp"
#include "MainCoord.hpp"
// #include "UserLoginCoord.hpp"

#include "UserLoginVM.hpp"

#include "Log.hpp"
#include "utils.hpp"

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>


AppCoord::AppCoord(QObject *parent)
    : QObject(parent)
{


    config                     = Config::get_instance(); //get_instace head üzerinde bir nesne oluşturup onun adresini döndürüyor
    config->initialize();

    mainCoord                  = new MainCoord();
    dBLoginCoord               = new DBLoginCoord();

    dBManager                  = DBManager::getInstance();



    connect(dBLoginCoord,   &DBLoginCoord::connectedToDatabase,
        [this](){
            cout << "acilmalı" << endl;
            dBLoginCoord->show_window(false);
            mainCoord->show_window(true);
        }
    );




} // AppCoord::AppCoord(QObject *parent)



#include "CryptoManager.hpp"

void AppCoord::startApplication(){

    qInfo() << "\ncurrent working directory: " << utils::get_current_working_dir().string();

    filesystem::path log_file_path = utils::get_current_working_dir().parent_path() / "share" / "logs.log";

    QString log_file_path_qstr = QString::fromStdString( log_file_path.string() );

    if ( !std::filesystem::exists(log_file_path) ) {

        QFile newLogFile(log_file_path_qstr);

        if (newLogFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Yeni log dosyası oluşturuldu: " << log_file_path_qstr;
            newLogFile.close();

        } else {
            qWarning() << "Log dosyası oluşturulamadı.";
            return;
        }

    }


    Log::instance().initialize(log_file_path_qstr);


    qInfo() << "\n\n" <<
    "##############################" << "\n" <<
    "#    STARTING THE PROGRAM    #" << "\n" <<
    "##############################";

    try{
        DBManager::checkPostgresqlInstallation();

    } catch (const std::exception &e){


        if (QMessageBox::critical(nullptr, "PostgreSQL database Failure!", e.what(), QMessageBox::Ok)
            ==QMessageBox::Ok )
        {
            exit(1);
        }

    }


    // userLoginCoord->show_window();

    int result = 0;

    while (true){
        result = dBLoginCoord->exec_view();

        if ( result == 357){
            break;
        }
        
        if (result == 0)
        {
            exit(0);
        }
        else {
            exit(-1);
        }
    }
    
    mainCoord->set_enabled(false);

    mainCoord->show_window(true);
    
    try{
        dBManager->ensure_tables_exists();
        mainCoord->set_enabled(true);
    }
    catch (std::exception &e ) {
        mainCoord->set_enabled(false);
        if (QMessageBox::critical(nullptr, "Critical Error", e.what())
        == QMessageBox::Ok)
        {
            exit(1);
        }
    }

}


AppCoord::~AppCoord(){

    delete config;
    delete mainCoord;
    delete dBLoginCoord;
}






