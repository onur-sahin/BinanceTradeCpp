

#include "Binance.hpp"
#include "PullDataMdl.hpp"
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QTimeZone>
#include <nlohmann/json.hpp>

#include "DBManager.hpp"

using namespace std;
using json = nlohmann::json;

qint64 intervalToMs(QString &interval){
    if (interval[interval.length() - 1] == QChar('m')){
        return 5*60*1000;
    }
    return 0; // Default return value if condition is not met
}

void PullDataWorker::download_and_save(qint64 startTs, qint64 endTs){

    string data;

    DBManager *db = DBManager::getInstance();

    data = fetchBinanceHistoricalData(  pair.toStdString(), interval.toStdString(), startTs, endTs);

    json parsed_json = json::parse(data);

    // for (const auto &kline: parsed_json){
    //     cout << kline[0] << " - " << QDateTime::fromMSecsSinceEpoch(kline[0], QTimeZone::utc()).toString().toStdString() << endl;
    // }

    db->insert_klines(table_name, parsed_json);

}

void PullDataWorker::pullData(){

    deltaMs      = intervalToMs(interval);
    _500deltaMs  = deltaMs * 500;

    if (startTs > endTs){
        emit finished();
        return;
    }

    //kopya oluştur
    qint64 startTs = this->startTs;
    qint64 endTs   = this->endTs;

    // startTs'yi yukarı yuvarla
    startTs = ((startTs + deltaMs - 1) / deltaMs) * deltaMs;

    // endTs'yi aşağı yuvarla
    endTs = (endTs / deltaMs) * deltaMs;

    table_name = "tbl_" + pair.toLower() + "_" + interval;

    DBManager *db = DBManager::getInstance();

    db->create_klines_table(table_name);

    QVector<qint64> saved_ts = db->select_open_time(table_name, startTs, endTs);
    QVector<qint64> absent_ts;

    QVector<QPair<qint64, qint64>> pair_ts;

  
    qint64 temp_ts = startTs;

    while(temp_ts <= endTs){
        if(not saved_ts.contains(temp_ts)){
            absent_ts.append(temp_ts);
        }

        temp_ts += deltaMs;
    }
    
    qint64 temp_startTs;

    if (not absent_ts.isEmpty()){
        temp_startTs = absent_ts.at(0);
    }

    bool mark_start = false;

    qint64 count = 0;

    for (qint64 &ts : absent_ts){

        count++;

        if (mark_start){
            temp_startTs = ts;
            mark_start = false;
        }

        temp_ts = ts + deltaMs;

        if (not absent_ts.contains(temp_ts) or count > 500){

            pair_ts.append(QPair<qint64, qint64>(temp_startTs, ts));
            mark_start = true;
            count = 0;
        }

    }   
    
    for ( QPair<qint64, qint64> &pair : pair_ts){
        download_and_save(pair.first, pair.second);
    }


    emit finished();
}


PullDataMdl::PullDataMdl(QObject *parent)
    : QObject(parent){

    worker       = new PullDataWorker();
    workerThread = new QThread(this);

    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &PullDataWorker::pullData);

}


void PullDataMdl::start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs) {

    worker->pair    = pair;
    worker->interval= interval;
    worker->startTs = startTs;
    worker->endTs   = endTs;

    workerThread->start();


}


