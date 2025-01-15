// #pragma once

// #include <QList>
// #include <QSqlDatabase>
// #include <QString>
// #include <filesystem>

// using namespace std;

// class DBManager{


// private:
//     static QString DBName;
//     static QString DBUser;
//     static QString DBHost;
//     static QString DBPort;
//     static QString DBPassword;

//     static QList<QSqlDatabase> connectionPool_;

// public:
//     DBManager();
//     ~DBManager();

//     void initializeDatabase();

//     static void checkPostgresqlInstallation();

//     void test_database_connection( const QString &database,  const QString &user,
//                                    const QString &host,      const QString &port,
//                                    const QString &password);

//     void save_database_connection_settings(const QString database,  const QString user,
//                                            const QString host,      const QString port,
//                                            const QString password);

//     QSqlDatabase get_connection();

//     void releaseConnection(QSqlDatabase db);


// private:
//     bool createNamesTable();
//     bool createDatabase();

// };




#pragma once

#include <QList>
#include <QSqlDatabase>
#include <QString>
#include <filesystem>
#include <QMutex>
#include <QMutexLocker>

using namespace std;

class DBManager {
private:
    // Private static member to hold the single instance
    static DBManager* instance;
    
    static QString DBName;
    static QString DBUser;
    static QString DBHost;
    static QString DBPort;
    static QString DBPassword;

    static QList<QSqlDatabase> connectionPool_;
    static QMutex mutex_;

    // Private constructor to prevent direct instantiation
    DBManager();
    ~DBManager();

public:
    // Static method to access the single instance
    static DBManager* getInstance();

    void initializeDatabase();

    static void checkPostgresqlInstallation();

    void test_database_connection(const QString &database, const QString &user,
                                   const QString &host, const QString &port,
                                   const QString &password);

    void save_database_connection_settings(const QString database, const QString user,
                                           const QString host, const QString port,
                                           const QString password);

    QSqlDatabase get_connection();

    void releaseConnection(QSqlDatabase &db);

    void execute_query(QString &query);

    void create_klines_table(const QString table_name);
    void ensure_tables_exists();

private:


};
