// #pragma once

// #include <QDialog>

// namespace Ui {
// class DBLoginVw;
// }

// class DBLoginVw : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit DBLoginVw(QWidget *parent = nullptr);
//     ~DBLoginVw();


//     void show_database_test_result(bool result, std::exception e);
    
//     void connectLoginButton(std::function<void()> callback) override;
//     void connectTestButton (std::function<void()> callback) override;
//     void exec_view         ()                               override;

//     inline void show_window(bool status) const override{

//         if (status==true){
//             this->window()->show();

//         } else {
//             this->window()->hide();
//         }
//     }

//     inline void set_enabled(bool enabled) const override{
//         this->window()->setEnabled(enabled);
//     }

//     inline const QString get_database() const override{
//         return ui->le_database->text(); }

//     inline const QString get_user() const override{
//         return ui->le_user->text(); }

//     inline const QString get_host() const override{
//         return ui->le_host->text(); }

//     inline const QString get_port() const override{
//         return ui->le_port->text(); }

//     inline const QString get_password() const override{
//         return ui->le_password->text(); }

//     inline const Qt::CheckState get_rememberPassword() const override {
//         return ui->cb_remember_pass->checkState(); }

//     // inline       QPushButton &*get_login_button() const {
//     //     return ui->btn_login;
//     // }


//     inline void set_database(const QString &database) override {
//         ui->le_database->setText(database); }

//     inline void set_user(const QString &user) override {
//         ui->le_user->setText(user); }

//     inline void set_host(const QString &host) override {
//         ui->le_host->setText(host); }

//     inline void set_port(const QString &port) override {
//         ui->le_port->setText(port); }

//     inline void set_password(const QString &password) override {
//         ui->le_password->setText(password);
//     }

//     inline void set_remember(const Qt::CheckState &remember) override {
//         ui->cb_remember_pass->setCheckState(remember);
//     }

//     inline void set_connection_test_result(const QString &test_result) override {
//         ui->label_connection_test_result->setText(test_result);
//     }



// // signals:
// //     void btn_test_connection_clicked(){}

// // private slots:
// //     void test_connection_succesfully(){}


// private:
//     Ui::DBLoginVw *ui;
// };
