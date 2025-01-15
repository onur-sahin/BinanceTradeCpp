

#include <cstdlib>      // for system() function
#include <fstream>      // for ifstream to read from file
#include <iostream>     // for std::cout and std::cerr
#include <unistd.h>     // for POSIX API (e.g., fork, exec)
#include <QDebug>

#include "Config.hpp"
#include "utils.hpp"

Config::Config(){
}

// TODO: işaretçi yerine referans döndürmeye çevrilecek
Config *Config::get_instance(){
        static Config *instance = new Config();
        return instance;
}


void Config::initialize(){


    Config *config    = Config::get_instance();

    currentWorkingDir = utils::get_current_working_dir();
    configJsonPath    = currentWorkingDir.parent_path() / PATH_REL_CONFIG_JSON;
    versionJsonPath   = currentWorkingDir.parent_path() / PATH_REL_VERSION_JSON;
    userJsonPath      = currentWorkingDir.parent_path() / PATH_REL_USERS_JSON;
    userDatPath       = currentWorkingDir.parent_path() / PATH_REL_USER_DAT;
    databaseDatPath   = currentWorkingDir.parent_path() / PATH_REL_DATABASE_DAT;
    logsFilePath      = currentWorkingDir.parent_path() / PATH_REL_LOGS_FILE;


    // loading version.json file
    ifstream json_file(versionJsonPath);

    if ( !json_file.is_open() ){
        std::cerr << "version.json dosyası açılamadı! in Config::initialize() " << std::endl;
        return;
    }

    if (json_file.peek() == std::ifstream::traits_type::eof() ){
        qDebug() << "version.json file is empty! in Config::Initialize()";
        return;
    }

    json_file >> version_json_data;

    if (version_json_data.contains("version") ){
        projectVersion = version_json_data["version"];
    }else{
        std::cerr << "version bilgisi JSON  dosyasında bulunamadı!" << std::endl;
    }



    // loading config.json file
    json_file.open(configJsonPath);

    if ( !json_file.is_open() ){
        qDebug() << "JSON dosyası açılamadı!";
        return;
    }

    if (json_file.peek() == std::ifstream::traits_type::eof() ){
        qDebug() << "config.json file is empty! in Config::Initialize()";
        return;
    }

    

    // TODO: json_file boş olduğunda yada json yapısında bir dizi içermediğinde hata veriyor bu düzeltilecek. Hata yukarda biryerde yakalanacak*/
    json_file >> version_json_data;

    if (version_json_data.contains("version") ){
        projectVersion = version_json_data["version"];
    }else{
        qDebug() << "version bilgisi JSON  dosyasında bulunamadı!";
    }


}
