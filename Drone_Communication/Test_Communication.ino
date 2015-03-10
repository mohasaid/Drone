#include <SoftwareSerial.h>
#define BT_TX 10
#define BT_RX 11

#define USB_BAUD_RATE 9600

SoftwareSerial BT(BT_TX,BT_RX); 

// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup()  
{
  // set digital pin to control as an output
  pinMode(13, OUTPUT);
  Serial.begin(USB_BAUD_RATE);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  
  // Send test message to other device
  Serial.println("Missatge inicial per usb");
  BT.println("Diarrea de penes");
}
char a; // stores incoming character from other device
void loop() 
{
  //test1();
  test2();
}

void test1(){
  
  if (BT.available())
  {
    a=(BT.read());
    Serial.println(a);
    if (a=='1')
    {
      digitalWrite(13, HIGH);
      Serial.println("new Data: "+a);
      BT.println("LED on");
    }
    if (a=='2')
    {
      digitalWrite(13, LOW);
      Serial.println("new Data: "+a);
      BT.println("LED off");
    }
    if (a=='?')
    {
      Serial.println("new Data: "+a);
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED on");
    }
  }
}

void test2(){
 boolean isSend=false;
 
 while(BT.available()){
  isSend=true;
  char r = BT.read();
  Serial.print(r);
 }

if(isSend) Serial.println(""); 
}
