#pragma once
#include <QObject>

class PullDataMdl;

class PullDataVM : public QObject{
    Q_OBJECT


public slots:

    // void onProgbar


public:
    PullDataVM(QObject *parent = nullptr);

    void start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs);

    PullDataMdl *m_model;

private:
};