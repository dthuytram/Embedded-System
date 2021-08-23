 /*
Chân RST cắm vào chân số 7 trên Arduino

Chân SDA cắm vào chân số 10 trên Arduino

Chân MOSI cắm vào chân số 11 trên Arduino

Chân MISO cắm vào chân số 12 trên Arduino

Chân SCK cắm vào chân số 13 trên Arduino

Chân 3.3V cắm vào chân số 3.3v trên Arduino

Chân GND cắm vào chân số GND trên Arduino
*/

#include <SPI.h>

#include <MFRC522.h>
#include<Stepper.h>
const int LED1 = 2;

#define SS_PIN 10

#define RST_PIN 7

MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long uidDec, uidDecTemp;

byte bCounter, readBit;

unsigned long ticketNumber;

void setup() {

  pinMode(LED1, OUTPUT);
  
  Serial.begin(9600);
  
  SPI.begin();
  
  mfrc522.PCD_Init();
  
  Serial.println("Hay quet the de hien thi ID...");

}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  
  return 0;
  
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  
  return 0;
  
  }
  
  uidDec = 0;
  
  Serial.println("************************************************");
  
  Serial.println(" ID cua the la: ");
  
  for (byte i = 0; i < mfrc522.uid.size; i++ ) {
  
    uidDecTemp = mfrc522.uid.uidByte[i];
    
    uidDec = uidDec*256+uidDecTemp;
  
  }
  
  Serial.print(" [");
  
  Serial.print(uidDec);
  
  if(uidDec == 167058621){
  
    digitalWrite(LED1, HIGH);
 
  }
 
  
  if(uidDec == 3642690243){
    digitalWrite(LED1, LOW);
  }  
  Serial.println("]"); 
  Serial.println("................................................");
  delay(1000);

}
