# README in Two Languages: ESP32 Web Server and Motor Control Project ESP32 Codes

- [Türkçe Bölüm](#turkce-bolum)
- [English Section](#english-section)

## Türkçe Bölüm <a id="turkce-bolum"></a>
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

***

<br><br><br><br><br><br><br><br><br><br><br><br><br>

# Prototip
![Kontrol prototip](https://github.com/12enes34/ESP32_With_Python_Remotre_Control/blob/main/Kontrolc%C3%BC.gif)




 
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



# Proje
![Kontrol prototip](https://github.com/12enes34/ESP32_With_Python_Remotre_Control/blob/main/Kontrol.jpg)










<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>


## English Section <a id="english-section"></a>


# ESP32 Web Server and Motor Control Project ESP32 Codes

## Project Summary

- **Purpose**: Remotely control motors, measure distance and make a sound with a buzzer.
- **Technologies Used**:
- ESP32 Wi-Fi module
- L298N motor driver
- Ultrasonic distance sensor
- Buzzer

## How it works:
It receives the information sent via web socket communication via Python code and processes this information and executes and processes the necessary command.

## Hardware Requirements

### Materials

- 1 x ESP32 Development Board
- 2 x L298N Motor Driver Board
- 2 x DC Motor
- 1 x Ultrasonic Distance Sensor (HC-SR04)
- 1 x Buzzer
- Jumper cables

### Connections

| Device | ESP32 Pin |
|---------------------|-------------|
| Right Motor Enable 1 | D8 |
| Right Motor Enable 2 | D9 |
| Right Motor In 1 | D6 |
| Right Motor In 2 | D7 |
| Left Motor Enable 1 | D13 |
| Left Motor Enable 2 | D12 |
| Left Motor In 1 | D14 |
| Left Motor In 2 | D15 |
| Top Motor Enable | D0 |
| Top Motor In 1 | D1 |
| Top Motor In 2 | D4 |
| Ultrasonic Trig | D10 |
| Ultrasonic Echo | D11 |
| Buzzer | D5 |

## Software Requirements

- **Arduino IDE**: You must use an IDE that has the ESP32 libraries installed. [Download Arduino IDE](https://www.arduino.cc/en/software)

## Setup

1. **Wi-Fi Settings**: Edit the `ssid` and `password` variables according to your network:

```cpp
const char* ssid = "WifiName"; // Wi-Fi name
const char* password = "Password"; // Wi-Fi password
```

2. **Install Libraries**:

Make sure that the ESP32 and WebServer libraries are loaded.

2. **Upload Code to ESP32**:

Open the code in Arduino IDE and upload it to ESP32.

3. **Open Serial Monitor**:

Set the baud rate to 115200. The IP address will be displayed after the Wi-Fi connection is established.

## Usage
When the project is running, the ESP32 web server is started and users can control the motors via their web browsers.

## Web Server
The web server processes HTTP POST requests that send specific commands to ESP32. The commands are as follows:
- LEFT: Sets the direction and speed of the left motor. ```LEFT(<rotation>,<speed>)```
- RIGHT: Sets the direction and speed of the right motor. ```RIGHT(<rotation>,<speed>)```
- BackAndForth: Moves both motors forward or backward. ```BackAndForth(<rotation>,<speed>)```
- 2BackAndForth: Moves both motors forward or backward with separate powers. ```2BackAndForth(<rightMotorPwm>,<leftMotorPwm>,<rotation>)```

- 3BackAndForth: Moves both motors separately forward or backward, with separate powers. ```3BackAndForth(<rightRotation>,<leftRotation>,<rightMotorPwm>,<leftMotorPwm>)```

- G_Turn: Provides rotation movement by rotating the right and left motors in different directions. ```G_Turn(<rotation>,<speed>)```

- Upper: Adjusts the direction and speed of the upper motor. ```Upper(<rotation>,<speed>)```

- MEASURE: Measures distance with ultrasonic sensor. ```MEASURE()```
- BUZZER: Makes melodic sound with buzzer. ```BUZZER()```

## HTTP POST Request Examples
- Left Motor Forward: LEFT,1,255 (1: Forward, 255: Maximum speed)
- Right Motor Reverse: RIGHT,0,200 (0: Reverse, 200: Speed)
- Forward-Backward Movement: BackAndForth,1,150 (Forward at 150 speed)
- Distance Measurement: MEASURE

## Buzzer Function
The melody played with the buzzer is based on the note frequencies defined in the pitches.h file.

The buzzer provides audio feedback to users with different melodies.

***

<br><br><br><br><br><br><br><br><br><br><br>

# Prototype
![Control prototype](https://github.com/12enes34/ESP32_With_Python_Remotre_Control/blob/main/Kontrolc%C3%BC.gif)

# ESP32 Web Server and Motor Control Project Python Codes (Controller)

Controls motors via keyboard or joystick with an ESP-based system.
Currently supported joystick is Logitech EXTREME 3D PRO.
The project sends commands to the ESP device using `requests`, `keyboard`, `pygame`, and `threading` libraries.

## Requirements

To run this project, the following software and libraries must be installed:

- Python 3.x
- `requests` library
- `keyboard` library
- `pygame` library

You can use the following commands to install the required libraries:

```bash
pip install requests
pip install keyboard
pip install pygame
```

## Functions

### Motor Control Functions

- control_left_motor(rotation, speed): Controls the left motor.
- control_right_motor(rotation, speed): Controls the right motor.
- back_and_forth(rotation, speed): Motor moves back and forth.
- g_turn(rotation, speed): Turns the motor right or left.
- control_upper_motor(rotation, speed): Controls the upper motor.
- control_right_left_motor(right_motor_pwm, left_motor_pwm, rotation): Controls the right and left motors at the same time.
- control_right_left_motor_with_rotations(right_motor_pwm, left_motor_pwm, RightRotation, LeftRotation): Controls the right and left motors in different directions and speeds.

### Extra Functions
- measure_distance(): Measures distance.
- play_buzzer(): Plays the buzzer melody.

## Motor Control with Keyboard
* t: Forward movement.
* s: Backward movement.
* d: Left rotation.
* a: Right rotation.
* e: Starts the right motor.
* q: Starts the left motor.
* m: Measures distance.
* b: Rings the buzzer.
* r: Fast forward movement.
* f: Stops the motor.
* z: Exits the program.

## Motor Control with Joystick
Motor control can also be provided using the joystick.

Commands can be sent to the motors using the joystick's axes and buttons.

# Usage
- 1 - Connect your ESP 32 and computer to the same network.
- 2 - Edit the esp_ip and esp_port variables at the beginning of the code according to the IP address and port number of your ESP device.
- 3 - Run the Esp32KontrolcuV3_With_joystick.py file
- 4 - If you want to use a joystick, connect the joystick and replace the function in the Thread with control_motors_with_joystick.
if you want to control from keyboard replace the function with control_motors_with_keyboard
```bash
if __name__ == '__main__:
motor_thread = Thread(target=control_motors_with_joystick)
motor_thread.start()
motor_thread.join()
```
while the program is running you can control the motors with the joystick.

# Joystick usage:
You can determine the maximum speed of the vehicle with the throttle opening joystick located under the joystick arm.

You can run the upper motor upwards with the number 1 button on it and downwards with the number 2 button.

The more you push or pull the joystick forward, the more power you can send to the motors.

You can make the device make a point turn from where it is by rotating the joystick on its own axis.

![Logitech EXTREME 3D PRO JOYSTICK IMAGE](https://github.com/12enes34/ESP32_With_Python_Remotre_Control/blob/main/Logitech%20Extreme%203D%20Pro.jpg) # Project ![Control prototype](https://github.com/12enes34/ESP32_With_Pyth on_Remotre_Control/blob/main/Control.jpg)






  
