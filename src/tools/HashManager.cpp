/*
* Project    : BinanceTradeCpp
* Filename   : HashManager.cpp
* Description: 
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-22 07:39 (UTC+3)
* Updated    : 2024-10-22 07:39 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*/

#include <QByteArray>         // `QByteArray` sınıfı için, `hash` metodu
#include <QCryptographicHash> // SHA-256 hash işlemi için `QCryptographicHash` sınıfı, `hash` metodu
#include <QFile>              // Dosya işlemleri için `QFile` sınıfı, `saveHashToFile` ve `readHashFromFile` metodları
#include <QString>
#include <QTextStream>       // Dosyaya veri yazmak ve okumak için `QTextStream`, `saveHashToFile` ve `readHashFromFile` metodları


#include "HashManager.hpp"

// Hash method implementation
QString HashManager::hash(const QString &input) {
    // Convert the input string to a QByteArray
QByteArray byteArray = ( QString("ZkEW4LUi1wR9VUWxjbRs8n9YS4Ap7z4tTld8") + input).toUtf8();
    
    // Generate the SHA-256 hash
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    
    // Convert the hash to a hexadecimal string
    return hash.toHex();
}

// Save the hash value to a specified file
void HashManager::saveHashToFile(const QString &filePath, const QString &hashValue) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qFatal("Could not open file to save hash.");
    }

    QTextStream out(&file);
    out << hashValue; // Write the hash value to the file
    file.close(); // Close the file
}

// Read the hash value from a specified file
QString HashManager::readHashFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("Could not open file to read hash.");
    }

    QTextStream in(&file);
    QString hashValue = in.readLine(); // Read the hash value from the file
    file.close(); // Close the file
    return hashValue; // Return the hash value
}


// Hash the input string and save the hash value to a specified file
void HashManager::hashAndSaveToFile(const QString &input, const QString &filePath) {
    QString hashValue = hash(input); // Hash the input
    saveHashToFile(filePath, hashValue); // Save the hash value to the file
}




// EXAMPLE USAGE

// #include <QCoreApplication>
// #include <QDebug>
// #include "HashManager.hpp"

// int main(int argc, char *argv[]) {
//     QCoreApplication a(argc, argv);

//     // Use the Singleton instance of HashManager
//     HashManager& hashManager = HashManager::getInstance(); 

//     QString input = "mySecurePassword"; // The string to hash
//     QString hashedValue = hashManager.hash(input); // Get the hash of the input

//     qDebug() << "Input String:" << input; // Print the original string
//     qDebug() << "Hashed Value (SHA-256):" << hashedValue; // Print the hashed value

//     // Save the hashed value to a file
//     QString filePath = "hash.txt"; // Specify the file path
//     hashManager.saveHashToFile(filePath, hashedValue); // Save the hash to the file

//     // Read the hash value back from the file
//     QString readHash = hashManager.readHashFromFile(filePath); // Read the hash from the file
//     qDebug() << "Read Hash from File:" << readHash; // Print the read hash value

//     return a.exec(); // Execute the application
// }
