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
#include <QMutex>
#include <QMutexLocker>
#include <QSqlDatabase>
#include <QString>
#include <QVariantMap>
#include <filesystem>

#include <nlohmann/json.hpp>

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

    void insert_klines(const QString &table_name, const nlohmann::json &parsed_json);
    QVariantList execute_query_result(const QString &query_text, const QVariantMap &bind_values);
    void execute_query(const QString &query_text, const QVariantMap &bind_values={});

    void create_klines_table(const QString table_name);
    void ensure_tables_exists();

    QPair<qint64, qint64> get_min_max_ts(const QString &table_name);

private:


};
