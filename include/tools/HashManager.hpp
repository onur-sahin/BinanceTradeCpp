/*
* Project    : BinanceTradeCpp
* Filename   : HashManager.hpp
* Description: -
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-22 07:33 (UTC+3)
* Updated    : 2024-10-22 07:33 (UTC+3)
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

class QString;

class HashManager {
public:
    // Get the single instance of HashManager
    static HashManager& get_instance() {
        static HashManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Method to hash a given input string using SHA-256
    QString hash(const QString &input);

    // Method to save the hash value to a file
    void saveHashToFile(const QString &filePath, const QString &hashValue);

    // Method to read the hash value from a file
    QString readHashFromFile(const QString &filePath);

    // Method to hash a given input string and save it to a file
    void hashAndSaveToFile(const QString &input, const QString &filePath);

private:
    // Private constructor to prevent instantiation
    HashManager() = default;

    // Delete copy constructor and assignment operator
    HashManager(const HashManager&) = delete;
    HashManager& operator=(const HashManager&) = delete;
};