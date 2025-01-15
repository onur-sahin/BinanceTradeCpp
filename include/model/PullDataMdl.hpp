#pragma once

#include <QObject>
#include <iostream>
#include <unistd.h>

class QThread;


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

private:
    QThread        *workerThread;
    PullDataWorker *worker;
};
