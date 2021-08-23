#include <Regexp.h>
int led[] = {3, 5, 6};
int tmp[255];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 0);
  }
  tmp['R'] = 3; // đỏ
  tmp['G'] = 6; // xanh
  tmp['Y'] = 5; // vàng

}
void action(char* command) {
  String s(command);
  char ledName = s[0];
  int brightness = s.subst,ring(1).toInt();
  analogWrite(tmp[ledName], brightness);
  Serial.println(command);
}
void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    String command = Serial.readString();
        char* c = command.c_str();
        char* param;
        param = strtok(c, ", ");
        while (param != NULL) {
          action(param);
          Serial.println("----------");
          param = strtok(NULL, ", ");
        }
  }
}
