#pragma once

#include <QObject>

class PullDataWidget;
class PullDataVM;

class PullDataCoord : public QObject{
    Q_OBJECT
public:
    PullDataCoord(QObject *parent=nullptr);

    PullDataWidget *m_view;
    PullDataVM     *m_viewmodel;

private:

};