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
    qint64  startTs  = 1672531200000;
    qint64  endTs    = 1672533000000;

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
