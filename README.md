# ESP32 Web Server ve Motor Kontrol Projesi ESP32 Kodları

## Proje Özeti

- **Amaç**: Motorları uzaktan kontrol etmek, mesafe ölçmek ve bir buzzer ile ses çıkarmak.
- **Kullanılan Teknolojiler**: 
  - ESP32 Wi-Fi modülü
  - L298N motor sürücüsü
  - Ultrasonik mesafe sensörü
  - Buzzer

## Nasıl Çalışıyor:
  Python kodu üzerinden web soket haberleşme ile gönderilen bilgileri alarak ve bu bilgileri işleyerek geerekli komutu çalıştırır ve işler.

## Donanım Gereksinimleri

### Malzemeler

- 1 x ESP32 Geliştirme Kartı
- 1 x L298N Motor Sürücü Kartı
- 2 x DC Motor
- 1 x Ultrasonik Mesafe Sensörü (HC-SR04)
- 1 x Buzzer
- Jumper kabloları

### Bağlantılar

| Cihaz               | ESP32 Pin   |
|---------------------|-------------|
| Sağ Motor Enable 1  | D8          |
| Sağ Motor Enable 2  | D9          |
| Sağ Motor In 1      | D6          |
| Sağ Motor In 2      | D7          |
| Sol Motor Enable 1  | D13         |
| Sol Motor Enable 2  | D12         |
| Sol Motor In 1      | D14         |
| Sol Motor In 2      | D15         |
| Üst Motor Enable    | D0          |
| Üst Motor In 1      | D1          |
| Üst Motor In 2      | D4          |
| Ultrasonik Trig     | D10         |
| Ultrasonik Echo     | D11         |
| Buzzer              | D5          |

## Yazılım Gereksinimleri

- **Arduino IDE**: ESP32 kütüphanelerinin yüklü olduğu bir IDE kullanmalısınız. [Arduino IDE İndir](https://www.arduino.cc/en/software)

## Kurulum

1. **Wi-Fi Ayarları**: `ssid` ve `password` değişkenlerini kendi ağınıza göre düzenleyin:

   ```cpp
   const char* ssid = "WifiAdı";      // Wi-Fi adı
   const char* password = "Şifre"; // Wi-Fi şifresi
   ```

2. **Kütüphaneleri Yükleyin**:

   ESP32 ve WebServer kütüphanelerinin yüklü olduğundan emin olun.
   
2. **Kodu ESP32 Ye Yükleyin**:

   Arduino IDE'de kodu açın ve ESP32'ye yükleyin.

3. **Seri Monitörü Açın**:

   115200 baud hızında ayarlayın. Wi-Fi bağlantısı kurulduktan sonra IP adresi görüntülenecektir.

## Kullanım
  Proje çalıştığında, ESP32 web sunucusu başlatılır ve kullanıcılar web tarayıcıları üzerinden motorları kontrol edebilirler.

##  Web Sunucusu
  Web sunucusu, belirli komutları ESP32'ye gönderen HTTP POST isteklerini işler. Komutlar aşağıdaki gibidir:
  - LEFT: Sol motorun yönünü ve hızını ayarlar.                                                    ```LEFT(<rotation>,<speed>)```
  - RIGHT: Sağ motorun yönünü ve hızını ayarlar.                                                   ```RIGHT(<rotation>,<speed>)```
  - BackAndForth: Her iki motoru ileri veya geri hareket ettirir.                                  ```BackAndForth(<rotation>,<speed>)```
  - 2BackAndForth: Her iki motoru ileri veya geri ayrı ayrı güçlerde hareket ettirir.              ```2BackAndForth(<rightMotorPwm>,<leftMotorPwm>,<rotation>)```
  - 3BackAndForth: Her iki motoru ayrı ayrı ileri veya geri , ayrı ayrı güçlerde hareket ettirir.  ```3BackAndForth(<rightRotation>,<leftRotation>,<rightMotorPwm>,<leftMotorPwm>)```
  - G_Turn: Sağ ve sol motorları farklı yönlerde döndürerek dönüş hareketi sağlar.                 ```G_Turn(<rotation>,<speed>)```
  - Upper: Üst motorun yönünü ve hızını ayarlar.                                                   ```Upper(<rotation>,<speed>)```
  - MEASURE: Ultrasonik sensör ile mesafe ölçümü yapar.                                            ```MEASURE()```
  - BUZZER: Buzzer ile melodik ses çıkarır.                                                        ```BUZZER()```
    

## HTTP POST İstek Örnekleri
  - Sol Motor İleri: LEFT,1,255 (1: İleri, 255: Maksimum hız)
  - Sağ Motor Geri: RIGHT,0,200 (0: Geri, 200: Hız)
  - İleri-Geri Hareket: BackAndForth,1,150 (İleri yönde 150 hızında)
  - Mesafe Ölçümü: MEASURE

## Buzzer Fonksiyonu
Buzzer ile çalınan melodi, pitches.h dosyasında tanımlanan nota frekanslarına dayanmaktadır. 
Buzzer, farklı melodilerle kullanıcılara sesli geri bildirim sağlar.


