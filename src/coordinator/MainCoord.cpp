
#include "MainCoord.hpp"
#include "MainVM.hpp"
#include "MainVw.hpp"
#include "CreateModelCoord.hpp"

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
}


