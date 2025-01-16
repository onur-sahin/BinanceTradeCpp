
#include "MainCoord.hpp"
#include "MainVM.hpp"
#include "MainVw.hpp"
#include "CreateModelCoord.hpp"
#include "PullDataCoord.hpp"
#include "PullDataWidget.hpp"
#include "PullDataVM.hpp"

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

void MainCoord::connectViewModelToView(){
    m_view->connectCreateModelButton(

        [this](){
            m_createModelCoord->show_window(true);
        }

    );

    m_view->connectPullDataButton(

        [this](){

            m_viewmodel->update_inputs_for_train(m_view->ui->cb_pairs->currentText(),
                                                 m_view->ui->le_epoch->text().toInt(), //toInt 32 bit, toLongLong 64 bit
                                                 m_view->ui->de_train_start->date(),
                                                 m_view->ui->te_train_start->time(),
                                                 m_view->ui->de_train_end->date(),
                                                 m_view->ui->te_train_end->time()
            );  

            PullDataCoord *pullDataCoord = new PullDataCoord(m_view);

            m_pullDataCoords.push_back(pullDataCoord);

            m_view->ui->vl_info_area->addWidget( pullDataCoord->m_view );
            // m_viewmodel->
            std::cout << "bu:" << m_view->ui->de_train_start->date().toString().toStdString() << std::endl;
            m_view->ui->te_train_start->time();
            pullDataCoord->m_viewmodel->start_pulling_data();

        }
    );


}


