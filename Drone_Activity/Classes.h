#include <Arduino.h>

//Classes
class Motor{
  
 private:
   Servo servo;
   int pin;
   int velocity;
   float factor;
   
   void arm(){                                                                  // Funcion del armado del ESC
     servo.write(0);
     delay(100);
     servo.write(20);
     delay(100);
  }

  public:
    Motor(){}
    Motor(int p,float f){
      pin=p;
      factor=f;
      velocity=0;  
    }
    
    void startMotor(){
      servo.attach(pin);  // attaches the servo on pin 9 to the servo object  
      arm();
    }

  void setVelocity(int vel){
    velocity=vel;
  }

  int getVelocity(){
    return velocity;
  }
  
  void setFactor(float f){
    factor=f;
  }
  
  void incVelocity(int inc){
    if(velocity+inc>100) velocity=100;
    else velocity+=inc;
  }
  
  void decVelocity(int dec){
    if(velocity-dec<0) velocity=0;
    else velocity-=dec; 
  }
  
  void run(int inc){
    int vel = factor*(float)(velocity+inc);
    servo.write(vel);
    delay(15);    
  }
};

class Accelerometer{
  private:
    int px,py,pz,offX,offY,offZ;
  
  public:
    Accelerometer(){}
    Accelerometer(int x,int y, int z){
      px=A5;
      py=A4;
      pz=A3;
      offX=x;
      offY=y;
      offZ=z;
    }
    
    int readX(){
      return analogRead(px)-offX;      
    }
    
    int readY(){
      return analogRead(py)-offY;
    }
    
    int readZ(){
      return analogRead(pz)-offZ;
    }
};
