#pragma once
#include <QString>


class Queries{

public:
    static const QString insert_account;
    static const QString insert_model;
    static const QString insert_kline;

};

const QString Queries::insert_account = R"(
    INSERT INTO tbl_accounts(account_name,  account_type,  api_key,  api_secret)
                    VALUES (:account_name, :account_type, :api_key, :api_secret);
)";


const QString Queries::insert_model = R"(
    INSERT INTO 
)";

const QString Queries::insert_kline = R"(
    INSERT INTO %1 (
        open_time, 
        open, 
        high, 
        low, 
        close, 
        volume, 
        close_time, 
        qav, 
        num_trades, 
        taker_base_vol, 
        taker_quoto_vol
    ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ON CONFLICT (open_time) DO NOTHING

)";



// USAGE:
//     QSqlQuery query;

//     // Sorguyu hazırla
//     query.prepare(Queries::insert_account);

//     // Parametreleri bağla
//     query.bindValue(":account_name", accountName);
//     query.bindValue(":account_type", accountType);
//     query.bindValue(":api_key", apiKey);
//     query.bindValue(":api_secret", apiSecret);