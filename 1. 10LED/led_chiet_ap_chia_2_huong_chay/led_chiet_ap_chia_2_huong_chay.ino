/*
 * led 2 -> 11
 * biến trở chân giữa A0, 2 chân ngoài nối GND và 5V
 */
int bt = A0;
int led[5][2] = {{2, 11},{3, 10},{4, 9},{5, 8},{6, 7}};
void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= 4; i++) {
    for(int j = 0; j < 2; j++){
      pinMode(led[i][j], OUTPUT);
      digitalWrite(led[i][j], LOW);
    }
  }
}
void loop() {
  int i, j; 
  for (i = 0; i < 5;i++) {
    for(j = 0; j < 2; j++){
      digitalWrite(led[i][j], HIGH);
    }
    delay(analogRead(bt));
    for(j = 0; j < 2; j++){
      digitalWrite(led[i][j], LOW);
    }
  }
  for (i = 4; i > 0; i--) {
    for(j = 0; j < 2; j++){
      digitalWrite(led[i][j], HIGH);
    }
    delay(analogRead(bt));
    for(j = 0; j < 2; j++){
      digitalWrite(led[i][j], LOW);
    }
  }
}
