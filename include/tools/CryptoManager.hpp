/*
* Project    : BinanceTradeCpp
* Filename   : PasswordManager.hpp
* Description: This header file defines the CryptoManager class, responsible for managing 
*              cryptographic operations like encryption and decryption using AES-256. 
*              The class loads a 32-byte encryption key from a file and provides methods 
*              to encrypt and decrypt plaintext and ciphertext, respectively. 
*              The encryption process ensures secure data handling, while the class 
*              structure keeps key management separated and modular for ease of use.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-21 23:30 (UTC+3)
* Updated    : 2024-10-21 23:30 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      : 
*              - The key file must contain at least 32 bytes for AES-256 encryption.
*              - This class is designed for secure handling of sensitive data 
*                like passwords or private information.
*/

#pragma once

class QString;


class CryptoManager {
public:
    CryptoManager(const QString &keyFile);
    QString encrypt(const QString &plaintext);
    QString decrypt(const QString &ciphertext);

private:
    unsigned char m_key[32]; // 32-byte key for AES-256
    void handleErrors();
    void loadKey(const QString &keyFile);
};

