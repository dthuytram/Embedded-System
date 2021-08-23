/*
 - Nut bam:
    + 1 chân nối VCC 1 nối dien tro qua GND va noi Pin2
    + Chân giữa nối Pin2
 - nhiệt độ : pin 4;
 - lcd : 
      + SCL : a5
      + SDA : a4
  - dien tro: 
      + chan giua noi V0 cua LCD
      + 
 */
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int  nutbam = 2;
int value = 0; 
int a=1;
int dem =0;
int tg1=0;
int tg2 = 0;
int tg3 = 2000;
int trangthai=1;
int nhietdotheo =1;
int tt1  =0;
int tt2 = 0;
#define  DHT11Pin 4
#define DHTType DHT11
DHT HT(DHT11Pin,DHTType);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,    
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  Serial.begin(9600);
  pinMode(nutbam,INPUT);
  lcd.init();  
  
  lcd.createChar(1, degree);

  HT.begin(); 
   
}

void loop(){
  lcd.setCursor(0,0);//tạo độ con trỏ
  if (trangthai%2==1){
    lcd.backlight();//Dùng để bật đèn nền của lcd
    lcd.display()
    float t = HT.readTemperature();
  if(nhietdotheo%2==1){
//    lcd.setCursor(4,0);
    lcd.print("Do C: ");
    lcd.print(round(t));
    lcd.print(" C");
  }
  else{
//    lcd.setCursor(4,0);
    lcd.print("Do F: ");
    lcd.print(round(t*1.8+32));
    lcd.print(" F"); 
  } 
  }
  else{
    lcd.noBacklight();//Dùng để tat đèn nền của lcd
    lcd.noDisplay(); //Tăt màn hình hiển thị
  }
  tt1 = digitalRead(nutbam);
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


//void loop() {
//  int v = digitalRead(nutbam);
//  Serial.println(v);
//  float t = HT.readTemperature();
//  if(check(v) == 1){
//    value = abs(value - 1);
//  }
//  lcd.setCursor(0,0);//tạo độ con trỏ
//
//  if (isnan(t)) { // Kiểm tra xem thử việc đọc giá trị có bị thất bại hay không. Hàm isnan bạn xem tại đây http://arduino.vn/reference/isnan
//
//  } 
//  else {
//    if(value == 0)
//    {
//    lcd.print("Do C: ");
//    lcd.print(round(t));
//    lcd.print(" C");
//    }
//    else   
//    {
//    lcd.print("Do F: ");
//    lcd.print(round(t*1.8+32));
//    lcd.print(" F"); 
//    }   
//  }
//  delay(300);
//}
//
//int check( int v){
//  if(v == 1){
//    return 1;
//  }
//  else{
//    return 0;
//  }
//}
