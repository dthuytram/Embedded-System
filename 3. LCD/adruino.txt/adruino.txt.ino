#include<LiquidCrystal.h>
#include <DHT.h>
LiquidCrystal lcd(12,11,6,5,4,3);
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int a=1;
int dem =0;
int tg1=0;
int tg2 = 0;
int tg3 = 3000;
int trangthai=1;
int nhietdotheo =1;
int tt1  =0;
int tt2 = 0;
void setup() {
 Serial.begin(9600);
 dht.begin();
 pinMode(8,INPUT);
 pinMode(2,OUTPUT);
 lcd.begin(16,2);
// lcd.print("chao ban");
}
void loop(){
  if (trangthai%2==1){
    lcd.display();
    digitalWrite(2,LOW);
//    digitalWrite(9,HIGH);
    float t = dht.readTemperature();
    Serial.print("tem=");
    Serial.print(t);
    delay(1000);
  if(nhietdotheo%2==1){
    lcd.setCursor(4,0);
    lcd.print("ND ");
     lcd.print(t);
     lcd.print("C");
  }
  else{
    lcd.setCursor(4,0);
    lcd.print("ND ");
    float ngu = (9*t/5)+32;
    lcd.print(ngu);
    lcd.print("F");
  } 
  }
  else{
    lcd.noDisplay();
    digitalWrite(2,HIGH);
//digitalWrite(9,LOW);
  }
  tt1 = digitalRead(8);
  if(tt1 != tt2){
    if(tt1==1){
      tt2=tt1;
    Serial.println(tt1);
    nhietdotheo++;
    if (tg1 == tg2){
      tg1 = millis();
      Serial.println(tg1);
    }
    else{
      tg2 = millis();
      Serial.println("tg2");
      Serial.print(tg2);
      if(tg2-tg1<tg3){
        trangthai++;
        tg1=tg2;
      }
      else{
      tg1=tg2;
      tg2=0;
      }
    }
    }
    else tt2=tt1;
    }
  
}
