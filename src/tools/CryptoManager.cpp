/*
* Project    : BinanceTradeCpp
* Filename   : CryptoManager.cpp
* Description: This implementation file provides the actual functionality for the 
*              CryptoManager class defined in the header. It uses OpenSSL's AES-256-CBC 
*              encryption/decryption algorithms to securely transform plaintext into encrypted 
*              data and vice versa. The loadKey function loads the encryption key from a file, 
*              while the encrypt and decrypt methods handle the cryptographic operations.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin) (onur25032503@gmail.com)
* Created    : 2024-10-22 04:33 (UTC+3)
* Updated    : 2024-10-22 04:33 (UTC+3)
* Version    : 1.0.0
* Copyright  : Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      : 
*              - The encryption key is stored in a private member variable and must be at 
*                least 32 bytes for AES-256 encryption.
*              - Hexadecimal encoding is used to present encrypted data in a readable format.
*              - Error handling is performed using fatal error reporting to ensure 
*                robustness in cryptographic operations.
*/




#include <QDebug>
#include <QFile>
#include <QString>

#include <openssl/evp.h>   // `EVP_CIPHER_CTX`, `EVP_EncryptInit_ex`, `EVP_DecryptInit_ex` gibi OpenSSL şifreleme işlemleri için
#include <openssl/rand.h>  // Gerekirse anahtar oluşturmak gibi rastgele veri işlemleri için (bu kodda doğrudan kullanılmamış, ancak potansiyel olarak gerekli)

#include "CryptoManager.hpp"

CryptoManager::CryptoManager(const QString &keyFile) {
    loadKey(keyFile); // Load the encryption key from the file
}

void CryptoManager::loadKey(const QString &keyFile) {
    QFile file(keyFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qFatal("Could not open key file."); // Fatal error if the file can't be opened
    }
    
    QByteArray keyData = file.readAll();
    if (keyData.size() < 32) {
        qFatal("Key must be at least 32 bytes long for AES-256."); // Ensure the key is long enough for AES-256
    }
    
    memcpy(m_key, keyData.data(), 32); // Copy the key data into the member variable (m_key)
}

QString CryptoManager::encrypt(const QString &plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // Create a new encryption context
    unsigned char ciphertext[128];
    int len;
    int ciphertext_len;

    // Initialize AES-256-CBC encryption with the key (m_key)
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, m_key, NULL);

    // Encrypt the plaintext and store the result in ciphertext
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.toUtf8().data(), plaintext.length());
    ciphertext_len = len;

    // Finalize the encryption (padding, if needed)
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx); // Clean up the encryption context

    // Convert the encrypted data to a hexadecimal string to make it readable
    QString hexCiphertext;
    for (int i = 0; i < ciphertext_len; i++) {
        hexCiphertext.append(QString::number(ciphertext[i], 16).rightJustified(2, '0')); // Append hex values to the string
    }
    return hexCiphertext; // Return the encrypted data as a hex string
}

QString CryptoManager::decrypt(const QString &ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new(); // Create a new decryption context
    unsigned char decryptedtext[128];
    int len;
    int decryptedtext_len;

    // Convert the hex string back to its byte form
    QByteArray byteArray = QByteArray::fromHex(ciphertext.toUtf8());

    // Initialize AES-256-CBC decryption with the key (m_key)
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, m_key, NULL);

    // Decrypt the ciphertext and store the result in decryptedtext
    EVP_DecryptUpdate(ctx, decryptedtext, &len, (unsigned char*)byteArray.data(), byteArray.size());
    decryptedtext_len = len;

    // Finalize the decryption (removes padding if present)
    EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len);
    decryptedtext_len += len;

    EVP_CIPHER_CTX_free(ctx); // Clean up the decryption context
    
    decryptedtext[decryptedtext_len] = '\0'; // Null-terminate the decrypted string
    return QString::fromUtf8(reinterpret_cast<char*>(decryptedtext), decryptedtext_len); // Return the decrypted plaintext
}

void CryptoManager::handleErrors() {
    // Handle errors during encryption or decryption
    qFatal("An error occurred during the encryption/decryption process.");
}



// EXAMPLE USAGE

// #include <QCoreApplication>
// #include <QDebug>
// #include "CryptoManager.hpp"

// int main(int argc, char *argv[]) {
//     QCoreApplication a(argc, argv);

//     QString keyFile = "key.bin"; // Anahtar dosyasının yolu
//     CryptoManager cryptoManager(keyFile);

//     QString plaintext = "Hello, OpenSSL!";
//     QString encryptedText = cryptoManager.encrypt(plaintext);
//     qDebug() << "Encrypted text (hex):" << encryptedText;

//     QString decryptedText = cryptoManager.decrypt(encryptedText);
//     qDebug() << "Decrypted text:" << decryptedText;

//     return a.exec();
// }


