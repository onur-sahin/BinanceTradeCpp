

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

void PullDataWorker::pullData(){

    string data;
    QString table_name = "tbl_" + pair + "_" + interval;
    DBManager *db = DBManager::getInstance();

    db->create_klines_table(table_name);

    QPair<qint64,qint64> min_max = db->get_min_max_ts(table_name);

    if( startTs < min_max.first and endTs >= min_max.second){

    } else if ( startTs >= min_max.first and endTs <= min_max.second){
    
    } else if ()
    
    qint64 pulledLastTimestamp = -1;

    qint64 deltaMs = intervalToMs(interval);
    qint64 _500deltaMs = deltaMs*500;

    qint64 tempStartTimestamp = startTs;
    qint64 tempEndTimestamp   = startTs + 500*deltaMs;

    while(pulledLastTimestamp != endTs){

        if (tempEndTimestamp >= endTs){

            tempEndTimestamp    = endTs;
            pulledLastTimestamp = endTs;

        } else {
            pulledLastTimestamp = tempEndTimestamp;
        }

        data = fetchBinanceHistoricalData(  pair.toStdString(), interval.toStdString(),
                                                tempStartTimestamp, tempEndTimestamp);

        json parsed_json = json::parse(data);

        // for (const auto &kline: parsed_json){
        //     cout << kline[0] << " - " << QDateTime::fromMSecsSinceEpoch(kline[0], QTimeZone::utc()).toString().toStdString() << endl;
        // }

        db->insert_klines(table_name, parsed_json);

        tempStartTimestamp = tempEndTimestamp   + deltaMs;
        tempEndTimestamp   = tempStartTimestamp + _500deltaMs;


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


