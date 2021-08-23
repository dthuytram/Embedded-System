
// Xoa dau cach
// Them thoi gian tat den

const int r = 3;
const int g = 5;
const int b = 6;
long at = 0;
int isTurnOff = 0;
long timeOut = 0;
void setup() {
  Serial.begin(9600);
  Serial.flush();
  }



void setLED(char* s) {
  char x = s[0];
  String n = (String) s;
  String ns = n.substring(1);
  int nx = ns.toInt();
//  Serial.println(x);
//  Serial.println(nx);
  if (x == 'R') {

    analogWrite(r, nx);
    
    }
  if (x == 'G') {
    analogWrite(g, nx);}
  if (x == 'B') {
    analogWrite(b, nx);
    }
  if (x == 'T') {
    at = millis();
    isTurnOff = 1;
    timeOut = nx;
    }
  }



 void loop() {
  
  String s = "";
  if (Serial.available()) {
    s = Serial.readString();
//    char* a = ax.c_str();
//    char* parameter;
//    parameter = strtok(a, " ,");
//    while (parameter != NULL) {
//      setLED(parameter);
////      Serial.println(param3eter);
//      parameter = strtok(NULL, " ,");
//      }
    int index = 0;
    int ids[10]; 
    for (int i=0; i<s.length(); i++) {

        if (s[i] == 'R' || s[i] == 'G' || s[i] == 'B' || s[i] == 'T') {
            
            ids[index++] = i;
            
            
        }
       
      }

      for (int i = 0; i<index-1; i++) {

        String st = s.substring(ids[i], ids[i+1]);
        Serial.println(st);
        setLED(st.c_str());
        }
        Serial.println(s.substring(ids[index-1]));
        setLED(s.substring(ids[index-1]).c_str());
    
  
  }
  if (isTurnOff) {
    if (millis() - at >= timeOut) {
      analogWrite(r,0);
      analogWrite(g,0);
      analogWrite(b,0);
    }
    }
 }
