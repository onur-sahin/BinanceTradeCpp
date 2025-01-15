
#include "CreateModelCoord.hpp"


CreateModelCoord::CreateModelCoord(QObject *parent)
    : QObject     ( parent              )
    , m_view      ( new CreateModelVw() )
    , m_viewmodel ( new CreateModelVM() )
{

    connectViewmodelToView();
}

CreateModelCoord::~CreateModelCoord(){}

void CreateModelCoord::show_window(bool status){
    m_view->show_window(status);
}

void CreateModelCoord::connectViewmodelToView(){

}