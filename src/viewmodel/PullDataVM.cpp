#include "PullDataMdl.hpp"
#include "PullDataVM.hpp"

PullDataVM::PullDataVM(QObject *parent)
    : QObject(parent)
    , m_model(new PullDataMdl(parent))
{

}

void PullDataVM::start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs){

    m_model->start_pulling_data(pair, interval, startTs, endTs);

}

