#ifndef CREATEMODELVW_H
#define CREATEMODELVW_H

#include <QDialog>

namespace Ui {
class CreateModelVw;
}

class CreateModelVw : public QDialog
{
    Q_OBJECT

public:
    explicit CreateModelVw(QWidget *parent = nullptr);
    ~CreateModelVw();

    void show_window(bool status);


private:
    Ui::CreateModelVw *ui;
};

#endif // CREATEMODELVW_H
