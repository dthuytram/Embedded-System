/*
 * led 2 -> 11
 * biến trở chân giữa A0, 2 chân ngoài nối GND và 5V
 * nút bấm 1 chân nối chân 12 và điện trở nối GND. Chân còn lại nối 5V
 */
int bt = A0;
int led[5][2] = {{2, 11},{3, 10},{4, 9},{5, 8},{6, 7}};
int n = sizeof(led) / sizeof(led[0]);
int m = 0;
int i = 0;
int j;
int k = 1;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i <= n; i++) {
    for(int j = 0; j < 2; j++){
      pinMode(led[i][j], OUTPUT);
    }
  }
  pinMode(12,INPUT);
}
void loop() {
  int button = digitalRead(12);
  Serial.println(button);
  if(button == 1){
    k = -k;
  }
  i = (i+n)%n;
  
  for(j = m; j < 2; j++){
    digitalWrite(led[i][j], HIGH);
  }
  //delay(500);
  delay(analogRead(bt));
  for(j = m; j < 2; j++){
    digitalWrite(led[i][j], LOW);
  }
  i += k;
}
