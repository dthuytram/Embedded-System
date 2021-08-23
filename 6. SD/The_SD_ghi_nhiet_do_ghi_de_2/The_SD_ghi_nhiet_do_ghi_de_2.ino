/*
 * Cảm biến DHT11: - chân Data nối Pin7
 *                 - chân GND nối GND
 *                 - chân VCC nối 5V
 * Đồng hồ IC: - GND-GND
 *             - VCC-VCC
 *             - SDA - CHÂN  SỐ A4
 *             - SCL - chân số  A5
 * Thẻ nhớ: - CS -chaand  số 4
 *          -  SCK- chân số 13
 *          - MOSI-chân  số 11
 *          - MISO-  chân số 12 
 */
  
#include <SPI.h> //for the SD card module
#include <SD.h> // for the SD card
#include <DHT.h> // for the DHT sensor
#include <RTClib.h> // for the RTC

//define DHT pin
#define DHTPIN 7     // what pin we're connected to

// uncomment whatever type you're using
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

// change this to match your SD shield or module;
// Arduino Ethernet shield and modules: pin 4
// Data loggin SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 10; 

// Create a file to store the data
String filename = "DATA.txt";
File myFile;

// RTC
RTC_DS1307 rtc;

void setup() {
  //initializing the DHT sensor
  dht.begin();

  //initializing Serial monitor
  Serial.begin(9600);
  
  // setup for the RTC
  while(!Serial); // for Leonardo/Micro/Zero
    if(! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
    else {
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if(! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
    }
    
  // setup for the SD card
  Serial.print("Initializing SD card...");

  if(!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    
  //open file
  myFile=SD.open(filename, FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    myFile.println("Date,Time,Temperature ºC");
  }
  myFile.close();
}

void loop() {
  loggingTime();
//  loggingTemperature();
  delay(5000);
}

void loggingTime() {
  SD.remove(filename);
  DateTime now = rtc.now();
  float t = dht.readTemperature();
  if  (isnan(t) /*|| isnan(f)*/) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  myFile = SD.open(filename, FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.println("Temperature: ");
    myFile.print(t);
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  myFile.close();
//  delay(1000);  
}

//void loggingTemperature() {
//  // Reading temperature or humidity takes about 250 milliseconds!
//  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  // Read temperature as Celsius
//  float t = dht.readTemperature();
//  // Read temperature as Fahrenheit
//  //float f = dht.readTemperature(true);
//  
//  // Check if any reads failed and exit early (to try again).
//  if  (isnan(t) /*|| isnan(f)*/) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
//  
//  //debugging purposes
//  Serial.print("Temperature: "); 
//  Serial.print(t);
//  Serial.println(" *C");
//  //Serial.print(f);
//  //Serial.println(" *F\t"); 
//
//  SD.remove(filename); 
//  myFile = SD.open(filename, FILE_WRITE);
//  if (myFile) {
//    Serial.println("open with success");
//    myFile.print(t);
//    myFile.println(",");
//  }
//  myFile.close();
//}
