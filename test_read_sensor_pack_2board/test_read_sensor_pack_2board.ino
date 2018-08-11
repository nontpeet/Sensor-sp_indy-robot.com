/*
 * 
 * โค๊ดนี้เป็นตัวอย่างการอ่านค่าจาก Sensor indy-sp
 * โดยโค็ดนี้ จะทดลองต่อกับ sensor สองตัว และทำการอ่านค่าสลับกัน
 * 
 * www.indy-robot.com
 *  
 */

#include <Adafruit_MCP3008.h>  //เรียกใช้ Library
Adafruit_MCP3008 adc; 


void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Indy-robot.com");

  //adc.begin();  //SPI HW สำหรับ arduino nano -->>  clk=13,miso=12,mosi=11,cs=10
  //adc.begin(A0, A1, A2, A3);  // Software SPI  (sck, mosi, miso, cs);
}

void loop() {
  adc.begin(A0, A2, A1, A3);       // กำหนดขา ที่ใช่ต่อกับ sensor  เรียงตาม sck, mosi, miso, cs  ซ้ายไปขวา
  for (int chan=0; chan<8; chan++) // วนลูป อ่านค่า ตัวที่ 0-7 
      {
      Serial.print(adc.readADC(chan));  // เรียกใช้ adc.readADC(chan) เพื่ออ่านค่า  (chan แทนค่าช่องที่อ่าน ใส่ได้ 0-7)
      Serial.print("\t");
      }

   adc.begin(A0, A2, A1, 13);     // กำหนดขา ที่ใช่ต่อกับ sensor  เรียงตาม sck, mosi, miso, cs  ซ้ายไปขวา
  for (int chan=0; chan<8; chan++)  // วนลูป อ่านค่า ตัวที่ 0-7 
      {
      Serial.print(adc.readADC(chan)); // เรียกใช้ adc.readADC(chan) เพื่ออ่านค่า  (chan แทนค่าช่องที่อ่าน ใส่ได้ 0-7)
      Serial.print("\t");
      }

  

  Serial.println("");
  delay(1000);
}
