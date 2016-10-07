//transmitter_current
#include <SoftwareSerial.h>

#include <TinyGPS++.h>

#include <Wire.h>

#include <RadioHead.h>
#include <radio_config_Si4460.h>
#include <RHCRC.h>
#include <RHDatagram.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHMesh.h>
#include <RHNRFSPIDriver.h>
#include <RHReliableDatagram.h>
#include <RHRouter.h>
#include <RHSoftwareSPI.h>
#include <RHSPIDriver.h>
#include <RHTcpProtocol.h>
#include <RH_ASK.h>
#include <RH_NRF24.h>
#include <RH_NRF905.h>
#include <RH_RF22.h>
#include <RH_RF24.h>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <RH_Serial.h>
#include <RH_TCP.h>

#include <Adafruit_MPL3115A2.h>
#include <SPI.H>

// Power by connecting Vin to 3-5V, GND to GND
// Uses I2C - connect SCL to the SCL pin, SDA to SDA pin
// See the Wire tutorial for pinouts for each Arduino
// http://arduino.cc/en/reference/wire
//Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

RH_ASK driver;

/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


void sendMSG(const char *msg)
{
  int max_msg_size = 8; //max msg size is 8
  int msg_size = strlen(msg);
  int current_char = 0;
  
  const char *__msg;

  
  int y = 0;

  const char short_msg[7]; // 8 chars
  {
    if(!(msg_size - current_char > 0))
    {
      y = 0;
      //send msg if __msg != null
      return;
    }
    
    if(msg_size - current_char > 0 && __msg[current_char] != null)
    {
      
    }
  }while (y == 0);
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();

  if(!driver.init())
    Serial.println("trnasmitter init failed");
}

/*
void sendSTR(String string)
{
  const char *char_array;
  sprintf(char_array, "%", string);

  driver.send((uint8_t *)char_array, strlen(char_array));
  driver.waitPacketSent();

  if(!driver.init())
    Serial.println("trnasmitter init failed");
}
*/

//no longer used
/*
const char toConstChar(String string)
{
    char __output_msg[sizeof(output_msg)];
    output_msg.toCharArray(__output_msg, sizeof(__output_msg));

    return __output_msg;
}
8
*/
const char *msg;

static bool transmitter_init = false;

static int msg_count = 0;

void setup() {

  Serial.begin(9600); //Debug Serial output

  //serial for gps module
  ss.begin(GPSBaud);
  
 // Serial.println("Adafruit_MPL3115A2 test!");
  transmitter_init = driver.init();
  if(!transmitter_init)
    Serial.println("transmitter init failed");

  /* 
  Serial.println(F("-* GPS Module *-"));
  Serial.print(F("Using TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();
  Serial.println();
  Serial.println(F("Sats HDOP Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
  Serial.println(F("          (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
  Serial.println(F("---------------------------------------------------------------------------------------------------------------------------------------"));

  */
  /*
  sendMSG("-* GPS Module *-");

  sprintf(msg, "Using TinyGPS++ library v. % \n", Serial.println(TinyGPSPlus::libraryVersion()));
  sendMSG(msg);

  sendMSG("\n");
  sendMSG("\n");

  sendMSG("Sats HDOP Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Chars Sentences Checksum  Transmitter Status \n");
  sendMSG("          (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  RX    RX        Fail         True/False \n");
  sendMSG("---------------------------------------------------------------------------------------------------------------------------------------\n");

  */
}


void loop() {

   if(!transmitter_init)
    Serial.println("transmitter init failed");
  //driver.send("Hello World! ( xddd )");
  //driver.waitPacketSent();
  
  //sprintf(combinedArray, "Air Pressure: %s Pascales\n", pascals);
  //sendMSG(combinedArray);

  /*
    static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printInt(gps.hdop.value(), gps.hdop.isValid(), 5);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.value()) : "*** ", 6);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  //printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  //printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();
  sendMSG("\n");
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
    sendMSG("No GPS data received: check wiring");

  */
  
  //order: (# starts sequence ) #(transmission number),S:sattelite val,HD:hdop,LAT:lat,LN:long,AG:age,ALT:altitude in meters,C:course deg,SP:speed kmh$
  const char *__buffer;

  //start of sequence
  sprintf(__buffer, "#,%,S:%,", msg_count, gps.satellites.value());
  sendMSG(__buffer);
  ++msg_count;
  smartDelay(0);

  sprintf(__buffer, "HD:%,", gps.hdop.value());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "LAT:%,", gps.location.lat());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "LN:%,", gps.location.lng());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "AG:%,", gps.location.age());
  sendMSG(__buffer);
  smartDelay(0);
  
  //TODO: fix D and T for msg
  //printDateTime(gps.date, gps.time);
  
  sprintf(__buffer, "ALT:%,", gps.altitude.meters());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "C:%,", gps.course.deg());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "SP:%$\n", gps.speed.kmph());
  sendMSG(__buffer);
  smartDelay(0);
  
  //printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.value()) : "*** ", 6);

} //end of loop


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
      sendMSG('*');
    Serial.print(' ');
    sendMSG(' ');
  }
  else
  {
    Serial.print(val, prec);
    
    const char* __val;
    sprintf(__val, "%", val);
    sendMSG(__val);
    
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
      sendMSG(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  sendMSG(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    
    sendMSG("********** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    
    sendMSG(sz);
  }
  
  if (!t.isValid())
  {
   
    sendMSG("******** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
   
    sendMSG(sz);
  }

  
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
    
  smartDelay(0);
}


