#include "PullDataCoord.hpp"
#include "PullDataVM.hpp"
#include "PullDataWidget.hpp"
#include "ui_PullDataWidget.h"

PullDataCoord::PullDataCoord(QObject *parent)
    : QObject(parent)
    , m_view     ( new PullDataWidget() )
    , m_viewmodel( new PullDataVM()     )
{
    connectViewmodelToView();

    connect(m_viewmodel, &PullDataVM::progressBarMaxValueUpdated,
            this, &PullDataCoord::onViewmodelProgressBarMaxValueUpdated);

    connect(m_viewmodel, &PullDataVM::progressBarValueUpdated,
            this, &PullDataCoord::onViewmodelProgressBarValueUpdated);

    connect(m_viewmodel, &PullDataVM::finished,
            this,        &PullDataCoord::onViewmodelFinished);

    // connect(m_view->ui->btn_ok, &QPushButton::clicked, )

}


void PullDataCoord::connectViewmodelToView(){
    m_view->connectOkButton([this](){
        emit closeWidget(this);
    });
}



void PullDataCoord::onViewmodelProgressBarMaxValueUpdated(int maxValue){

    if (maxValue == -1) {
        m_view->ui->progressBar->setValue(m_view->ui->progressBar->maximum() );
        m_view->ui->progressBar->setFormat("No data to process");
        return;
    }

    m_view->ui->progressBar->setMaximum(maxValue);
}


void PullDataCoord::onViewmodelProgressBarValueUpdated(int value){
     m_view->ui->progressBar->setValue(value);
}

void PullDataCoord::onViewmodelFinished(){

    m_view->ui->btn_ok->setEnabled(true);

}