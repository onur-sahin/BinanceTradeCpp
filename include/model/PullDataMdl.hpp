#pragma once

#include <QObject>
#include <iostream>
#include <unistd.h>

class QThread;
class QDataTime;


class PullDataWorker : public QObject {
    Q_OBJECT

public:

    QString pair     = "BTCUSDT";
    QString interval = "5m";
    qint64  startTs  = 0;
    qint64  endTs    = 0;

    QString table_name = "";
    qint64  deltaMs;
    qint64  _500deltaMs;
    qint64  pulledLastTimestamp = -1;

    void download_and_save(qint64 startTs, qint64 endTs);



signals:
    void updateProgress(int value);
    void finished();

public slots:
    void pullData();

};

class PullDataMdl : public QObject {
    Q_OBJECT

public:
    

    PullDataMdl(QObject *parent = nullptr);

    void start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs);
    

signals:
    void dataFetched();  // Veri çekme işlemi tamamlandığında sinyal

public:


private:
    QThread        *workerThread;
    PullDataWorker *worker;
};
