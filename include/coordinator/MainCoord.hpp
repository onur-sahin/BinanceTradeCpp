#pragma once

#include <QObject>


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
    
private:
    MainVw    *m_view;
    MainVM    *m_viewmodel;

    CreateModelCoord *m_createModelCoord;

    std::vector<PullDataCoord*> m_pullDataCoords;


};