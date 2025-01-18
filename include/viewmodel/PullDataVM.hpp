#pragma once
#include <QObject>

class PullDataMdl;

class PullDataVM : public QObject{
    Q_OBJECT



public:
    PullDataVM(QObject *parent = nullptr);

    void start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs);

public slots:
    void onModelMaxValueChanged(int maxValue);
    void onModelValueChanged(int value);
    void onModelFinished();

signals:
    void progressBarMaxValueUpdated(int maxValue);
    void progressBarValueUpdated(int value);
    void finished();

public:

    PullDataMdl *m_model;

private:

};