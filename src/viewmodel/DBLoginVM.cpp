

#include "DBLoginVM.hpp"
#include <QDebug>
#include <QObject>

DBLoginVM::DBLoginVM( QObject *parent)
    :IDBLoginVM(parent),
    m_model( new DBLoginMdl() )
{
}


void DBLoginVM::show_window(bool status){
    emit showWindowRequested(status);
}

void DBLoginVM::test_connection(){
    m_model->test_database_connection();
}

void DBLoginVM::save_connection(){
    m_model->save_database_connection();
}



void DBLoginVM::attempt_login(){
    // m_model->user_name_in_use();
}



