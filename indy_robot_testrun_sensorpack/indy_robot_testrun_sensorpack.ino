#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP3008.h>

Adafruit_MCP3008 adc;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define PWML  5  //   motor L
#define IN1L  4  //  
#define IN2L  9  //

#define PWMR  6  //   motor R
#define IN1R  8  //  
#define IN2R  7  //


const int buttonPin = 2;

int adcValue_0 = 0;
int adcValue_1 = 0;
int adcValue_2 = 0;
int adcValue_3 = 0;
int adcValue_4 = 0;
int adcValue_5 = 0;
int adcValue_6 = 0;
int adcValue_7 = 0;


int adcflaq_0 = 0;
int adcflaq_1 = 0;
int adcflaq_2 = 0;
int adcflaq_3 = 0;
int adcflaq_4 = 0;
int adcflaq_5 = 0;
int adcflaq_6 = 0;
int adcflaq_7 = 0;


int cenValue_0 = 100;
int cenValue_1 = 100;
int cenValue_2 = 100;
int cenValue_3 = 100;
int cenValue_4 = 100;
int cenValue_5 = 100;
int cenValue_6 = 100;
int cenValue_7 = 100;


int sp_r = 150; 
int sp_l = 150;



void setup()
{
  Serial.begin(115200);

  pinMode(PWML,OUTPUT);
  pinMode(IN1L,OUTPUT);
  pinMode(IN2L,OUTPUT);
  
  pinMode(PWMR,OUTPUT); 
  pinMode(IN1R,OUTPUT);
  pinMode(IN2R,OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);

 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,25);
  display.print("INDY ROBOT");
  display.display();
  delay(200);

  // Software SPI (specify all, use any available digital)
  // (sck, mosi, miso, cs);
  adc.begin(A0, A1, A2, A3);  //set pin sensor pack


while(digitalRead(buttonPin)==HIGH){;;}

  display.clearDisplay();
  delay(200);
}

void loop()
{
  read_test();
  track();

//while(1){;;}

/*
  //สั่งงานมอเตอร์ Motor(ความเร็วล้อซ้าย,ความเร็วล้อขวา);   max speed : 255
  Motor(255,255);   //เดินหน้าทั้งสองล้อ
  delay(1000);
  Motor(-80,-80);   //ถอยหลังทั้งสองล้อ
  delay(1000);
  Motor(-80,80);    //ล้อซ้ายถอย ล้อขวาเดินหน้า
  delay(1000);
  Motor(80,-80);    //ล้อซ้ายเดินหน้า ล้อขวาถอย
  delay(1000);
  Motor(0,0);       //หยุดทั้ง สองล้อ
 */
}

void trackT() //แทรคเจอ T
{
  while(1)
  {
   track();
     if((adcflaq_0==1) && (adcflaq_1==1) && (adcflaq_2==1) && (adcflaq_5==1) && (adcflaq_6==1) && (adcflaq_7==1))      
        {
	Motor(sp_l,sp_r); 
        delay(300);
        Motor(0,0); 
	      delay(100);
        break;
       }
   }
}

void track()
{
	  readADC(); 
    if((adcflaq_0==0) && (adcflaq_1==0) && (adcflaq_2==0) && (adcflaq_5==0) && (adcflaq_6==0) && (adcflaq_7==0))// เซนเซอร์ เจอขาว
      {
      Motor(sp_l,sp_r);  
      }
    else
      {
      ////////////////////////////////////
      if(adcflaq_3==1) // เซนเซอซ้ายเจอดำ
        {
        Motor(0,sp_r);  
        }
      else if(adcflaq_4==1) // เซนเซอขวาเจอดำ
        {
        Motor(sp_l,0); 
        }
      ////////////////////////////////////
      if(adcflaq_2==1) // เซนเซอซ้ายเจอดำ
        {
        Motor(0,sp_r); 
        }
      else if(adcflaq_5==1) // เซนเซอขวาเจอดำ
        {
        Motor(sp_l,0); 
        }
      ////////////////////////////////////
      if(adcflaq_1==1) // เซนเซอซ้ายเจอดำ
        {
        Motor(0,sp_r);  
        }
      else if(adcflaq_6==1) // เซนเซอขวาเจอดำ
        {
        Motor(sp_l,0); 
        }
      ////////////////////////////////////
      if(adcflaq_0==1) // เซนเซอซ้ายเจอดำ
        {
        Motor(-100,sp_r); 
        }
      else if(adcflaq_7==1) // เซนเซอขวาเจอดำ
        {
        Motor(sp_l,-100);  
        }
      }
    
}
  
 
///////////////////////////////////////////////////////////////////////
void Motor(int sl,int sr){          
  if(sr>255)
    sr = 255;
  else if(sr<-255)
    sr = -255;
    
  if(sl>255)
    sl = 255;
  else if(sl<-255)
    sl = -255;
    
  if(sl>0){
      digitalWrite(IN1L,HIGH);
      digitalWrite(IN2L,LOW);
      analogWrite(PWML,sl);
  }else if(sl<0){    
      digitalWrite(IN1L,LOW);
      digitalWrite(IN2L,HIGH);
      analogWrite(PWML,-sl);
  }else{        
      digitalWrite(IN1L,HIGH);
      digitalWrite(IN2L,HIGH);
      analogWrite(PWML,255);
  }  
  
  if(sr>0){
      digitalWrite(IN1R,HIGH);
      digitalWrite(IN2R,LOW);
      analogWrite(PWMR,sr);
  }else if(sr<0){    
      digitalWrite(IN1R,LOW);
      digitalWrite(IN2R,HIGH);
      analogWrite(PWMR,-sr);
  }else{        
      digitalWrite(IN1R,HIGH);
      digitalWrite(IN2R,HIGH);
      analogWrite(PWMR,255);
  }    
}

void readADC()
{ 
 adcValue_0 = adc.readADC(0); 
 adcValue_1 = adc.readADC(1);
 adcValue_2 = adc.readADC(2);
 adcValue_3 = adc.readADC(3);
 adcValue_4 = adc.readADC(4); 
 adcValue_5 = adc.readADC(5);
 adcValue_6 = adc.readADC(6);
 adcValue_7 = adc.readADC(7);

 if(adcValue_0<cenValue_0){adcflaq_0=1;}else{adcflaq_0=0;}
 if(adcValue_1<cenValue_1){adcflaq_1=1;}else{adcflaq_1=0;}
 if(adcValue_2<cenValue_2){adcflaq_2=1;}else{adcflaq_2=0;}
 if(adcValue_3<cenValue_3){adcflaq_3=1;}else{adcflaq_3=0;}
 if(adcValue_4<cenValue_4){adcflaq_4=1;}else{adcflaq_4=0;}
 if(adcValue_5<cenValue_5){adcflaq_5=1;}else{adcflaq_5=0;}
 if(adcValue_6<cenValue_6){adcflaq_6=1;}else{adcflaq_6=0;}
 if(adcValue_7<cenValue_7){adcflaq_7=1;}else{adcflaq_7=0;}
 
}
//////////////////////////////////////////////////////
void read_test()
{      
  
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        
        display.print(" A0 : ");
        display.print(adcflaq_0,DEC);
        display.print(" : ");
        display.println(adcValue_0,DEC);
        
        display.print(" A1 : ");
        display.print(adcflaq_1,DEC);
        display.print(" : ");
        display.println(adcValue_1,DEC);
        
        display.print(" A2 : ");
        display.print(adcflaq_2,DEC);
        display.print(" : ");
        display.println(adcValue_2,DEC);
        
        display.print(" A3 : ");
        display.print(adcflaq_3,DEC);
        display.print(" : ");
        display.println(adcValue_3,DEC);
        
        display.print(" A4 : ");
        display.print(adcflaq_4,DEC);
        display.print(" : ");
        display.println(adcValue_4,DEC);
        
        display.print(" A5 : ");
        display.print(adcflaq_5,DEC);
        display.print(" : ");
        display.println(adcValue_5,DEC);
        
        display.print(" A6 : ");
        display.print(adcflaq_6,DEC);
        display.print(" : ");
        display.println(adcValue_6,DEC);
        
        display.print(" A7 : ");
        display.print(adcflaq_7,DEC);
        display.print(" : ");
        display.println(adcValue_7,DEC);
        

        display.display();
        delay(200);
        display.clearDisplay();
        delay(100);
}




