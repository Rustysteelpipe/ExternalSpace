#include <Keyboard.h>

int buttonSPC = 3;

void setup()
{
  pinMode(buttonSPC, INPUT);  // Set the button as an input
  digitalWrite(buttonSPC, HIGH);  // Pull the button high

  Keyboard.begin();
}

void loop()
{
  if (digitalRead(buttonSPC) == 0)
  {
    Keyboard.press(32);
    Serial.print("Hey AIMEE...?");
    delay(300);
  }
    else
     {
      Keyboard.release(32);
     }
     

}                                                                          
