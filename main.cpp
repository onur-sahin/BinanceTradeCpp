/*
* Project    : BinanceTradeCpp
* Filename   : main.cpp
* Description: This file is intentionally left empty.
* Author     : Onur ŞAHİN (https://github.com/onur-sahin)
* Email      : onur25032503@gmail.com
* Created    : 2024-10-16 01:19 (UTC+3)
* Updated    : 2024-10-16 01:19 (UTC+3)
* Version    : 1.0
*
* Copyright (c) 2024 Onur ŞAHİN
* License    : MIT License
               https://opensource.org/licenses/MIT
               This code is free for use under the MIT license terms.
*
* Notes      :
*             - 
*
* This software is licensed under the MIT License.
* You may obtain a copy of the license at https://opensource.org/licenses/MIT
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/



#include "AppCoord.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages) {
        const QString baseName = "BinanceTradeCpp_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    AppCoord *coordinator = new AppCoord();

    coordinator->startApplication();

    return app.exec();

}
