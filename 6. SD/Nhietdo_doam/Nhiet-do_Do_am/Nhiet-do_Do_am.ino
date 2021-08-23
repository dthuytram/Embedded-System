


#include<SD.h>
#include<SPI.h>
#include <RTClib.h>
RTC_DS1307 rtc;
int trigPin = 7;                                                    //ultrasonic-sensor trigger pin is connected to IO 7
int echoPin = 6;                                                    //ultrasonic-sensor echo pin is connected to IO 6
float roundTrip;                                                    //round-trip-time (RTT)
float distance2target;

const int CS = 10; //chip select
//uint32_t id = 577652; //this number will need to be long
String filename = "TESTCASE.txt";

void setup()
{
   while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  } // end rtc.begin()

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));  
  }    
  SD.begin(CS);  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(10,OUTPUT);                                               //reserve IO 10 as an output - this is required by the SD.h library
   

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(15);

  roundTrip = pulseIn(echoPin,HIGH);  
  
  //measure RTT in microseconds
  distance2target = roundTrip *0.034/2 ;
  
  Serial.begin(9600);
  if (!SD.begin(CS))
  {
    Serial.println("Card not loaded");
  }
  else
  {
    Serial.println("Card ready");
  }
  File datafile = SD.open(filename, FILE_WRITE);
  Serial.print("File found?"); Serial.println(datafile);
  
  if (datafile)
  {
    DateTime now = rtc.now();
    datafile.println("");
    datafile.print(now.year(), DEC);
    datafile.print('/');
    datafile.print(now.month(), DEC);
    datafile.print('/');
    datafile.print(now.day(), DEC);
    datafile.print(',');
    datafile.print(now.hour(), DEC);
    datafile.print(':');
    datafile.print(now.minute(), DEC);
    datafile.print(':');
    datafile.print(now.second(), DEC);
    datafile.print(",");
    datafile.print(distance2target);
    datafile.close();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(',');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(",");
    Serial.print(distance2target);
   
  }
  else
  {
    Serial.println("Couldn't save the number");
  }
}
void loop()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(15);

  roundTrip = pulseIn(echoPin,HIGH);  
  //measure RTT in microseconds
  distance2target = roundTrip *0.034/2;
  
  SD.remove(filename); 
  File datafile = SD.open(filename, FILE_WRITE);
  if (datafile)
  {
    DateTime now = rtc.now();
    datafile.println("");
    datafile.print(now.year(), DEC);
    datafile.print('/');
    datafile.print(now.month(), DEC);
    datafile.print('/');
    datafile.print(now.day(), DEC);
    datafile.print(',');
    datafile.print(now.hour(), DEC);
    datafile.print(':');
    datafile.print(now.minute(), DEC);
    datafile.print(':');
    datafile.print(now.second(), DEC);
    datafile.print(",");
    datafile.print(distance2target);

    Serial.println("");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(',');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(",");
    Serial.print(distance2target);
  }
  datafile.close();

  delay(1000);
//
//  Serial.println("+++++++++");
//  Serial.println("Reading from SD Card");
//  File readfile = SD.open(filename, FILE_READ);
//  while (readfile.available()) {
//    char c = readfile.read();
//    Serial.print(c);
//  }
//  readfile.close();
//  Serial.println("\nSD Card read complete");
//  Serial.println("========");

//
//   Serial.print(readfile.read());
//   
}
