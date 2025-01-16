#pragma once

#include <QObject>
#include <iostream>
#include <unistd.h>

class QThread;
class QDataTime;


class PullDataWorker : public QObject {
    Q_OBJECT

public:

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

    void start_pulling_data();


signals:
    void dataFetched();  // Veri çekme işlemi tamamlandığında sinyal

public:
    QString        *start_timestamp;


private:
    QThread        *workerThread;
    PullDataWorker *worker;
};
