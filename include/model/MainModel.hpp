/*
* Project    : BinanceTradeCpp
* Filename   : MainModel.hpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-25 09:17 (UTC+3)
* Updated    : 2024-10-25 09:17 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/


#pragma once

#include <QDateTime>
// #include <QTimestamp> // Removed because it does not exist

#include <QString>

class MainModel{

public:
    MainModel();

    void update_ts_train_start();
    void update_ts_train_end();
    void update_ts_test_start();
    void update_ts_test_end();

    void update_dt_trainStart();
    void update_dt_trainEnd();
    void update_dt_testStart();
    void update_dt_testEnd();

    qint64 getTrainStartTs() const;
    qint64 getTraintEndTs() const;
    qint64 getTestStartTs() const;
    qint64 getTestEndTs() const;

    // Getter ve Setter for trainStartDate
    QDate getTrainStartDate() const;
    void setTrainStartDate(const QDate& date);

    // Getter ve Setter for trainEndDate
    QDate getTrainEndDate() const;
    void setTrainEndDate(const QDate& date);


    // Getter ve Setter for trainStartTime
    QTime getTrainStartTime() const;
    void setTrainStartTime(const QTime& time);

    // Getter ve Setter for trainEndTime
    QTime getTrainEndTime() const;
    void setTrainEndTime(const QTime& time);

    // Getter ve Setter for epoch
    qint32 getEpoch() const;
    void setEpoch(qint32 value);

    // Getter ve Setter for pair
    QString getPair() const;
    void setPair(const QString& value);

    // Getter ve Setter for testSpeed
    qint32 getTestSpeed() const;
    void setTestSpeed(qint32 value);

    // Getter ve Setter for maxChartCount
    qint32 getMaxChartCount() const;
    void setMaxChartCount(qint32 value);

    // Getter ve Setter for testStartDate
    QDate getTestStartDate() const;
    void setTestStartDate(const QDate& date);

    // Getter ve Setter for testEndDate
    QDate getTestEndDate() const;
    void setTestEndDate(const QDate& date);

    // Getter ve Setter for testStartTime
    QTime getTestStartTime() const;
    void setTestStartTime(const QTime& time);

    // Getter ve Setter for testEndTime
    QTime getTestEndTime() const;
    void setTestEndTime(const QTime& time);

private:
    QDate trainStartDate;
    QDate trainEndDate;

    QTime trainStartTime;
    QTime trainEndTime;

    qint32 epoch;
    QString pair;

    QDateTime dt_trainStart;
    QDateTime dt_trainEnd;

    qint64 ts_ms_trainStart;
    qint64 ts_ms_trainEnd;




    qint32 testSpeed;
    qint32 maxChartCount;

    QDate testStartDate;
    QDate testEndDate;

    QTime testStartTime;
    QTime testEndTime;

    QDateTime dt_testStart;
    QDateTime dt_testEnd;

    qint64 ts_ms_testStart;
    qint64 ts_ms_testEnd;

    


public:
    ~MainModel(){
    }
};