#pragma once
#include <QObject>

class PullDataMdl;

class PullDataVM : public QObject{
    Q_OBJECT
public:
    PullDataVM(QObject *parent = nullptr);

    void start_pulling_data();

    PullDataMdl *m_model;

private:
};