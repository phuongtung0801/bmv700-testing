/*************************************************************************************
 ReadVeDirectFrameHandler

 Uses VeDirectFrameHandler library

 This example and library tested with NodeMCU 1.0 using Software Serial.
 If using with a platform containing 2 harware UART's, use those, not SoftwareSerial.
 Tested with Victron BMV712.

 VEDirect Device:
   pin 1 - gnd
   pin 2 - RX
   pin 3 - TX
   pin 4 - power

 History:
   2020.05.05 - 0.3 - initial release

**************************************************************************************/

#include "Arduino.h"
#include <HardwareSerial.h>
#include "VeDirectFrameHandler.h"

#define RX_232_PIN 35
#define TX_232_PIN 34

VeDirectFrameHandler myve;

void EverySecond();
void PrintData();
void ReadVEData();

void setup()
{
  Serial.begin(115200);                                     // output serial port
  Serial1.begin(19200, SERIAL_8N1, RX_232_PIN, TX_232_PIN); // input serial port (VE device)
  Serial1.flush();
  Serial.println("DEBUG-setup");
}

void loop()
{
  ReadVEData();
  EverySecond();
}

void ReadVEData()
{
  while (Serial1.available())
  {
    myve.rxData(Serial1.read());
  }
  yield();
}

void EverySecond()
{
  static unsigned long prev_millis;

  if (millis() - prev_millis > 1000)
  {
    PrintData();
    prev_millis = millis();
  }
}

void PrintData()
{
  for (int i = 0; i < myve.veEnd; i++)
  {
    Serial.print(myve.veName[i]);
    Serial.print("= ");
    Serial.println(myve.veValue[i]);
  }
}
