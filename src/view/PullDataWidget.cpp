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
