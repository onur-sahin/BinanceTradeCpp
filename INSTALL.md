# Installation Instructions

Varsayılan olarak home dizini altına kurulmaktadadır.
Program ismi home dizini altınada "BinanceTradeCpp" şeklinde görünecektir.
Programla ilgili tüm dosya, klasör ve loglar BinanceTradeCpp klasörünün içindedir.
Tüm dosyalar tek klasörde olduğundan BinanceTradeCpp kalasörü modülerdir, kopyalanarak istenilen konuma taşınabilir, sistem klasör ve dosyalarından bağımsızdır.

## AppImage
AppImage klasöründe ayrıca bir appImage dosyası bulunmaktadır. Bu dosyayı çalıştırmak için bilgisayarda sadece postgresql veritabanı yönetim sisteminin kurulu olması gerekmektedir. Diğer tüm kütüphaneler static olarak linklendiğinden, hepsi binary dosyasının içine gömülüdür.

## Gereksinimler

- CMake (v3.10 or higher)
- g++ 13 or higher (or another compiler)
- Qt 6 (v6.2 or higher recommended)
- curl
- Required libraries:
   - absent

- libraries embedded in the binary file (for information only, no need to install or download)
   - nlohmann/json

## Installing Dependencies

Linux (Debian/Ubuntu-based):
```bash
sudo apt-get install cmake qt6-base-dev
sudo apt-get install libcurl4-openssl-dev

```

## Programın Çalıştırılması
Program kurulduktan sonra executable dosyasını çalıştırmak için iki yöntem aşağıda verilmiştir.
### Birinci Yöntem
terminalde
```bash
cd ~/BinanceTradeCpp/<version>/bin
```
dizinine girip bin dizinindeki BinanceTradeCpp binary dosyası
```bash
./BinanceTradeCpp
```
komutuyla çalıştırılabilir.
### İkinci Yöntem
BinanceTradeCpp klasöründe bulunan istenilen versiyon numarasına sahip executable dosyaya çift tıklanabilir.

