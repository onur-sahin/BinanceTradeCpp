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

    void connectOkButton(std::function<void()> callback);
    
Ui::PullDataWidget *ui;

};

