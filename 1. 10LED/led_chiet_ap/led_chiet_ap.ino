/*
 * led 2 -> 11
 * Biến trở chân giữa nối A0, 2 chân ngoài nối GND và 5V.
 */
int bt = A0;
int led[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int n = sizeof(led) / sizeof(led[0]);
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < n; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 0);
  }
}
void loop() {
  for (int i = 0; i < n; i++) {
    digitalWrite(led[i], 1);
    delay(analogRead(bt));
    digitalWrite(led[i], 0);
  }
  for (int i = n - 1; i > 0; i--) {
    digitalWrite(led[i], 1);
    delay(analogRead(bt));
    digitalWrite(led[i], 0);
  }
}
