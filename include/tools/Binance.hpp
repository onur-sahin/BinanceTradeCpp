#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string * out){
    size_t totalSize = size*nmemb;
    out->append((char*)contents, totalSize);
    return totalSize;
};


void fetchBinanceHistoricalData(const std::string &symbol, const std::string &interval, long startTime, long endTime){
    std::string baseUrl = "https://api.binance.com/api/v3/klines";

    std::string url = baseUrl + "?symbol=" + symbol + "&interval=" + interval +
                      "&startTime=" + std::to_string(startTime) + "&endTime=" + std::to_string(endTime);

    CURL *curl = curl_easy_init();

    if(curl){
        std::string responseString;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "API Response: " << responseString << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize cURL." << std::endl;
    }

};