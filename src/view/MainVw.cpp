

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>

#include <QCloseEvent>
#include "MainVw.hpp"

#include <iostream>

MainVw::MainVw(QWidget *parent)
    : QMainWindow(parent)
    , ui( new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainVw::~MainVw(){
    delete ui;
}

void MainVw::show_window(bool status){
    this->show();
}

void MainVw::set_enabled(bool enabled){
    this->setEnabled(enabled);
}


void MainVw::closeEvent(QCloseEvent *event) {
    
    // if ( QMessageBox::question(this, "Comfirm Exit", "Are you sure want to exit?")==QMessageBox::Yes ){
    //     event->accept();
    //     QApplication::quit();
    //     qDebug() << "\n" <<
    //     "###############################"  << "\n" <<
    //     "#   QUITING THE PROGRAM ...   #" << "\n" <<
    //     "###############################" ;
    // } else {
    //     event->ignore();
    // }

    QApplication::quit();
}

void MainVw::connectCreateModelButton(std::function<void()> callback){
    connect(ui->btn_create_new_model, &QPushButton::clicked, this,
    [callback](){callback();}
    );
}

void MainVw::connectPullDataButton(std::function<void()> callback){
    connect(ui->btn_pull_data, &QPushButton::clicked, this, 
    [callback](){callback();}
    );
}








