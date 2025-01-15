
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

            PullDataCoord *coord = new PullDataCoord(m_view);
            m_pullDataCoords.push_back(coord);

            m_view->ui->vl_info_area->addWidget( coord->m_view );

            coord->m_viewmodel->start_pulling_data();
        }
    );
}


