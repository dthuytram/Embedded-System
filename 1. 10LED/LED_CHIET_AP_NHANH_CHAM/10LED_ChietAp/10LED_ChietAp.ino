int leds[] = {2,3,4,5,6,7,8,9,10,11};
int N = sizeof(leds)/sizeof(leds[0]);
void setup() {
  Serial.begin(9600);
  for (int i=0; i<N; i++) {
    pinMode(leds[i], OUTPUT);
    }
    

}

void loop() {
  // put your main code here, to run repeatedly:
//  int s = analogRead(0);
//  int speed = map(s, 0,1023, 1000,100);
  for (int i = 0; i<N; i++) {
    int s = analogRead(0);
    int speed = map(s, 0,1023, 1000,100);
    digitalWrite(leds[i], HIGH);
    delay(speed);
    digitalWrite(leds[i], LOW);
    Serial.println(s);
    }
    for (int i = N-1; i>0; i--) {
      int s = analogRead(0);
  int speed = map(s, 0,1023, 1000,100);
    digitalWrite(leds[i], HIGH);
    delay(speed);
    digitalWrite(leds[i], LOW);
    Serial.println(s);
    }
}
