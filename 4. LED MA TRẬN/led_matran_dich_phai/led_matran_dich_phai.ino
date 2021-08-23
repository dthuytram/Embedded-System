const int DATA = 12;// pin 12 của Arduino nối với pin DATA của 74HC595
const int CLOCK = 10;//pin 10 của Arduino nối với pin CLOCK của 74HC595
const int LATCH = 11;//pin 11 của Arduino nối với pin LATCH của 74HC595
/* hàng và cột của LED matrix*/
unsigned int row[] = {1, 2, 4, 8, 16, 32, 64, 128};
unsigned int column[] = {128, 64, 32, 16, 8, 4, 2, 1};
/*biểu diễn các ký tự chữ và số ở dạng HEX*/
unsigned int characterHEX[][8] = {
{0x18,0x3C,0x66,0x66,0x7E,0x66,0x66,0x66},//A
{0x78,0x64,0x68,0x78,0x64,0x66,0x66,0x7C},//B
{0x3C,0x62,0x60,0x60,0x60,0x62,0x62,0x3C},//C
{0x78,0x64,0x66,0x66,0x66,0x66,0x64,0x78},//D
{0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x7E},//E
{0x7E,0x60,0x60,0x7C,0x60,0x60,0x60,0x60},//F
{0x3C,0x62,0x60,0x60,0x66,0x62,0x62,0x3C},//G
{0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x66},//H
{0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x7E},//I
{0x7E,0x18,0x18,0x18,0x18,0x18,0x1A,0x0C},//J
{0x62,0x64,0x68,0x70,0x70,0x68,0x64,0x62},//K
{0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x7E},//L
{0xC3,0xE7,0xDB,0xDB,0xC3,0xC3,0xC3,0xC3},//M
{0x62,0x62,0x52,0x52,0x4A,0x4A,0x46,0x46},//N
{0x3C,0x66,0x66,0x66,0x66,0x66,0x66,0x3C},//O
{0x7C,0x62,0x62,0x7C,0x60,0x60,0x60,0x60},//P
{0x38,0x64,0x64,0x64,0x64,0x6C,0x64,0x3A},//Q
{0x7C,0x62,0x62,0x7C,0x70,0x68,0x64,0x62},//R
{0x1C,0x22,0x30,0x18,0x0C,0x46,0x46,0x3C},//S
{0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18},//T
{0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x3C},//U
{0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x18},//V
{0x81,0x81,0x81,0x81,0x81,0x99,0x99,0x66},//W
{0x42,0x42,0x24,0x18,0x18,0x24,0x42,0x42},//X
{0xC3,0x66,0x3C,0x18,0x18,0x18,0x18,0x18},//Y
{0x7E,0x02,0x04,0x08,0x10,0x20,0x40,0x7E},//Z
{0x3C,0x66,0x66,0x6E,0x76,0x66,0x66,0x3C},//0
{0x18,0x38,0x58,0x18,0x18,0x18,0x18,0x7E},//1
{0x3C,0x66,0x66,0x0C,0x18,0x30,0x7E,0x7E},//2
{0x7E,0x0C,0x18,0x3C,0x06,0x06,0x46,0x3C},//3
{0x0C,0x18,0x30,0x6C,0x6C,0x7E,0x0C,0x0C},//4
{0x7E,0x60,0x60,0x7C,0x06,0x06,0x46,0x3C},//5
{0x04,0x08,0x10,0x38,0x6C,0x66,0x66,0x3C},//6
{0x7E,0x46,0x0C,0x18,0x18,0x18,0x18,0x18},//7
{0x3C,0x66,0x66,0x3C,0x66,0x66,0x66,0x3C},//8
{0x3C,0x66,0x66,0x36,0x1C,0x08,0x10,0x20},//9
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},// khoảng trắng
{0x00,0x66,0xFF,0xFF,0x7E,0x3C,0x18,0x00}// hình trái tim, kí hiệu là '&'
};
/* ký tự đại diện để biểu diễn chữ và số trên matrix*/
char character[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' ','&'};
void setup()
{
  Serial.begin(9600);// Serial với baudrate 9600
  /* 3 pins DATA, CLOCK, LATCH cần phải để OUTPUT*/
  pinMode(DATA,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(LATCH,OUTPUT);
  /* in ra cổng Serial "ENTER A STRING"*/
  Serial.println("ENTER A STRING");
}
/* hàm nhấp nháy chữ*/
/* image là ký tự cần hiển thị,
   times là số lần nhấp nháy,
   on, off là độ dài của hiệu ứng*/
void blinkImage(unsigned int image[],int times,int on,int off)
{
  for(int i=0;i<times;i++)
  {
    displayImage(image,on);// hiển thị
    
    clearImage(off);// xóa  
  }
}
/*hàm hiển thị chữ lên LED matrix*/
/* image là ký tự cần hiển thị,
   duration là độ dài của hiệu ứng*/
void displayImage(unsigned int image[],int duration)
{
  for(int hold=0;hold<duration;hold++)
  {
    for(int a=0;a<8;a++)
    {
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, LSBFIRST,~image[a]);//column
      shiftOut(DATA, CLOCK, LSBFIRST,row[a]);//row
      digitalWrite(LATCH, HIGH);
      delay(1);
    }
  }
}
/* hàm clear LED matrix*/
/* duration là độ dài của hiệu ứng clear*/
void clearImage(int duration)
{
  for(int hold=0;hold<duration;hold++)
  {
    for(int a=0;a<8;a++)
    {
      digitalWrite(LATCH, LOW);
      shiftOut(DATA, CLOCK, MSBFIRST,0B00000000);//column
      shiftOut(DATA, CLOCK, MSBFIRST,row[a]);//row
      digitalWrite(LATCH, HIGH);
      delay(1);
    }
  }
}
/*hàm scroll image sang phải*/
/* image là ký tự cần hiển thị*/
void scrollImage(unsigned int image[])
{
  int shift, hold, a;//biến shift dùng để lưu số bit cần shiftOut
                     //biến hold dùng để điều chỉnh độ dài của hiệu ứng
                     //biến a dùng để lưu column và row hiện tại
  for(shift = 0; shift < 9; shift++)
  {
    for(hold = 0; hold < 30; hold++)
    {
      for(a = 0; a < 8; a++)
      {
        digitalWrite(LATCH, 0);
        /* dịch ký tự sang trái*/
        shiftOut(DATA,CLOCK,MSBFIRST,~(image[a]<<shift));//column
        shiftOut(DATA,CLOCK,MSBFIRST,row[a]);//row
        digitalWrite(LATCH, 1);
        delay(1);
      }
    }
  }
  
}
void scrollImage(unsigned int image[])
{
  int shift, hold, a;//biến shift dùng để lưu số bit cần shiftOut
                     //biến hold dùng để điều chỉnh độ dài của hiệu ứng
                     //biến a dùng để lưu column và row hiện tại
  for(shift = 0; shift < 9; shift++)
  {
    for(hold = 0; hold < 30; hold++)
    {
      for(a = 0; a < 8; a++)
      {
        digitalWrite(LATCH, 0);
        /* dịch ký tự sang trái*/
        shiftOut(DATA,CLOCK,MSBFIRST,~(image[a]>>shift));//column
        shiftOut(DATA,CLOCK,MSBFIRST,row[a]);//row
        digitalWrite(LATCH, 1);
        delay(1);
      }
    }
  }
  
}
void loop()
{
   String string;// khai báo biến String object
   /* đọc dữ liệu từ cổng Serial */
   while(Serial.available() > 0)
   {
     char ch = Serial.read();
     string += ch;// lưu ký tự vừa nhận được vào biến string
     delay(5);// delay để đợi ký tự tiếp theo, KHÔNG THỂ THIẾU
   }
   Serial.println(string);// in string ra Serial monitor
   /* hiển thị ra LED matrix */
   while(Serial.available() == 0)
   {
     /*so sánh từng phần tử của string với 
     các ký tự đã được lưu trong mảng character[].
     Nếu ký tự xuất hiện trong string tồn tại 
     trong mảng character[] thì hiển thị ra LED matrix,
     nếu không tồn tại thì báo "invalid character"*/
     for(int k = 0;k < string.length();k++)
     {
       for(int i=0;i < sizeof(character);i++)
       {
         if(string.charAt(k) == character[i])
         {
           //bỏ "//" nếu muốn sử dụng hàm blinkImage()
           //blinkImage(characterHEX[i],1,30,30);
           scrollImage(characterHEX[i]);
           break;
         }
         /* nếu ko tồn tại ký tự xuất hiện trong string*/
         if((i == (sizeof(character) - 1)) && (string.charAt(k) != character[i]))
         {
           Serial.print(string.charAt(k));
           Serial.println(":invalid character");
         }
       }
       /*kiểm tra xem có dữ liệu mới hay không*/
       if(Serial.available() > 0)
       break;
     }
     delay(30);
   }
}
