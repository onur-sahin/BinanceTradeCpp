/*
* Project    : BinanceTradeCpp
* Filename   : Log.cpp
* Description: This source file implements the Log class, which provides 
*              a singleton logging utility. It handles file operations for 
*              logging messages and installs a custom message handler to 
*              redirect Qt logging to the log file.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-21 00:21 (UTC+3)
* Updated    : 2024-10-21 00:21 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - The Log class ensures only one instance exists throughout 
*               the application by using the singleton pattern.
*             - The log file is opened in append mode, ensuring that new log 
*               entries are added to the end of the file.
*             - The custom message handler captures messages sent through 
*               qDebug(), qWarning(), etc., and redirects them to the log file.
*/

#include "Log.hpp"            // Log sınıfı bildirimleri için

#include <QDateTime>          // QDateTime: tarih ve saat bilgisini almak için
#include <QIODevice>          // QIODevice::Append ve Text modları için
#include <QTextStream>        // QTextStream: dosyaya yazmak için
#include <QTimeZone>          // QTimeZone: zaman dilimini ayarlamak için
#include <iostream>           // std::cerr kullanımı için


// Log::Log(){} defined in .hpp file as follows Log()=default;

// Returns the singleton instance
Log& Log::instance(){
    static Log instance;
    return instance;
}



// Inıtializes the log file and installs the custom message handler
void Log::initialize(const QString &logFilePath){
    logFile.setFileName(logFilePath);
    logFile.open(QIODevice::Append | QIODevice::Text);

    qInstallMessageHandler( messageHandler );

}


void Log::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QTextStream out(&Log::instance().logFile);

    QString errorLevel = "None";

    switch (type) {
        case QtDebugMsg:
            errorLevel = "Debug";
            break;
        case QtInfoMsg:
            errorLevel = "Info";
            break;
        case QtWarningMsg:
            errorLevel = "Warning";
            break;
        case QtCriticalMsg:
            errorLevel = "Critical";
            break;
        case QtFatalMsg:
            errorLevel = "Fatal";
            abort();
    }

    errorLevel = errorLevel.leftJustified(10, ' ');

    QString logFormat = "[%1] [%2] %3";
    
    QTimeZone timeZone("Europe/Istanbul");

    QString datetimeString = QDateTime::currentDateTime(timeZone).toString("HH:mm:sstt dd-MM-yy");

    QString editedMessage = logFormat.arg(datetimeString, errorLevel, msg );

    std::cerr << editedMessage.toStdString() << std::endl;
    out       << editedMessage << "\n";

    out.flush();
}