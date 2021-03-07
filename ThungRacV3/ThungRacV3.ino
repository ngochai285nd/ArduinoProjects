//The Wrench
#include <SD.h>
#include <TMRpcm.h>
#define SD_ChipSelectPin 4
#include <Servo.h>
Servo servo1, servo2;
TMRpcm tmrpcm;
/*
  CS   ------------ >> 4
  SCK  ------------ >> 13
  MOSI ------------ >> 11
  MISO ------------ >> 12
  VCC  ------------ >> + 5v
  GND  ------------ >> GND
*/
int Relay = 8;

int trigPin = A0;
int echoPin = A1;

int servo1Pin = 2;
int servo2Pin = 3;
int hongNgoai = 5;

long duration, dist;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(Relay, OUTPUT);
  pinMode(hongNgoai, INPUT);

  for (int i = servo1.read(); i >= 0; i--) {
    servo1.write(i);
    delay(25);
  }

  for (int i = servo2.read(); i <= 150 ; i++) {
    servo2.write(i);
    delay(25);
  }
  servo1.detach();
  servo2.detach();

  tmrpcm.speakerPin = 9;

  if (!SD.begin(SD_ChipSelectPin)) {
    return;
  }
  tmrpcm.setVolume(6);
  digitalWrite(Relay, LOW);
}

void measure() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;
}

double distance() {
  double aver[3];
  for (int i = 0; i <= 2; i++) {
    measure();
    aver[i] = dist;
    delay(50);
  }
  return (aver[0] + aver[1] + aver[2]) / 3.0;
}

void loop() {
  if (distance() < 50 ) {
    tmrpcm.setVolume(6);
    tmrpcm.play("1.wav");
    delay(6500);
    servo1.attach(servo1Pin);
    for (int i = servo1.read(); i <= 90; i++) {
      servo1.write(i);
      delay(25);
    }
    bool flag = false;
    for (int i = 1; i <= 15; i++) {
      while (digitalRead(hongNgoai) == 0) {
        servo2.attach(servo2Pin);
        delay(1);
        for (int i = servo2.read(); i >= 90; i--) {
          servo2.write(i);
          delay(25);
        }
        flag = true;
        delay(7000);
      }
      servo2.attach(servo2Pin);
      delay(1);
      for (int i = servo2.read(); i <= 150 ; i++) {
        servo2.write(i);
        delay(25);
      }
      if (flag == true) {
//        tmrpcm.play("2.wav");
//        delay(2500);
      }
      servo2.detach();
      flag = false;
      delay(1000);
    }
    for (int i = servo1.read(); i >= 0; i--) {
      servo1.write(i);
      delay(25);
    }
    servo1.detach();
    tmrpcm.play("3.wav");
    delay(2500);
    //    digitalWrite(Relay, HIGH);
    //    delay(30000);
    //    digitalWrite(Relay, LOW);
    
    
  }
}
