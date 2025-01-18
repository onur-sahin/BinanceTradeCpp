
#include "CreateModelCoord.hpp"
#include "MainCoord.hpp"
#include "MainVM.hpp"
#include "MainVw.hpp"
#include "PullDataCoord.hpp"
#include "PullDataVM.hpp"
#include "PullDataWidget.hpp"

#include <iostream>

MainCoord::MainCoord()
    : m_view(new MainVw())
    , m_viewmodel(new MainVM())
    
{
    
    connectViewModelToView();
    m_createModelCoord = new CreateModelCoord(this);

}

MainCoord::~MainCoord(){
    delete m_view;
    delete m_viewmodel;
    delete m_createModelCoord;
}

void MainCoord::show_window(bool status){
    m_view->show_window(status);
}

void MainCoord::set_enabled(bool status){
    m_view->set_enabled(status);
}

void MainCoord::onPullDataCoordCloseWidget(PullDataCoord *pullDataCoord){
    pullDataCoord->m_view->hide();
    m_view->ui->vl_info_area->removeWidget(pullDataCoord->m_view);
    m_pullDataCoords.removeOne(pullDataCoord);
    delete pullDataCoord;
}

void MainCoord::connectViewModelToView(){
    
    m_view->connectCreateModelButton(

        [this](){
            m_createModelCoord->show_window(true);
        }

    );

    m_view->connectPullDataButton(

        [this](){

            m_viewmodel->update_inputs_for_train(m_view->ui->cb_pairs->currentText(),
                                                 m_view->ui->le_interval_pulldata->text(),
                                                 m_view->ui->le_epoch->text().toInt(), //toInt 32 bit, toLongLong 64 bit
                                                 m_view->ui->de_train_start->date(),
                                                 m_view->ui->te_train_start->time(),
                                                 m_view->ui->de_train_end->date(),
                                                 m_view->ui->te_train_end->time()
            );

            PullDataCoord *pullDataCoord = new PullDataCoord(m_view);

            QObject::connect(pullDataCoord, &PullDataCoord::closeWidget,
                             this,          &MainCoord::onPullDataCoordCloseWidget);

            m_pullDataCoords.push_back(pullDataCoord);

            m_view->ui->vl_info_area->addWidget( pullDataCoord->m_view );
            m_view->ui->te_train_start->time();

            pullDataCoord->m_viewmodel->start_pulling_data(
                                                           m_viewmodel->m_model->getPair(),
                                                           m_viewmodel->m_model->getInterval(),
                                                           m_viewmodel->m_model->getTrainStartTs(),
                                                           m_viewmodel->m_model->getTraintEndTs()
                                                          );

            // m_viewmodel->print_main_model_values();



        }
    );

}


