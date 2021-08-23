#include <SPI.h>
#include <SD.h>
#include <DHT.h> 
File file1;
const int DHTPIN = 9;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
const int chipSelect = 10;
void setup() {
  Serial.begin(9600);
  Serial.print("Khởi tạo thẻ SD...");
  dht.begin();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print(t);
  if (!SD.begin(chipSelect)) {
    Serial.println("Không thành công!");
    return;
  }
  Serial.println("Khởi tạo thành công.");

  file1 = SD.open("BAI6.txt", FILE_WRITE);

  if (file1) {
    Serial.print("ghi du lieu test.txt...");
    file1.print("NHiệt độ :");
    file1.print(t);
    file1.println("C");
    file1.print("Độ ẩm :");
    file1.println(h);
    file1.close();
    Serial.println("Ok");
  } else {
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
