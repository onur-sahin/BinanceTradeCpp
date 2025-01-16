
#include <iostream>

#include "DBLoginCoord.hpp"
#include "DBLoginVM.hpp"
#include "DBLoginVw.hpp"
#include <QMessageBox>
#include <QString>

DBLoginCoord::DBLoginCoord(QObject *parent)
    : QObject    (     parent      )
    , m_view     ( new DBLoginVw() )
    , m_viewmodel( new DBLoginVM() )
{

    connectViewmodelToView();
    initiliaze_model_default_values_from_view();
}

void DBLoginCoord::set_enabled(bool enabled){
    m_view->set_enabled(enabled);
}

void DBLoginCoord::show_window(bool status){
    m_view->show_window(status);
}

int DBLoginCoord::exec_view(){

    return m_view->exec_view();
}

void DBLoginCoord::test_connection(){
    m_viewmodel->test_connection();
}

void DBLoginCoord::save_connection(){
    m_viewmodel->save_connection();
}

void DBLoginCoord::initiliaze_model_default_values_from_view(){

    m_viewmodel->updateViewmodelFromView();

}

void DBLoginCoord::connectViewmodelToView(){

    m_viewmodel->updateViewmodelFromView =
    
    [this](){
        m_viewmodel->set_database ( m_view->get_database() );
        m_viewmodel->set_user     ( m_view->get_user()     );
        m_viewmodel->set_host     ( m_view->get_host()     );
        m_viewmodel->set_port     ( m_view->get_port()     );
        m_viewmodel->set_password ( m_view->get_password() );

        m_viewmodel->set_rememberPassword (m_view->get_rememberPassword());
   
        };


    m_view->connectLoginButton(

        [this](){
            m_viewmodel->updateViewmodelFromView();

            // QObject::connect(m_viewmodel, &DBLoginVM::connection_test_result, this, [=](bool result, std::exception e){
            //     std::cout << "bura456" << result << std::endl;
            //     if (result){
            //         emit connectedToDatabase();

            //     } else {

            //         QMessageBox::StandardButton button =  QMessageBox::critical(m_view,
            //                                                                     "Failure Login to Database",
            //                                                                     e.what(),
            //                                                                     QMessageBox::Ok);

            //         if (button == QMessageBox::Ok){
            //             return;
            //         }

            //     }

            // });

            try{
                test_connection();
            } catch (std::exception &e){
                qDebug()<< "Failure in DBLogingCoord in after clicked login button: " << e.what();
                m_view->set_connection_test_result( QString("failure in DBLoginCoord::connectLoginButton: {}").arg(e.what()) );
                return;
            }


            save_connection();

            if (m_view->get_rememberPassword() == true ){
                ;
            }

            this->m_view->done(357);

        }
    );


    m_view->connectTestButton(

        [this](){
            m_viewmodel->updateViewmodelFromView();

            try {
                m_viewmodel->test_connection();

            } catch ( std::exception &e){
                qDebug()<< "failure in DBLoginCoord::test_connection(): " << e.what();
                m_view->set_connection_test_result( QString("failure in DBLoginCoord::test_connection(): {}").arg(e.what()) );
                return;
            }

            m_view->set_connection_test_result("Connection Test Result:Succesfull");

        }

    );

    // CONNECT INPUT SIGNALS

    // handle connection test result
    QObject::connect(m_viewmodel, &DBLoginVM::connection_test_result, this, [=](bool result, std::exception e){
            m_view->show_database_test_result(result, e);

    });

    QObject::connect(m_viewmodel, &DBLoginVM::showWindowRequested, this, [=](bool status){
        show_window(status);
    });


    QObject::connect(m_viewmodel, &IDBLoginVM::databaseChanged, [this](){
        m_view->set_database(m_viewmodel->get_database());
    });

    QObject::connect(m_viewmodel, &IDBLoginVM::userChanged, [this](){
        m_view->set_user(m_viewmodel->get_user() );
    });

    QObject::connect(m_viewmodel, &IDBLoginVM::hostChanged, [this](){
        m_view->set_host(m_viewmodel->get_host() );
    });

    QObject::connect(m_viewmodel, &IDBLoginVM::portChanged, [this](){
        m_view->set_port(m_viewmodel->get_port() );
    });

    QObject::connect(m_viewmodel, &IDBLoginVM::passwordChanged, [this](){
        m_view->set_password(m_viewmodel->get_password() );
    });
    
} // connectViewmodelToView


bool DBLoginCoord::authenticate(const QString &database){
    return true;
}





