/*
 - Công tắc trượt:
    + 2 chân ngoài 1 cái nối VCC 1 cái nối GND
    + Chân giữa nối Pin2
    - nhiệt độ : pin 4;
    - lcd : SCL : a5
            SDA : a4
 */
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
//int  nutbam =8;
int ct= 8;
int value;
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
  //pinMode(8,INPUT);
  pinMode(ct, INPUT);
  value = digitalRead(ct);
  lcd.init();  
  lcd.backlight();
  
  lcd.createChar(1, degree);

  HT.begin(); 
   
}

void loop() {
  //int v= digitalRead(nutbam);
  int value1 = digitalRead(ct);
  //Serial.println(v);
  //float h = HT.readHumidity();
  float t = HT.readTemperature();
  lcd.setCursor(0,0);

  if (isnan(t)) { // Kiểm tra xem thử việc đọc giá trị có bị thất bại hay không. Hàm isnan bạn xem tại đây http://arduino.vn/reference/isnan

  } 
  else {
    if(value != value1)
    {
    lcd.print("Do C: ");
    lcd.print(round(t));
    lcd.print(" C");
    }
    else   
    {
    lcd.print("Do F: ");
    lcd.print(round(t*1.8+32));
    lcd.print(" F"); 
    }   
  }
}
