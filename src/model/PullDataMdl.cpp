

#include "PullDataMdl.hpp"
#include "Binance.hpp"
#include <QThread>
#include <QDebug>



void PullDataWorker::pullData(){

    std::string symbol = "BTCUSDT";      // İşlem çifti
    std::string interval = "1h";        // Mum çubuğu aralığı (1 saat)
    long startTime = 1672531200000;     // Başlangıç zamanı (timestamp, milisaniye)
    long endTime = 1672617600000;       // Bitiş zamanı (timestamp, milisaniye)

    fetchBinanceHistoricalData(symbol, interval, startTime, endTime);



    emit finished();
}


PullDataMdl::PullDataMdl(QObject *parent)
    : QObject(parent){

    worker       = new PullDataWorker();
    workerThread = new QThread(this);

    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::started, worker, &PullDataWorker::pullData);

}


void PullDataMdl::start_pulling_data() {
    // Veritabanı işlemlerini burada yapıyoruz
    // Örnek olarak:

    workerThread->start();


}


