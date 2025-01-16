/*
* Project    : BinanceTradeCpp
* Filename   : MainModel.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-25 09:16 (UTC+3)
* Updated    : 2024-10-25 09:16 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/


#include "MainModel.hpp"
#include <QTimeZone>

MainModel::MainModel(){

}

void MainModel::update_ts_train_start(){
    ts_ms_trainStart = dt_trainStart.toMSecsSinceEpoch();
}

void MainModel::update_ts_train_end(){
    ts_ms_trainEnd = dt_trainEnd.toMSecsSinceEpoch();
}

void MainModel::update_ts_test_start(){
    ts_ms_testStart = dt_testStart.toMSecsSinceEpoch();
}

void MainModel::update_ts_test_end(){
    ts_ms_testEnd = dt_testEnd.toMSecsSinceEpoch();
}

void MainModel::update_dt_trainStart(){
    dt_trainStart = QDateTime(trainStartDate, trainStartTime, QTimeZone::utc());
    update_ts_train_start();
}

void MainModel::update_dt_trainEnd(){
    dt_trainEnd = QDateTime(trainEndDate, trainEndTime, QTimeZone::utc());
    update_ts_train_end();
}

void MainModel::update_dt_testStart(){
    dt_testStart = QDateTime(testStartDate, testStartTime, QTimeZone::utc());
    update_ts_test_start();
}

void MainModel::update_dt_testEnd(){
    dt_testEnd = QDateTime(testEndDate, testEndTime, QTimeZone::utc());
    update_ts_test_end();
}

qint64 MainModel::getTrainStartTs() const {return ts_ms_trainStart;}
qint64 MainModel::getTraintEndTs()  const {return ts_ms_trainEnd;}
qint64 MainModel::getTestStartTs()  const {return ts_ms_testStart;}
qint64 MainModel::getTestEndTs()    const {return ts_ms_testEnd;}


// Getter ve Setter for trainStartDate
QDate MainModel::getTrainStartDate() const {
    return trainStartDate;
}

void MainModel::setTrainStartDate(const QDate& date) {
    trainStartDate = date;
}

// Getter ve Setter for trainEndDate
QDate MainModel::getTrainEndDate() const {
    return trainEndDate;
}

void MainModel::setTrainEndDate(const QDate& date) {
    trainEndDate = date;
}

// Getter ve Setter for trainStartTime
QTime MainModel::getTrainStartTime() const {
    return trainStartTime;
}

void MainModel::setTrainStartTime(const QTime& time) {
    trainStartTime = time;
}

// Getter ve Setter for trainEndTime
QTime MainModel::getTrainEndTime() const {
    return trainEndTime;
}

void MainModel::setTrainEndTime(const QTime& time) {
    trainEndTime = time;
}

// Getter ve Setter for epoch
qint32 MainModel::getEpoch() const {
    return epoch;
}

void MainModel::setEpoch(qint32 value) {
    epoch = value;
}

// Getter ve Setter for pair
QString MainModel::getPair() const {
    return pair;
}

void MainModel::setPair(const QString& value) {
    pair = value;
}

// Getter ve Setter for testSpeed
qint32 MainModel::getTestSpeed() const {
    return testSpeed;
}

void MainModel::setTestSpeed(qint32 value) {
    testSpeed = value;
}

// Getter ve Setter for maxChartCount
qint32 MainModel::getMaxChartCount() const {
    return maxChartCount;
}

void MainModel::setMaxChartCount(qint32 value) {
    maxChartCount = value;
}

// Getter ve Setter for testStartDate
QDate MainModel::getTestStartDate() const {
    return testStartDate;
}

void MainModel::setTestStartDate(const QDate& date) {
    testStartDate = date;
}

// Getter ve Setter for testEndDate
QDate MainModel::getTestEndDate() const {
    return testEndDate;
}

void MainModel::setTestEndDate(const QDate& date) {
    testEndDate = date;
}

// Getter ve Setter for testStartTime
QTime MainModel::getTestStartTime() const {
    return testStartTime;
}

void MainModel::setTestStartTime(const QTime& time) {
    testStartTime = time;
}

// Getter ve Setter for testEndTime
QTime MainModel::getTestEndTime() const {
    return testEndTime;
}

void MainModel::setTestEndTime(const QTime& time) {
    testEndTime = time;
}