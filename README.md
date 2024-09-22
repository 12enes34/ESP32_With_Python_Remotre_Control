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
- 2 x L298N Motor Sürücü Kartı
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


<br><br><br><br><br><br><br><br><br><br><br><br><br>

***
 
# ESP32 Web Server ve Motor Kontrol Projesi Python Kodları (Kontrolcü)

ESP tabanlı bir sistem ile motorları klavye veya joystick aracılığıyla kontrol eder.
Şu an desteklenen joystick Logitech EXTREME 3D PRO.
Proje, `requests`, `keyboard`, `pygame`, ve `threading` kütüphanelerini kullanarak ESP cihazına komutlar gönderir.

## Gereksinimler

Bu projeyi çalıştırabilmek için aşağıdaki yazılımların ve kütüphanelerin yüklü olması gerekmektedir:

- Python 3.x
- `requests` kütüphanesi
- `keyboard` kütüphanesi
- `pygame` kütüphanesi

Gerekli kütüphaneleri yüklemek için aşağıdaki komutları kullanabilirsiniz:

```bash
pip install requests
pip install keyboard
pip install pygame
```

## Fonksiyonlar

  ### Motor Kontrol Fonksiyonları
  
  - control_left_motor(rotation, speed): Sol motoru kontrol eder.
  - control_right_motor(rotation, speed): Sağ motoru kontrol eder.
  - back_and_forth(rotation, speed): Motoru ileri geri hareket ettirir.
  - g_turn(rotation, speed): Motoru sağa veya sola döndürür.
  - control_upper_motor(rotation, speed): Üst motoru kontrol eder.
  - control_right_left_motor(right_motor_pwm, left_motor_pwm, rotation): Sağ ve sol motorları aynı anda kontrol eder.
  - control_right_left_motor_with_rotations(right_motor_pwm, left_motor_pwm, RightRotation, LeftRotation): Sağ ve sol motorları farklı yön ve hızlarda kontrol eder.


### Ekstra Fonksiyonlar
  - measure_distance(): Mesafe ölçümü yapar.
  - play_buzzer(): Buzzer melodisini çaldırır.

## Klavye ile Motor Kontrolü
* t: İleri hareket.
* s: Geri hareket.
* d: Sol dönüş.
* a: Sağ dönüş.
* e: Sağ motoru çalıştırır.
* q: Sol motoru çalıştırır.
* m: Mesafe ölçümü yapar.
* b: Buzzer'ı çaldırır.
* r: İleri hızlı hareket.
* f: Motoru durdurur.
* z: Programdan çıkar.
  
## Joystick ile Motor Kontrolü
Joystick kullanılarak motor kontrolü de sağlanabilir. 
Joystick'in eksen ve butonları kullanılarak motorlara komut gönderilebilir.

# Kullanım
- 1 - ESP 32 ile bilgisayarinizi ayni ağa bağlayın.
- 2 - Kodun başındaki esp_ip ve esp_port değişkenlerini ESP cihazınızın IP adresi ve port numarasına göre düzenleyin.
- 3 - Esp32KontrolcuV3_With_joystick.py dosyasını çalıştırın
- 4 - Joystick kullanmak istiyorsanız, joystick'i bağlayın ve Thread içinde ki fonksiyonu control_motors_with_joystick ile değiştirin.
    klavyeden kontrol etmek istiyorsanız fonksiyonu control_motors_with_keyboard ile değiştirin
```bash
  if __name__ == '__main__':
    motor_thread = Thread(target=control_motors_with_joystick)
    motor_thread.start()
    motor_thread.join()
```
program çalışırken joystick ile motorları kontrol edebilirsiniz.

# Joystick kullanımı:
  Joystick kolunun altında bulunan gaz açma joystick'i ile aracın max hızını belirleyebilirsiniz.
  
  Üzerinde bulunan 1 numaralı tuş ile upper motoru yukarı yönde çalıştırabilirsiniz 2 ile de aşağı yönde çalıştırabilirsiniz.
  
  Joystick'i ne kadar ileri iter veya geri çekerseniz motorlara o kadar çok güç gönderebilirsiniz.

  Joystick'i kendi ekseninde döndürerek cihazın olduğu yerden nokta dönüşü yapabilmesini sağlayabilirsiniz.


![Logitech EXTREME 3D PRO JOYSTICK IMAGE](https://github.com/12enes34/ESP32_With_Python_Remotre_Control/blob/main/Logitech%20Extreme%203D%20Pro.jpg)






  
