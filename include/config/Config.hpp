/*
* Project    : BinanceTradeCpp
* Filename   : Config.hpp
* Description: header of static functions for version.json anda config.json
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-20 01:38 (UTC+3)
* Updated    : 2024-10-20 01:38 (UTC+3)
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

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;

class Config{

private:

    filesystem::path PATH_REL_CONFIG_JSON          = filesystem::path("share/config.json");
    filesystem::path PATH_REL_VERSION_JSON         = filesystem::path("share/version.json");
    filesystem::path PATH_REL_USERS_JSON           = filesystem::path("share/users.json");
    filesystem::path PATH_REL_USER_DAT             = filesystem::path("share/keys/database.dat");
    filesystem::path PATH_REL_DATABASE_DAT         = filesystem::path("share/keys/user.dat");
    filesystem::path PATH_REL_LOGS_FILE            = filesystem::path("share/logs.log");

    filesystem::path  currentWorkingDir;
    filesystem::path  configJsonPath;
    filesystem::path  versionJsonPath;
    filesystem::path  userJsonPath;
    filesystem::path  userDatPath;
    filesystem::path  databaseDatPath;
    filesystem::path  logsFilePath;

    string            projectVersion;
    nlohmann::json    version_json_data;
    nlohmann::json    config_json_data;


public:

    Config();

    static Config *get_instance();
    void           initialize();

    const std::string       &get_project_version    () const {return projectVersion;}
    const filesystem::path  &get_current_working_dir() const {return currentWorkingDir;}
    const filesystem::path  &get_config_json_path   () const {return configJsonPath;}
    const filesystem::path  &get_version_json_path  () const {return versionJsonPath;}
    const filesystem::path  &get_user_json_path     () const {return userJsonPath;}
    const filesystem::path  &get_user_dat_path      () const {return userDatPath;}
    const filesystem::path  &get_database_dat_path  () const {return databaseDatPath;}
    const filesystem::path  &get_logs_file_path     () const {return logsFilePath;}


private:

    //Kopyalama ve atama işlemleri yasaklanır
    Config(const Config &)            = delete;
    Config &operator=(const Config &) = delete;

};