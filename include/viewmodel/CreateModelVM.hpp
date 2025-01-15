
#pragma once

#include <QObject>

#include "CreateModelMdl.hpp"



class CreateModelVM : public QObject {

    Q_OBJECT

public:
    CreateModelVM(QObject *parent = nullptr);
    ~CreateModelVM();

private:

    CreateModelMdl *m_model;

};