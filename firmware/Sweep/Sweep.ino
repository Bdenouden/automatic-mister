/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

unsigned long time_old;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(D8);  // attaches the servo on pin 9 to the servo object
}

void loop() {
//  for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
////    delay(5);                       // waits 15ms for the servo to reach the position
//  }
myservo.write(0); // close
  delay(1000);

  //open
  for (pos = 0; pos <= 100; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }

  time_old = millis();
  while(millis()-time_old <= 10000) yield();
  
}
