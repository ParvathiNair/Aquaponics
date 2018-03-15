#include <Servo.h>

#define FEED_INTERVAL   1   // minutes between feeding time

const byte servoPin = 9;      // pin used to command the servo motor
const int waitingTime = FEED_INTERVAL;

Servo servo;

volatile unsigned long sec;
const unsigned long feedInterval = (unsigned long) FEED_INTERVAL * (unsigned long) 60;  // expressed in seconds

/**
   stop the food from flowing
*/
void feederClose() {
  servo.write(180);
  delay(175);
  servo.write(90);
}

/**
   release a ration of food
*/
void feederOpen() {
  servo.write(0);
  delay(175);
  servo.write(90);
}

// Interrupt is called once a millisecond,
SIGNAL(TIMER0_COMPA_vect)
{
  if (millis() % 1000 == 0) { // if a second has passed
    sec++;  // increment the seconds counter
    Serial.print("Second: ");
    Serial.print(sec);
    Serial.print(" of ");
    Serial.println(feedInterval);
  }
}

void setup() {
  Serial.begin(9600);
  OCR0A = 0xAF; // set the timer interrupt
  TIMSK0 |= _BV(OCIE0A);
  servo.attach(servoPin);
  Serial.println("System initialized");
}

void loop() {
  Serial.println("Waiting...");
  sec = 0;  // reset the counter
  while (feedInterval > sec);   // wait until the time interval is elapsed
  Serial.println("Feeding the pet :)");
  feederOpen();
  delay(150);
  feederClose();
}
