#include <MFRC522.h>
#include <Servo.h>
#include <SPI.h>

#define RST_PIN 9
#define SS_PIN 10
#define SERVO_PIN 8

int Gled = 7;
int Rled = 6;

Servo motor;
MFRC522 rfid(SS_PIN, RST_PIN); 

byte ID[4] = {0,0,0,0}; #Enter your card ID

void setup() {
  motor.attach(SERVO_PIN);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(kled, OUTPUT);
  pinMode(yled, OUTPUT);
  digitalWrite(yled, HIGH);
  digitalWrite(kled, HIGH);
  Serial.println("System ready...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  if (rfid.uid.uidByte[0] == ID[0] &&
      rfid.uid.uidByte[1] == ID[1] &&
      rfid.uid.uidByte[2] == ID[2] &&
      rfid.uid.uidByte[3] == ID[3]) {
    Serial.println("Door Open!");
    ekranaYazdir();
    motor.write(90);
    digitalWrite(yled, LOW);
    digitalWrite(kled, HIGH);
    delay(3000);
    motor.write(0);
    digitalWrite(yled, HIGH);
    digitalWrite(kled, HIGH);
    delay(1000);
  } else {
    Serial.println("Wrong Card!");
    digitalWrite(yled, HIGH);
    digitalWrite(kled, LOW);
    ekranaYazdir();
    delay(3000);
    digitalWrite(yled, HIGH);
    digitalWrite(kled, HIGH);
  }

  rfid.PICC_HaltA();  // Kartı durdur
}

void ekranaYazdir() {
  Serial.print("ID No: ");
  for (int sayac = 0; sayac < rfid.uid.size; sayac++) {
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println();
}
