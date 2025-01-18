#pragma once

#include <QWidget>

namespace Ui {
class PullDataWidget;
}

class PullDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PullDataWidget(QWidget *parent = nullptr);
    ~PullDataWidget();

private:
    Ui::PullDataWidget *ui;

};

