#include "PullDataMdl.hpp"
#include "PullDataVM.hpp"

PullDataVM::PullDataVM(QObject *parent)
    : QObject(parent)
    , m_model(new PullDataMdl(parent))
{
    connect(m_model, &PullDataMdl::maxValueChanged,
            this, &PullDataVM::onModelMaxValueChanged);
    
    connect(m_model, &PullDataMdl::valueChanged,
        this, &PullDataVM::onModelValueChanged);

    connect(m_model, &PullDataMdl::finished,
            this,    &PullDataVM::onModelFinished);

}

void PullDataVM::onModelMaxValueChanged(int maxValue){
    emit progressBarMaxValueUpdated(maxValue);
}
void PullDataVM::onModelValueChanged(int value){
    emit progressBarValueUpdated(value);
}

void PullDataVM::onModelFinished(){
    emit finished();
}

void PullDataVM::start_pulling_data(QString pair, QString interval, qint64 startTs, qint64 endTs){

    m_model->start_pulling_data(pair, interval, startTs, endTs);

}

