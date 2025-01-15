#pragma once

#include "ui_MainWindow.h"
#include "IMainVw.hpp"
#include <QMainWindow>

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

class MainVw : public QMainWindow, public IMainVw
{
    Q_OBJECT
public:
    MainVw(QWidget *parent = nullptr);
    ~MainVw();

    void show_window(bool status);

    void set_enabled(bool enabled);

    void closeEvent(QCloseEvent *event);

    void connectCreateModelButton(std::function<void()> callback);
    void connectPullDataButton   (std::function<void()> callback);



Ui::MainWindow *ui;

private:



};
