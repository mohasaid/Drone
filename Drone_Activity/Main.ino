#include <SoftwareSerial.h>
#include <Servo.h>
#include "analize.h"

void setup(){
  //Com serie
  Serial.begin(USB_BAUD_RATE);
  
  //com bt
  BT.begin(BT_BAUD_RATE);
  
  //Motors
  topLeft = Motor(TOP_LEFT,FACTOR_TOP_LEFT);
  topLeft.startMotor();
  
  topRight = Motor(TOP_RIGHT,FACTOR_TOP_RIGHT);
  topRight.startMotor();
  
  bottomLeft= Motor(BOTTOM_LEFT,FACTOR_BOTTOM_LEFT);
  bottomLeft.startMotor();
  
  bottomRight = Motor(BOTTOM_RIGHT,FACTOR_BOTTOM_RIGHT); 
  bottomRight.startMotor();
  
  //Accelerometer
  accelerometer = Accelerometer(OFFSET_X,OFFSET_Y,OFFSET_Z);
  
  //Variables globals
  lastOrder=M_STOP;
  analize=false;
  
  Serial.println("End setup");
   
}

void loop(){
  //Analisi del bt
  if(BT.available()) analizeBTChar(BT.read());
  
  //analizeAccelerometer();
  
  //Analisi del accelerometre
  execute();
  
}
