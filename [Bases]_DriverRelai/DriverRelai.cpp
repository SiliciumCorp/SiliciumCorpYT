/*

   ___|  _)  | _)       _)                         ___|                     
 \___ \   |  |  |   __|  |  |   |  __ `__ \       |       _ \    __|  __ \  
       |  |  |  |  (     |  |   |  |   |   |      |      (   |  |     |   | 
 _____/  _| _| _| \___| _| \__,_| _|  _|  _|     \____| \___/  _|     .__/  
                                                                     _|   
*/

#include <Arduino.h>
#include "DriverRelai.h"
 

DriverRelai::DriverRelai(int pin)
{
  data_pin = pin;
  pinMode(data_pin, OUTPUT);
  current_state = false;
}

void DriverRelai::switchOn()
{
  current_state = true;
  digitalWrite(data_pin, current_state);
}

void DriverRelai::switchOff()
{
  current_state = false;
  digitalWrite(data_pin, current_state);
}

void DriverRelai::switchState()
{
  current_state = !current_state;
  digitalWrite(data_pin, current_state);
}


boolean DriverRelai::getCurrentState()
{
  return current_state;
}
