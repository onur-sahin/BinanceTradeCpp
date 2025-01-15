/*
* Project    : BinanceTradeCpp
* Filename   : utils.cpp
* Description: includes usefull functions
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-20 01:35 (UTC+3)
* Updated    : 2024-10-20 01:35 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/


#include "utils.hpp"

#include <climits> // PATH_MAX
#include <cstring> // strerror
#include <filesystem>
#include <system_error> // std::system_error
#include <unistd.h>     // getcwd

namespace utils {

std::filesystem::path get_current_working_dir() {
    char buffer[PATH_MAX];  // Buffer to store the current working directory

    // Use getcwd() to retrieve the current working directory
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::filesystem::path(buffer);  // Return as filesystem::path

    }
    // In case of error, throw a system_error with a descriptive message
    throw std::system_error(errno, std::generic_category(), 
                            "Failed to get current working directory: " + std::string(strerror(errno)));
}

}  // namespace utils

#include <cerrno>  // errno için
#include <cstring> // strerror için
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

namespace utils {

nlohmann::json read_from_json_file_nlohmann(const std::string &filePath) {
    
    nlohmann::json json_data;
    std::ifstream json_file(filePath);

    if (!json_file) { // Open failed
        throw std::ios_base::failure("Failed to open file: " + filePath + ". Error: " + std::strerror(errno));
    }

    try {
        json_file >> json_data; // Read JSON data
        if (json_file.fail()) {  // Check for read errors
            throw std::ios_base::failure("Failed to read JSON data from file: " + filePath);
        }
    
    } catch (const nlohmann::json::parse_error &e) {
        throw std::ios_base::failure("JSON parse error: " + std::string(e.what()));
    
    } catch (const std::exception &e) {
        throw std::ios_base::failure("Error reading from file: " + std::string(e.what()));
    }

    return json_data;
}


// JSON verisini dosyaya yazma
void write_to_json_file_nlohmann(const nlohmann::json &json_data, const std::string &filePath) {
    std::ofstream json_file(filePath);

    if (!json_file) { // Dosya açılamadı
        throw std::ios_base::failure("Failed to open file for writing: " + filePath + ". Error: " + std::strerror(errno));
    }

    try {
        json_file << json_data.dump(4); // JSON verisini yaz (4 boşluk ile girintili)
        if (json_file.fail()) { // Yazma hatası kontrolü
            throw std::ios_base::failure("Failed to write JSON data to file: " + filePath);
        }
    } catch (const std::exception &e) {
        throw std::ios_base::failure("Error writing to file: " + std::string(e.what()));
    }
}


}

#include <QDebug> // For qInfo()
#include <QFile>
#include <QFileDevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <stdexcept> // For std::invalid_argument and std::ios_base::failure
#include <string> // For std::string

namespace utils {

// Function to save a QMap to a JSON file
void append_QMap_to_json_file(const QMap<QString, QString>& qmapList, const QString& filePath) {
    QFile file(filePath);

    QJsonObject jsonObject;

    // Dosya mevcutsa ve JSON verisi içeriyorsa, mevcut veriyi yükle
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // Dosya geçerli bir JSON nesnesi içeriyorsa yükle
        if (jsonDoc.isObject()) {
            jsonObject = jsonDoc.object();
        }
        file.close();  // Okuma işlemi tamamlandıktan sonra kapat
    }

    // Yeni QMap verilerini mevcut JSON nesnesine yalnızca anahtar yoksa ekle
    for (auto it = qmapList.constBegin(); it != qmapList.constEnd(); ++it) {
        if (!jsonObject.contains(it.key())) {  // Sadece yeni anahtarları ekle
            jsonObject[it.key()] = it.value().isEmpty() ? "" : it.value();
        }
    }

    // Dosyayı yazma modunda aç
    if (!file.open(QIODevice::WriteOnly)) {
        throw std::ios_base::failure("Failed to open file for writing: " + file.errorString().toStdString());
    }

    // Güncellenmiş JSON nesnesini dosyaya yaz
    QJsonDocument updatedJsonDoc(jsonObject);
    file.write( updatedJsonDoc.toJson() );
    file.close();

}




// Function to read a QMap from a JSON file

QMap<QString, QString> read_QMap_from_json_file(const QString &filePath) {

    QFile file(filePath);

    QMap<QString, QString> qmapList;

    // Attempt to open the file for reading
    if (!file.open(QIODevice::ReadOnly)) {
        // Throw an error if the file cannot be opened, converting QString to std::string
        throw std::ios_base::failure("Failed to open file for reading: " + file.errorString().toStdString());
    }

    QByteArray data = file.readAll();

    // Check if the file is empty
    if (data.isEmpty()) {
        file.close();
        return qmapList;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // Check if the parsed document is a valid JSON object
    if ( !jsonDoc.isObject() ) {
        file.close(); // Close the file before throwing an error
        throw std::invalid_argument("Expected a JSON object but got something else.");
    }

    qInfo() << "Valid JSON object read.";

    // Extract key-value pairs from the JSON object into the QMap
    QJsonObject jsonObject = jsonDoc.object();
    for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
        qmapList.insert(it.key(), it.value().toString());
    }

    file.close(); // Close the file after reading
    return qmapList; // Return the populated QMap
}

QMap<QString, QString> read_QMap_from_json_file(const  std::string &filepath){
    return read_QMap_from_json_file( QString::fromStdString(filepath) );
}

} // namespace utils


#include <QGuiApplication>
#include <QScreen>
#include <QPoint>

namespace utils{

// Ekranın merkez koordinatını döndüren fonksiyon
QPoint get_screen_center() {
    
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        int centerX = screenGeometry.x() + screenGeometry.width() / 2;
        int centerY = screenGeometry.y() + screenGeometry.height() / 2;
        return QPoint(centerX, centerY);
    }
    return QPoint(0, 0); // Eğer ekran alınamazsa (hata durumu)
}

} //namespace utils

