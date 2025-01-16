/*
* Project    : BinanceTradeCpp
* Filename   : MainVM.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-25 09:13 (UTC+3)
* Updated    : 2024-10-25 09:13 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#include "MainVM.hpp"

MainVM::MainVM()
    :m_model(new MainModel)
{

}

void MainVM::update_inputs_for_train(const QString &pair,    const qint32 &epoch,
                                     const QDate &startDate, const QTime &startTime,
                                     const QDate &endDate, const QTime &endTime)
{
    m_model->setPair(pair);
    m_model->setEpoch(epoch);
    m_model->setTrainStartDate(startDate);
    m_model->setTrainStartTime(startTime);
    m_model->setTrainEndDate(endDate);
    m_model->setTrainEndTime(endTime);
}
