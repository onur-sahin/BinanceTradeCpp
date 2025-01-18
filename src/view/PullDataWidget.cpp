#include "PullDataWidget.hpp"
#include "ui_PullDataWidget.h"

PullDataWidget::PullDataWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PullDataWidget)
{
    ui->setupUi(this);
}

PullDataWidget::~PullDataWidget()
{ 
    delete ui;
}


void PullDataWidget::connectOkButton(std::function<void()> callback){
    connect(ui->btn_ok, &QPushButton::clicked, this, [callback](){callback();});
}
