

/*
* Project    : BinanceTradeCpp
* Filename   : Log.hpp
* Description: This header file declares the Log class, which provides a 
*              singleton logging utility for the application. It allows 
*              logging messages to a specified file and sets up a custom 
*              message handler to capture Qt log messages.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-21 00:34 (UTC+3)
* Updated    : 2024-10-21 00:34 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - The Log class uses the singleton pattern to ensure that 
*               there is only one instance of the logger throughout the 
*               application.
*             - It provides an interface to initialize the log file and 
*               handle logging messages.
*/



#pragma once

#include <QFile>
#include <QString>            // QString: parametrelerde ve dönüş değerlerinde kullanılıyor

// Forward declarations (ileri deklarasyonlar)
class QFile;                  // QFile: logFile nesnesi olarak tanımlanmış, ancak ayrıntılar cpp dosyasında
class QMessageLogContext;     // QMessageLogContext: referans olarak kullanılıyor, tam tanım cpp dosyasında gerekli


class Log{
public:
    // Singleton pattern: There will be only one instance of Log
    static Log& instance();

    // Function to initialize the log file
    void initialize(const QString & logFilePath);
private:
    QFile logFile;

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    // Private Constructor (cannot be instantiated externally)
    Log() = default;

    // Disable copy constructor and assignment operator
    Log(const  Log&) = delete;
    Log &operator = (const Log &) = delete;
    
};