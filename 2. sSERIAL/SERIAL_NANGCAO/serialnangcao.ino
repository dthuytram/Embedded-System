
// Không có dấu phẩy, cách trong câu lệnh
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) {
    String inputStr = Serial.readString();
    inputStr.trim();
    splitString(inputStr);  
  }
}

void splitString(String s)
{
  int count = 0; 
  String splited = ""; 
  int i = 0; 
  splited +=s[0]; 
  i++; 
  while (i< s.length())
  {
    while (s[i]>='0' && s[i]<='9')
    {
      splited +=s[i]; 
      i++; 
    }
    display(splited); 
    splited = ""; 
    if (i+1 < s.length())
      splited = s[i++]; 
  }
}

void display(String s)
{
  char color = s[0];
  int value = atoi(&s[1]);

  Serial.print(color);
  Serial.println(value);

   if (s[0] == 'R')
  {
    analogWrite(9, value);
  }
  if (s[0] == 'Y')
  {
    analogWrite(10, value);
  }
  
  if (s[0] == 'G')
  {
    analogWrite(11, value);
  }
  
  
}
