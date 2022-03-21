#include <Keyboard.h>

#define USE_KEYBOARD
//#define USE_SERIAL

const int pingTrigPin = 4;
const int pingEchoPin = 5;


const int space_scan_code = 32;

const float ping_threshold_lower_mm = 150.0;
const float ping_threshold_upper_mm = 200.0;

// various sources suggest a 38ms timeout built into the sensor
// this dominates the loop time, giving us approximately 25Hz scan rate
const unsigned long ping_timeout_us = 40000;

bool voice_active = false;



long ping(){
  long duration;
  // The HC-SR-01 is triggered by a HIGH pulse of 10 microseconds.
  digitalWrite(pingTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingTrigPin, LOW);
  //The echo pin goes high for the flight time
  duration = pulseIn(pingEchoPin, HIGH, ping_timeout_us);
  if(0 == duration){
    return ping_timeout_us;
  }
  return duration;
}


// compute a range from the round-trip time
float microsecondsToMillimeters(long microseconds) {
  const float speed_of_sound_m_per_s = 330.0;
  return microseconds * speed_of_sound_m_per_s / 1000.0 / 2.0;
}


void setup()
{
  pinMode(pingTrigPin, OUTPUT);
  digitalWrite(pingTrigPin, LOW);
  pinMode(pingEchoPin, INPUT);
  digitalWrite(pingEchoPin, HIGH);  // The sensor has an open-collector output and needs a pull-up

#ifdef USE_SERIAL
  while (!Serial) { //wait for the serial monitor to connect 
    delay(10);
  }
#endif

#ifdef USE_KEYBOARD
  Keyboard.begin();
#endif
}



void loop()
{

  float range = microsecondsToMillimeters(ping());

  #ifdef USE_SERIAL
  //Serial.print("range is ");
  //Serial.print(range);
  //Serial.print("mm\n");
  #endif

  if(false == voice_active)
  {
    if(ping_threshold_lower_mm > range){
      voice_active = true;

      #ifdef USE_KEYBOARD
      Keyboard.press(space_scan_code);
      #endif

      #ifdef USE_SERIAL
      Serial.println("press");
      #endif

    }
  }
  else
  {
    if(ping_threshold_upper_mm < range){
      voice_active = false;

      #ifdef USE_KEYBOARD
      Keyboard.release(space_scan_code);
      #endif

      #ifdef USE_SERIAL
      Serial.println("relase");
      #endif
    }
  }


}                                                                          
