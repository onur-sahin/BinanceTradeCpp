#pragma once
#include <QObject>

#include "CreateModelVM.hpp"
#include "CreateModelVw.hpp"


class CreateModelCoord : public QObject {
        Q_OBJECT
public:
    CreateModelCoord(QObject *parent = nullptr);
    ~CreateModelCoord();

    void show_window(bool status);

    void connectViewmodelToView();

private:
    CreateModelVw *m_view;
    CreateModelVM *m_viewmodel;

};