#include "PullDataVM.hpp"
#include "PullDataMdl.hpp"


PullDataVM::PullDataVM(QObject *parent)
    : QObject(parent)
    , m_model(new PullDataMdl(parent))
{

}

void PullDataVM::start_pulling_data(){

    m_model->start_pulling_data();

}

