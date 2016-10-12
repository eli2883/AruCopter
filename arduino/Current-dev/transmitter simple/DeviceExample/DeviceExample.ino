#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

static bool inits = false;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();

  //stuff for transmitter

  inits = driver.init();
    if (!init)
         Serial.println("init failed");
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  //stuff for transmr

    const char *msg;
    const char alt;
    float falt;
    //const char *msg_2 = "Unless you are a published theoretical physicist and have earned a Master of Science and two PhDs, have an IQ of 187, and went to college at 11, research String Theory at Caltech, switched disciplines from bosonic string theory to heterotic string theory and reconciled the black hole information paradox using a string network condensate approach, worked on the string theory implications of gamma rays from dark matter annihilations and considered a method for optimizing a 500 GeV particle detector to this end, jointly wrote a paper on supersolids to be presented at an Institute of Experimental Physics topical conference on Bose-Einstein condensates, keep a whiteboard in the living room for scientific theories containing virtual particles in quantum mechanics or series of Riemann zeta functions, then no I will not ask you any questions"

    falt = gps.altitude.meters();
    sprintf(msg, "%M", falt);
    
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    //TODO: find perfect delay (most bytes/min w/ somewhat stability
    delay(1000);

  Serial.println();
}
