#include <WiFi.h>
#include <WebServer.h>
#include "pitches.h"

// Wi-Fi ayarları
const char* ssid = "Tulpar";
const char* password = "12345687";

// HTTP sunucusu 80 numaralı portta çalışacak
WebServer server(80);

// Right Engine Controller pinout
#define enA D8
#define enA2 D9

#define in1 D6
#define in2 D7

// Left Engine Controller pinout
#define enB D13
#define enB2 D12

#define in3 D14
#define in4 D15

//Upper Engine Controller pinout
#define enC D0
#define in5 D1
#define in6 D4

// Ultrasonic pinout
const int trigPin = D10;
const int echoPin = D11;

// Buzzer pinout
int buzzerPin = D5;

// Engine Controller rotation
const int Rototion = 0;

// Buzzer melody
int melody[] = { NOTE_C5, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, 0, NOTE_B4, NOTE_C5 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  Serial.println("TEST ESP32 den arduinoya");
  // Wi-Fi bağlantısını başlat
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // IP adresini yazdır
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Sunucuyu başlat
  server.begin();
  Serial.println("Server started");

  // Ultrasonic 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Engine Controller Left
  pinMode(enA, OUTPUT);
  pinMode(enA2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Engine Controller Right
  pinMode(enB, OUTPUT);
  pinMode(enB2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //
  pinMode(enC, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  // HTTP isteklerini işleyicilere yönlendirme
  server.on("/", HTTP_POST, handleRoot);
}

void loop() {
  server.handleClient();
}

// HTTP POST isteğini işleyici fonksiyon
void handleRoot() {
  if (server.hasArg("plain") == false) {
    server.send(200, "text/plain", "Body not received");
    return;
  }
  String body = server.arg("plain");
  Serial.println("Received command : " + body);

  // Komutu işleme
  processCommand(body);

  //server.send(200, "text/plain", "Command received");
}

// Komut işleme fonksiyonu
void processCommand(String command) {
  command.trim();

  if (command.startsWith("LEFT")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    if (comma1 != -1 && comma2 != -1) {
      int rotation = command.substring(comma1 + 1, comma2).toInt();
      int speed = command.substring(comma2 + 1).toInt();
      ControllEngineLeft(rotation, speed); // Sol motoru belirtilen hızla hareket ettir
      server.send(200, "text/plain", "Turn Right");
      delay(50);
    }
  } else if (command.startsWith("RIGHT")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    if (comma1 != -1 && comma2 != -1) {
      int rotation = command.substring(comma1 + 1, comma2).toInt();
      int speed = command.substring(comma2 + 1).toInt();
      ControllEngineRight(rotation, speed);
      server.send(200, "text/plain", "Turn Left");

      delay(50);
    }
  } else if (command.startsWith("BackAndForth")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    if (comma1 != -1 && comma2 != -1) {
      int rotation = command.substring(comma1 + 1, comma2).toInt();
      int speed = command.substring(comma2 + 1).toInt();
      Serial.println("Incomming command: " + command + "speed:" + speed + "rotation:" + rotation);
      
      BackAndForth(rotation, speed);
      if(rotation == 1){
        server.send(200, "text/plain", "Go Forward");
      } else {
        server.send(200, "text/plain", "Go Back");
          }
       

      delay(50);
    }
  } else if (command.startsWith("2BackAndForth")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    int comma3 = command.indexOf(',', comma2 + 1);
    
    if (comma1 != -1 && comma2 != -1 && comma3 != -1) {
      int rightMotorPwm = command.substring(comma1 + 1, comma2).toInt();
      int leftMotorPwm = command.substring(comma2 + 1, comma3).toInt();
      int rotation = command.substring(comma3 + 1).toInt();
      Serial.println(String("BackAndFort2: R") + rightMotorPwm + " L " + leftMotorPwm + " r " + rotation);
      BackAndForth2(rotation, rightMotorPwm, leftMotorPwm);
      if(rotation == 1){
        server.send(200, "text/plain", "Go Forward");
      } else {
        server.send(200, "text/plain", "Go Back");
          }
      delay(50);
    }
  } else if (command.startsWith("3BackAndForth")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    int comma3 = command.indexOf(',', comma2 + 1);
    int comma4 = command.indexOf(',', comma3 + 1);

    if (comma1 != -1 && comma2 != -1 && comma3 != -1 && comma4 != -1) {
      int rightMotorPwm = command.substring(comma1 + 1, comma2).toInt();
      int leftMotorPwm = command.substring(comma2 + 1, comma3).toInt();
      int RightRotation = command.substring(comma3 + 1, comma4).toInt();
      int LeftRotation = command.substring(comma4 + 1).toInt();
      Serial.println(String("BackAndFort3: R ") + rightMotorPwm + " L " + leftMotorPwm + " r " + RightRotation + " l " + LeftRotation);
      BackAndForth3(RightRotation, LeftRotation, rightMotorPwm, leftMotorPwm);
      
      if(RightRotation == 1){
        server.send(200, "text/plain", "Go Forward");
      } else {
        server.send(200, "text/plain", "Go Back");
          }
          
      delay(50);
    }
  } else if (command.startsWith("G_Turn")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    if (comma1 != -1 && comma2 != -1) {
      int rotation = command.substring(comma1 + 1, comma2).toInt();
      int speed = command.substring(comma2 + 1).toInt();
      G_Turn(rotation, speed);
      if(rotation == 1){
        server.send(200, "text/plain", "G Turn Right");
      } else {
        server.send(200, "text/plain", "G Turn Left");
          }
      delay(50);
    }
  } else if (command.startsWith("Upper")) {
    int comma1 = command.indexOf(',');
    int comma2 = command.indexOf(',', comma1 + 1);
    if (comma1 != -1 && comma2 != -1) {
      int rotation = command.substring(comma1 + 1, comma2).toInt();
      int speed = command.substring(comma2 + 1).toInt();
      Serial.println("Incomming command: " + command + "speed:" + speed + "rotation:" + rotation);
      ControllUpperEngine(rotation, speed);
      if(rotation == 1){
        server.send(200, "text/plain", "Load Up");
      } else {
        server.send(200, "text/plain", "Load Down");
          }
      delay(50);
    }
  } else if (command.startsWith("MEASURE")) {
    server.send(200, "text/plain", "Distance Measurement");
    measureAndPrintDistance();

  } else if (command.startsWith("BUZZER")) {
    server.send(200, "text/plain", "Buzzer Ring On");
    BuzzerSong();
    
  }

  // Komut işlendikten sonra durdur
  stopEngines();
}

// Sol motor kontrol fonksiyonu
void ControllEngineLeft(int Rotation, int speedValue) {
  analogWrite(enB, speedValue); // Send PWM signal to L298N Enable pin
  analogWrite(enB2, speedValue);
  if (Rotation) {
    Serial.println("Work");
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

// Sağ motor kontrol fonksiyonu
void ControllEngineRight(int Rotation, int speedValue) {
  analogWrite(enA, speedValue); // Send PWM signal to L298N Enable pin
  analogWrite(enA2, speedValue);
  if (Rotation) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

// Her iki motoru ileri geri hareket ettirme fonksiyonu
void BackAndForth(int Rotation, int speedValue) {
  if (Rotation) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, speedValue);
    analogWrite(enA2, speedValue);
    analogWrite(enB, speedValue);
    analogWrite(enB2, speedValue);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, speedValue);
    analogWrite(enA2, speedValue);
    analogWrite(enB, speedValue);
    analogWrite(enB2, speedValue);
  }
}

// Üç motoru ileri geri hareket ettirme fonksiyonu
void BackAndForth2(int Rotation, int RightSpeed, int LeftSpeed) {
  if (Rotation) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, RightSpeed);
    analogWrite(enA2, RightSpeed);
    analogWrite(enB, LeftSpeed);
    analogWrite(enB2, LeftSpeed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, RightSpeed);
    analogWrite(enA2, RightSpeed);
    analogWrite(enB, LeftSpeed);
    analogWrite(enB2, LeftSpeed);
  }
}

// Üç motoru bağımsız ileri geri hareket ettirme fonksiyonu
void BackAndForth3(int RightRotation, int LeftRotation, int RightSpeed, int LeftSpeed) {
  if (RightRotation) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, RightSpeed);
    analogWrite(enA2, RightSpeed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, RightSpeed);
    analogWrite(enA2, RightSpeed);
  }

  if (LeftRotation) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, LeftSpeed);
    analogWrite(enB2, LeftSpeed);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, LeftSpeed);
    analogWrite(enB2, LeftSpeed);
  }
}

void ControllUpperEngine(int Rotation, int speedValue) {
  analogWrite(enC, speedValue);
  if (Rotation) {
    Serial.println("Work upper");
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
  } else {
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
  }
}

// Motorları durdurma fonksiyonu
void stopEngines() {
  analogWrite(enA, 0);
  analogWrite(enA2, 0);
  analogWrite(enB, 0);
  analogWrite(enB2, 0);
  analogWrite(enC, 0);
}

void measureAndPrintDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void BuzzerSong() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

void G_Turn(int rotation, int speedValue) {
  // Sağ motor ileri
  analogWrite(enA, speedValue);
  analogWrite(enA2, speedValue);
  if (rotation) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  // Sol motor geri
  analogWrite(enB, speedValue);
  analogWrite(enB2, speedValue);
  if (rotation) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}
