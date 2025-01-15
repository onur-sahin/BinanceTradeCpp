/*
* Project    : BinanceTradeCpp
* Filename   : utils.hpp
* Description: header file for usefull functions in utils.cpp
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-20 01:36 (UTC+3)
* Updated    : 2024-10-20 01:36 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#pragma once

#include <QMap>
#include <QPoint>
#include <QString>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;


namespace utils{

std::filesystem::path get_current_working_dir();

// read and write nlohmann::json objects from/to json file
nlohmann::json read_from_json_file_nlohmann(const string &filePath);
void write_to_json_file_nlohmann(const nlohmann::json &json_data, const std::string &filePath);

// read and write QMap objects from/to json file
QMap<QString, QString> read_QMap_from_json_file(const QString &filePath);
QMap<QString, QString> read_QMap_from_json_file(const std::string &filePath);


void append_QMap_to_json_file(const QMap<QString, QString> &qmapList, const QString &filePath);

QPoint get_screen_center();


}; // namespace utils