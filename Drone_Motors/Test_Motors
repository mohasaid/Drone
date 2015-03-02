#include <Servo.h> 

#define PIN_MOTOR 9
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
   myservo.attach(PIN_MOTOR);
   arm();
} 
 
void loop() 
{ 
  myservo.write(70);
  delay(15);                          // waits for the servo to get there 
}

void arm(){                                                                   // Funcion del armado del ESC
 myservo.write(0);
 delay(100);
 myservo.write(20);
 delay(100);
}
