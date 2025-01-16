#pragma once

#include <QDebug>
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <string>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string * out){
    size_t totalSize = size*nmemb;
    out->append((char*)contents, totalSize);
    return totalSize;
};


string fetchBinanceHistoricalData(const std::string &symbol, const std::string &interval, long startTime, long endTime){
    std::string baseUrl = "https://api.binance.com/api/v3/klines";

    std::string url = baseUrl + "?symbol=" + symbol + "&interval=" + interval +
                      "&startTime=" + std::to_string(startTime) + "&endTime=" + std::to_string(endTime);

    std::string responseString;

    CURL *curl = curl_easy_init();

    if(curl){

        curl_easy_setopt(curl, CURLOPT_URL,           url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &responseString);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {

            QString msg = "cURL error: " + QString(curl_easy_strerror(res));

            qDebug() << msg;
            curl_easy_cleanup(curl);
            throw std::runtime_error(msg.toStdString());
        }



    } else {
        curl_easy_cleanup(curl);
        string msg = "Failed to initialize cURL.";
        throw std::runtime_error(msg);
    }

    curl_easy_cleanup(curl);
    return responseString;
};