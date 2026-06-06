# pisayisi

Pi sayısının basamaklarını kullanarak zamana bağlı tek kullanımlık şifre (OTP) üreten terminal uygulaması.

## Nasıl çalışır

Her 20 saniyede bir, Unix zaman damgasından türetilen bir indeks hesaplanır. Bu indeksteki 6 pi basamağı [api.pi.delivery](https://api.pi.delivery) üzerinden çekilir ve aktif şifre olarak gösterilir. Aynı anda çalışan iki istemci her zman aynı kodu görür.

## Bağımlılıklar

- gcc
- libcurl

Fedora:
```
sudo dnf install gcc libcurl-devel
```

Ubuntu:
```
sudo apt install gcc libcurl4-openssl-dev
```

## Derleme ve çalıştırma

```
make
./pisayisi
```

Çıkmak için `q` tuşuna basın.

## Dosyalar

| Dosya | Açıklama |
|---|---|
| pisayisi.c | Ana program |
| kbhit.c | Non-blocking klavye okuma |
| kbhit.h | Kütüphane arayüzü |
| Makefile | Derleme |
| kbhitsizpisayisi.c | kütüphane oluşturulmadan önceki projenin ilk hali |

## Notlar

Bu bir güvenlik aracı değil. Pi basamakları herkese açık olduğundan üretilen kodlar tahmin edilebilr. kedim birşeyler deneme amacı ile yazıldım.
