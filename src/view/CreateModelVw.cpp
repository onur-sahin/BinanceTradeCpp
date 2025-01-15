#include "CreateModelVw.hpp"
#include "ui_CreateModelDialog.h"
#include <iostream>


CreateModelVw::CreateModelVw(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateModelVw)
{
    ui->setupUi(this);
}

CreateModelVw::~CreateModelVw()
{
    delete ui;
}

void CreateModelVw::show_window(bool status){

        if (status == true){
            this->window()->show();

        } else {
            this->window()->hide();
        }
    }
