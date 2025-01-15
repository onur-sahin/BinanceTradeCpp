

#include "PullDataMdl.hpp"
#include <QThread>
#include <QDebug>


void PullDataWorker::pullData(){
    
        for (int i= 0; i<10; i++){
            std::cout<<"iş\n"<<std::endl;
            sleep(5);
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


void PullDataMdl::start_pulling_data() {
    // Veritabanı işlemlerini burada yapıyoruz
    // Örnek olarak:

    workerThread->start();


}


