/*
 * 
 * โค๊ดนี้เป็นตัวอย่างการอ่านค่าจาก Sensor indy-sp
 * โดยโค็ดนี้ จะทดลองต่อกับ sensor 1ตัว 
 * 
 * www.indy-robot.com
 *  
 */

#include <Adafruit_MCP3008.h>  //เรียกใช้ Library
Adafruit_MCP3008 adc; 

int sensor_a0 = 0;
int sensor_a1 = 0;
int sensor_a2 = 0;
int sensor_a3 = 0;
int sensor_a4 = 0;
int sensor_a5 = 0;
int sensor_a6 = 0;
int sensor_a7 = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Indy-robot.com");

  //adc.begin();  //SPI HW สำหรับ arduino nano -->>  clk=13,miso=12,mosi=11,cs=10
  //adc.begin(A0, A1, A2, A3);  // Software SPI  (sck, mosi, miso, cs);

  adc.begin(A0, A2, A1, A3);       // กำหนดขา ที่ใช่ต่อกับ sensor  เรียงตาม sck, mosi, miso, cs  ซ้ายไปขวา
}

void loop() {
  
  // อ่านค่าจาก sensor และเก็บในตัวแปร
  sensor_a0 = adc.readADC(0);
  sensor_a1 = adc.readADC(1);
  sensor_a2 = adc.readADC(2);
  sensor_a3 = adc.readADC(3);
  sensor_a4 = adc.readADC(4);
  sensor_a5 = adc.readADC(5);
  sensor_a6 = adc.readADC(6);
  sensor_a7 = adc.readADC(7);

  //แสดงผลค่าที่อ่านได้
  Serial.print(adc.readADC(0));
  Serial.print("\t");
  Serial.print(adc.readADC(1));
  Serial.print("\t");
  Serial.print(adc.readADC(2));
  Serial.print("\t");
  Serial.print(adc.readADC(3));
  Serial.print("\t");
  Serial.print(adc.readADC(4));
  Serial.print("\t");
  Serial.print(adc.readADC(5));
  Serial.print("\t");
  Serial.print(adc.readADC(6));
  Serial.print("\t");
  Serial.print(adc.readADC(7));
  Serial.print("\t");
  
 
  Serial.println("");
  delay(1000);
}
