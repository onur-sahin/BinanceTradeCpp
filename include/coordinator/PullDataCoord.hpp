#pragma once

#include <QObject>

class PullDataWidget;
class PullDataVM;

class PullDataCoord : public QObject{
    Q_OBJECT
public:
    PullDataCoord(QObject *parent=nullptr);
    void connectViewmodelToView();


    PullDataWidget *m_view;
    PullDataVM     *m_viewmodel;

signals:
    void closeWidget(PullDataCoord*);

public slots:
    void onViewmodelProgressBarMaxValueUpdated(int maxValue);
    void onViewmodelProgressBarValueUpdated(int value);
    void onViewmodelFinished();

private:

};