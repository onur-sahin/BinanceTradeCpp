#pragma once

#include <QObject>
#include <QList>


class MainVw;
class MainVM;

class CreateModelCoord;
class PullDataCoord;

class MainCoord : public QObject{

    Q_OBJECT
    
public:
    MainCoord();
    ~MainCoord();

    void show_window(bool status);

    void set_enabled(bool status);

    MainVw &get_view() const {
        return *m_view;
    }

    void connectViewModelToView();

public slots:
    void onPullDataCoordCloseWidget(PullDataCoord *pullDataCoord);
    
private:
    MainVw    *m_view;
    MainVM    *m_viewmodel;

    CreateModelCoord *m_createModelCoord;

    QList<PullDataCoord*> m_pullDataCoords;


};