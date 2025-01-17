// /*
// * Project    : BinanceTradeCpp
// * Filename   : DBManager.cpp
// * Description: This file is intentionally left empty.
// * Author     : Onur ŞAHİN (onur25032503@gmail.com)(https://github.com/onur-sahin)
// * Created    : 2024-10-16 02:34 (UTC+3)
// * Updated    : 2024-10-16 02:34 (UTC+3)
// * Version    : 1.0.0
// * Copyright  : Copyright (c) TM_YEAR Onur ŞAHİN
// * License    : MIT License
//                https://opensource.org/licenses/MIT
//                This code is free for use under the MIT license terms.
// *
// * Notes      :
// *             - 
// */

#include <iostream>

#include <cstdlib>   // for system() function
#include <stdexcept>
#include <sys/wait.h>  // for WEXITSTATUS() MACRO

#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "Config.hpp"
#include "DBManager.hpp"
#include "Exceptions.hpp"
#include "Queries.hpp"

#include <nlohmann/json.hpp>

// Initialize static member
DBManager* DBManager::instance = nullptr;

QString DBManager::DBName;
QString DBManager::DBUser;
QString DBManager::DBHost;
QString DBManager::DBPort;
QString DBManager::DBPassword;

QList<QSqlDatabase> DBManager::connectionPool_;
QMutex DBManager::mutex_;

DBManager::DBManager() {
}

DBManager::~DBManager() {
}

DBManager* DBManager::getInstance() {
    // If no instance exists, create it
    if (instance == nullptr) {
        instance = new DBManager();
    }
    return instance;
}

void DBManager::checkPostgresqlInstallation() {
    static const filesystem::path PATH_REL_CHECK_POSTGRESQL_INSTALLATION_SH
        = filesystem::path("share") / "scripts" / "check_postgresql_installation.sh";

    filesystem::path filePath = Config::get_instance()->get_current_working_dir();
    filePath = filePath.parent_path().parent_path() / PATH_REL_CHECK_POSTGRESQL_INSTALLATION_SH;

    int ret = system(filePath.c_str());
    int exit_value = WEXITSTATUS(ret);

    if (exit_value == 0) {
        qDebug() << "Postgresql is available";
    } else if (exit_value == 127) {
        qDebug() << "File not found: " << filePath.c_str() << "Error Code: " << exit_value;
        throw std::ios_base::failure("File not found");
    } else {
        qDebug() << "Error executing bash script. Error Code: " << exit_value << " from: " << filePath.c_str();
        throw std::runtime_error("Error executing bash script");
    }
}

void DBManager::initializeDatabase() {
    checkPostgresqlInstallation();
}

void DBManager::test_database_connection(const QString &database, const QString &user,
                                          const QString &host, const QString &port,
                                          const QString &password) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port.toInt());
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Cannot open DATABASE: " << db.lastError().text();
        throw std::runtime_error(db.lastError().text().toStdString());
    }

    db.close();
}

void DBManager::save_database_connection_settings(const QString database, const QString user,
                                                  const QString host, const QString port,
                                                  const QString password) {
    test_database_connection(database, user, host, port, password);

    DBName = database;
    DBUser = user;
    DBHost = host;
    DBPort = port;
    DBPassword = password;
}

QSqlDatabase DBManager::get_connection() {

    QMutexLocker locker(&mutex_);

    std::cout << "database Connection count: " << connectionPool_.count() << std::endl;
    
    // Eğer connection pool boş değilse, son bağlantıyı al
    if (!connectionPool_.isEmpty()) {

        QSqlDatabase db = connectionPool_.takeLast();

        if (db.isOpen()) {
            return db;
        }
    }

    // Benzersiz bir bağlantı adı oluştur
    QString uniqueConnectionName = "qt_sql_default_connection_" + QString::number(QDateTime::currentMSecsSinceEpoch());

    // Veritabanı bağlantısını oluştur
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", uniqueConnectionName);
    db.setHostName(DBHost);
    db.setPort(DBPort.toInt());
    db.setDatabaseName(DBName);
    db.setUserName(DBUser);
    db.setPassword(DBPassword);

    // Bağlantıyı aç ve kontrol et
    if (!db.open()) {
        qDebug() << "Cannot open database: " << db.lastError().text();
        throw std::runtime_error(db.lastError().text().toStdString());
    }

    return db;
}





void DBManager::releaseConnection(QSqlDatabase &db) {

    QMutexLocker locker(&mutex_);

    if (db.isOpen()) {
        db.close();
        connectionPool_.append(db);
    } else {
        qDebug() << "Attempted to release a closed database connection!";
    }
    std::cout << "database Connection count: " << connectionPool_.count() << std::endl;
}



void DBManager::insert_klines(const QString &table_name, const nlohmann::json &parsed_json){

    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open!";
        releaseConnection(db);
        throw std::runtime_error("Database connection not open");
    }

    QSqlQuery query(db);

    // Sorguyu hazırlama
    if (!query.prepare(Queries::insert_kline.arg(table_name))) {
        qDebug() << "Query preparation error: " << query.lastError().text();
        releaseConnection(db);
        throw std::runtime_error("Query preparation failed: " + query.lastError().text().toStdString());
    }

    for (const auto &row : parsed_json) {

        query.bindValue(0, QVariant::fromValue(std::stoll(row[0].dump()))); // open_time
        query.bindValue(1, QVariant::fromValue(std::stof(row[1].get<std::string>())));  // open
        query.bindValue(2, QVariant::fromValue(stof(row[2].get<std::string>())));  // high
        query.bindValue(3, QVariant::fromValue(stof(row[3].get<std::string>())));  // low
        query.bindValue(4, QVariant::fromValue(stof(row[4].get<std::string>())));  // close
        query.bindValue(5, QVariant::fromValue(stof(row[5].get<std::string>())));  // volume
        query.bindValue(6, QVariant::fromValue(stoll(row[6].dump()))); // close_time
        query.bindValue(7, QVariant::fromValue(stof(row[7].get<std::string>())));  // qav
        query.bindValue(8, QVariant::fromValue(stof(row[8].dump())));  // num_trades
        query.bindValue(9, QVariant::fromValue(stof(row[9].get<std::string>())));  // taker_base_vol
        query.bindValue(10,QVariant::fromValue(stof(row[10].get<std::string>()))); // taker_quoto_vol


        if (!query.exec()) {
            qDebug() << "Query execution error: " << query.lastError().text();
            releaseConnection(db);

            throw DatabaseTableCreationException(
                "Couldn't execute query, \nquery text: " + query.lastQuery().toStdString() + "\n" +
                "Error: " + query.lastError().text().toStdString() + "\n"
            );
        }

    }

    releaseConnection(db);

}

QVector<qint64> DBManager::select_open_time(const QString table_name, const qint64 startTs, const qint64 endTs){

    QVector<qint64> result;

    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open!";
        releaseConnection(db);
        throw std::runtime_error("Database connection not open");
    }

    QSqlQuery query(db);

    // Sorguyu hazırlama
    if (!query.prepare(Queries::select_open_time.arg(table_name))) {
        qDebug() << "Query preparation error: " << query.lastError().text();
        releaseConnection(db);
        throw std::runtime_error("Query preparation failed: " + query.lastError().text().toStdString());
    }

    query.bindValue(":startTs", startTs);
    query.bindValue(":endTs",   endTs);

    // Sorguyu çalıştırma
    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        releaseConnection(db);

        throw DatabaseException(
            "Couldn't execute query, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    while ( query.next() ){
        result.append(query.value(0).toLongLong());  //qlonglong ile qint64 aynı türdür
    }

    return result;

}

void DBManager::execute_query(const QString &query_text, const QVariantMap &bind_values) {
    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open!";
        releaseConnection(db);
        throw std::runtime_error("Database connection not open");
    }

    QSqlQuery query(db);

    // Sorguyu hazırlama
    if (!query.prepare(query_text)) {
        qDebug() << "Query preparation error: " << query.lastError().text();
        releaseConnection(db);
        throw std::runtime_error("Query preparation failed: " + query.lastError().text().toStdString());
    }

    // Bind value ekleme
    for (auto it = bind_values.begin(); it != bind_values.end(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    // Sorguyu çalıştırma

    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        releaseConnection(db);

        throw DatabaseException(
            "Couldn't execute query, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    releaseConnection(db);
}

QVariantList DBManager::execute_query_result(const QString &query_text, const QVariantMap &bind_values) {
    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open!";
        releaseConnection(db);
        throw std::runtime_error("Database connection not open");
    }

    QSqlQuery query(db);

    // Sorguyu hazırlama
    if (!query.prepare(query_text)) {
        qDebug() << "Query preparation error: " << query.lastError().text();
        releaseConnection(db);
        throw std::runtime_error("Query preparation failed: " + query.lastError().text().toStdString());
    }

    // Bind value ekleme
    for (auto it = bind_values.begin(); it != bind_values.end(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    // Sorguyu çalıştırma
    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError().text();
        releaseConnection(db);

        throw DatabaseException(
            "Couldn't execute query, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    // Sonuçları almak için bir liste oluştur
    QVariantList results;

    // Sonuçları listeye ekleme
    while (query.next()) {

        QVariantMap row;

        for (int i = 0; i < query.record().count(); ++i) {
            row.insert(query.record().fieldName(i), query.value(i));
        }
        results.append(row);
    }

    releaseConnection(db);
    return results;
}


void DBManager::create_klines_table(const QString table_name) {
    // CREATE BINANCE DATA TABLE

    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open for table creation!";
        releaseConnection(db);
        // return false;
    }

    QSqlQuery query(db);

    QString queryCreateKlineTable = R"(
                            CREATE TABLE IF NOT EXISTS %1 (
                            open_time BIGINT PRIMARY KEY,
                            open FLOAT4 NOT NULL,
                            high FLOAT4 NOT NULL,
                            low  FLOAT4 NOT NULL,
                            close FLOAT4 NOT NULL,
                            volume FLOAT4 NOT NULL,
                            close_time BIGINT NOT NULL,
                            qav FLOAT4 NOT NULL,
                            num_trades FLOAT4 NOT NULL,
                            taker_base_vol FLOAT4 NOT NULL,
                            taker_quoto_vol FLOAT4 NOT NULL)
                        )";

    queryCreateKlineTable = queryCreateKlineTable.arg(table_name);

    if (!query.exec(queryCreateKlineTable)) {
        qDebug() << "Table creation error: " << query.lastError().text();
        releaseConnection(db);

        throw DatabaseTableCreationException(
            "Couldn't create a table, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    releaseConnection(db);
}

QPair<qint64, qint64> DBManager::get_min_max_ts(const QString &table_name){
    QString query = R"(
                        SELECT MIN(open_time) AS min_open_time, MAX(open_time) AS max_open_time
                            FROM %1;
                       )";

    QVariantList list = execute_query_result(query.arg(table_name), QVariantMap());

    QVariantMap map = list.at(0).toMap();

    return  QPair<qint64, qint64>(map.value("min_open_time").toLongLong(),
                                  map.value("max_open_time").toLongLong());

}

void DBManager::ensure_tables_exists() {

    // Bağlantı al
    QSqlDatabase db = get_connection();

    // Bağlantı kontrolü
    if (!db.isOpen()) {
        qDebug() << "Connection not open for table creation!";
        releaseConnection(db);
        // return false;
    }

    // CREATE ACCOUNT TABLE
    QSqlQuery query(db);
    QString createAccountTable = R"(CREATE TABLE IF NOT EXISTS tbl_accounts (

                                account_name VARCHAR PRIMARY KEY,
                                account_type VARCHAR NOT NULL,
                                api_key      VARCHAR NOT NULL,
                                api_secret   VARCHAR NOT NULL)
                        )";

    if (!query.exec(createAccountTable)) {
        qDebug() << "Table creation error: " << query.lastError().text();
        releaseConnection(db);
        throw DatabaseTableCreationException(
            "Couldn't create a table, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    // CREATE NEUROL NETWORK MODEL TABEL

    QString createModelTable = R"(CREATE TABLE IF NOT EXISTS tbl_models (
                                model_name VARCHAR PRIMARY KEY,
                                model_type character varying NOT NULL,
                                default_pair character varying NOT NULL,
                                default_interval character varying NOT NULL,
                                window_size integer NOT NULL
                            )
                        )";


    if (!query.exec(createModelTable)) {
        qDebug() << "Table creation error: " << query.lastError().text();
        releaseConnection(db);
        throw DatabaseTableCreationException(
            "Couldn't create a table, \nquery text: " + query.lastQuery().toStdString() + "\n" +
            "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    QString createNeurolNetworkTable = R"(CREATE TABLE IF NOT EXISTS tbl_neurol_networks (
                                     model_name VARCHAR PRIMARY KEY,
                                     network_name VARCHAR NOT NULL,
                                     bytea_object BYTEA NOT NULL,
                                     CONSTRAINT fk_model_name FOREIGN KEY (model_name)
                                     REFERENCES tbl_models (model_name)
                                     ON DELETE CASCADE
                                     ON UPDATE CASCADE)
    )";

    if (!query.exec(createNeurolNetworkTable)) {
        qDebug() << "Table creation error: " << query.lastError().text();
        releaseConnection(db);
        
    throw DatabaseTableCreationException(
        "Couldn't create a table, \nquery text: " + query.lastQuery().toStdString() + "\n" +
        "Error: " + query.lastError().text().toStdString() + "\n"
        );
    }

    releaseConnection(db);

    
}



