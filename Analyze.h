#include <Arduino.h>
#include "class.h"

//Serial com
#define USB_BAUD_RATE 9600

//Bluetooth com
#define BT_BAUD_RATE 9600
#define BT_TX 10
#define BT_RX 11

//Motors
#define TOP_LEFT 3
#define TOP_RIGHT 5
#define BOTTOM_LEFT 6
#define BOTTOM_RIGHT 9

#define FACTOR_TOP_LEFT 0.95
#define FACTOR_TOP_RIGHT 0.95
#define FACTOR_BOTTOM_LEFT 0.97
#define FACTOR_BOTTOM_RIGHT 1

#define M_UP '1'
#define M_DOWN '2'
#define M_LEFT '3'
#define M_RIGHT '4'
#define M_STOP '5'
#define M_START '6'

#define DEFAULT_INC 1
#define DEFAULT_DEC 1

#define START_VELOCITY 80

//Acceleromeer
#define OFFSET_X 500
#define OFFSET_Y 500
#define OFFSET_Z 600
#define ACC_MARGIN_ERROR 20
#define CHANGE_ON_ACC_ERROR 2

//Variables globals
Motor topLeft,topRight,bottomLeft,bottomRight;
SoftwareSerial BT(BT_TX,BT_RX);
Accelerometer accelerometer;
int lastOrder;
boolean analize;

//Funcions
void stop(){
  topLeft.setVelocity(0);
  topRight.setVelocity(0);
  bottomLeft.setVelocity(0);
  bottomRight.setVelocity(0); 
}

void start(){
  topLeft.setVelocity(START_VELOCITY);
  topRight.setVelocity(START_VELOCITY);
  bottomLeft.setVelocity(START_VELOCITY);
  bottomRight.setVelocity(START_VELOCITY);   
}

void testBTChar(char a){
  if (a=='1')
    {
      digitalWrite(13, HIGH);
      Serial.println("LED on");
      BT.println("LED on");
    }
    else if (a=='2')
    {
      digitalWrite(13, LOW);
      Serial.println("LED off");
      BT.println("LED off");
    }
    else if (a=='3')
    {
      Serial.println("new Data: "+a);
      BT.println("Send '1' to turn LED on");
      BT.println("Send '2' to turn LED on");
    }  
}

int charToInt(char c){
  if(c=='0') return 0;
  if(c=='1') return 1;
  if(c=='2') return 2;
  if(c=='3') return 3;
  if(c=='4') return 4;
  if(c=='5') return 5;
  if(c=='6') return 6;
  if(c=='7') return 7;
  if(c=='8') return 8;
  else return 9;
}


int readInt(){
  int out=0,i;
  
  for(i=0; i<3 && BT.available();++i){
     int ni = charToInt(BT.read());
    out+=ni;
     out*=10; 
  }
  return out/10;
}

void configure(char a){
  
  Serial.println("config");
 if(a=='F'){
   delay(20);
  if(BT.available()){
    a=BT.read();
    if(a=='T'){//Top
    delay(20);
     if(BT.available()){
      a=BT.read();
       if(a=='R'){//Dreta
         int i = readInt();
         topRight.setFactor((float)i/(float)100);
         
         Serial.print("TopRight: ");
         Serial.println((float)i/(float)100);
       }else if(a=='L'){//Esquerra
          int i = readInt();
         topLeft.setFactor((float)i/(float)100);
         Serial.print("TopLeft: ");
         Serial.println((float)i/(float)100);
       } 
     }
    }else if(a=='B'){//Bottom
    delay(20);
     if(BT.available()){
      a=BT.read();
       if(a=='R'){//Dreta
         int i = readInt();
         bottomRight.setFactor((float)i/(float)100);
         Serial.print("BottomRight: ");
         Serial.println((float)i/(float)100);
       }else if(a=='L'){//Esquerra
          int i = readInt();
         bottomLeft.setFactor((float)i/(float)100);
         Serial.print("BottomLeft: ");
         Serial.println((float)i/(float)100);
       } 
     }
    }
  } 
 }  
}

void analizeBTChar(char a){
  
  if(a==M_UP){
    lastOrder=M_UP;
    BT.write("up");
    topLeft.incVelocity(DEFAULT_INC);
    topRight.incVelocity(DEFAULT_INC);
    bottomLeft.incVelocity(DEFAULT_INC);
    bottomRight.incVelocity(DEFAULT_INC);
  }else if(a==M_DOWN){
    lastOrder=M_DOWN;
    BT.write("down");
    topLeft.decVelocity(DEFAULT_DEC);
    topRight.decVelocity(DEFAULT_DEC);
    bottomLeft.decVelocity(DEFAULT_DEC);
    bottomRight.decVelocity(DEFAULT_DEC);
  }else if(a==M_RIGHT){
    lastOrder=M_RIGHT;
    BT.write("left");
    topLeft.incVelocity(DEFAULT_INC);
    bottomLeft.incVelocity(DEFAULT_INC);
    
    topRight.decVelocity(DEFAULT_DEC);
    bottomRight.decVelocity(DEFAULT_DEC);
  }else if(a==M_LEFT){
    lastOrder=M_LEFT;
    BT.write("right");
    topRight.incVelocity(DEFAULT_INC);
    bottomRight.incVelocity(DEFAULT_INC);
    
    topLeft.decVelocity(DEFAULT_DEC);
    bottomLeft.decVelocity(DEFAULT_DEC);    
  }else if(a==M_STOP){
    lastOrder=M_STOP;
    BT.write("stop");
    stop();
  }else if(a==M_START){
    lastOrder=M_START;
    BT.write("start");
    start(); 
  }else if(a=='A'){
    analize!=analize;
  }else configure(a);
    
}






void analizeAccelerometer(){    
  Serial.print("X = ");      
  Serial.print(accelerometer.readX());          
  Serial.print("\tY = ");      
  Serial.print(accelerometer.readY());
  Serial.print("\tZ = ");      
  Serial.println(accelerometer.readZ());
  
  delay(500);
}

void execute(){
  int incTopLeft=0,incTopRight=0,incBottomLeft=0,incBottomRight=0;
  if(analize)
    if(lastOrder==M_UP){
      int acc = accelerometer.readX();
      if(acc<-ACC_MARGIN_ERROR){
        incTopRight=CHANGE_ON_ACC_ERROR;
        incBottomRight=CHANGE_ON_ACC_ERROR;
      }else if(acc>ACC_MARGIN_ERROR){
        incTopLeft=CHANGE_ON_ACC_ERROR;
        incBottomLeft=CHANGE_ON_ACC_ERROR;
      }
      
      acc=accelerometer.readY();
      if(acc<-ACC_MARGIN_ERROR){
        if(incTopLeft==0)incTopLeft=CHANGE_ON_ACC_ERROR;
        if(incTopRight==0)incTopRight=CHANGE_ON_ACC_ERROR;
      }else if(acc>ACC_MARGIN_ERROR){
        if(incTopLeft==0)incBottomLeft=CHANGE_ON_ACC_ERROR;
        if(incTopLeft==0)incBottomRight=CHANGE_ON_ACC_ERROR;
      }
    }
  
  topLeft.run(incTopLeft);
  topRight.run(incTopRight);
  bottomLeft.run(incBottomLeft);
  bottomRight.run(incBottomRight);  
}
