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
static int max_msg_size = 8; //max msg size is 8

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


void sendMSG(const char *msg)
{
  const char *debug;
  digitalWrite(13, HIGH);
  int msg_size = strlen(msg);

  sprintf(debug, "MSG Size: %", msg_size);
  Serial.println(debug);
  
  int current_char = 0;
  
  const char *__msg;

  
  int y = 0;

  char short_msg[msg_size - 1]; // 8 chars
  
  {

    Serial.println("enered while loop");
    if(strlen(msg) > 0)
    {
    
    if(!(msg_size - current_char > 0))
    {

      Serial.println("Ther is more stuff to send!");
      //send msg if __msg != null
      
      driver.send((uint8_t *)short_msg, strlen(short_msg));
      driver.waitPacketSent();
      digitalWrite(13, HIGH);
      delay(1000); //just to be safe

      
      digitalWrite(13, LOW);  
      return;
    }
    
    if(msg_size - current_char > 0)
    {
  
      Serial.println("more stuff to send");
      
      for(int i = 0; i < 8; ++i)
      {
        Serial.println("begin loading buffer");
        short_msg[i] = msg[current_char];
        current_char += 1;

        
      }

      Serial.println("sending msg");
      driver.send((uint8_t *)short_msg, strlen(short_msg));
      Serial.println("wating for send");
      driver.waitPacketSent();
      
    }
    
    }
    return;
  }while (y == 0);

  digitalWrite(13, LOW);

  Serial.println("ending sendMSG()");
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

   while (ss.available() > 0)
   {
    if (gps.encode(ss.read()))
    {
   pinMode(13, OUTPUT); //for led
   pinMode(8, OUTPUT);

   if(!transmitter_init)
      digitalWrite(8, HIGH);

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

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}


void loop() {

  Serial.println("starting loop");

    const char *randommsg = "asdffdf";
  driver.send((uint8_t *)randommsg, strlen(randommsg));
    driver.waitPacketSent();

  delay(1000);

  int agew = gps.location.age();
  sprintf(randommsg, "ag:%", agew);
  driver.send((uint8_t *)randommsg, strlen(randommsg));
    driver.waitPacketSent();
  sendMSG("Hello");
  
   if(!transmitter_init)
    Serial.println("transmitter init failed");
  //driver.send("Hello World!", strlen("Hello World!"));
  //driver.waitPacketSent();
  
  //sprintf(combinedArray, "Air Pressure: %s Pascales\n", pascals);
  //sendMSG(combinedArray);

  


  sendMSG("Hello World");
  delay(1000);

  

  //order: (# starts sequence ) #(transmission number),S:sattelite val,HD:hdop,LAT:lat,LN:long,AG:age,ALT:altitude in meters,C:course deg,SP:speed kmh$
  const char *__buffer;

  //start of sequence
  sprintf(__buffer, "#,%,S:%,", msg_count, gps.satellites.value());

  driver.send((uint8_t *)__buffer, strlen(__buffer));
  driver.waitPacketSent();

  delay(1000);
  
  sendMSG(__buffer);
  ++msg_count;
  smartDelay(0);


  if(strlen(__buffer) > 0)
    digitalWrite(8, HIGH);
  if(sizeof(__buffer) > 0)
    digitalWrite(8, HIGH);

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

  driver.send((uint8_t *)__buffer, strlen(__buffer));
  driver.waitPacketSent();

  delay(1000);
  
  sendMSG(__buffer);
  smartDelay(0);

  driver.send((uint8_t *)__buffer, strlen(__buffer));
    driver.waitPacketSent();

  delay(1000);

  digitalWrite(8, LOW);
  //TODO: fix D and T for msg
  //printDateTime(gps.date, gps.time);
  
  sprintf(__buffer, "ALT:%,", gps.altitude.meters());
  sendMSG(__buffer);
  smartDelay(0);
  Serial.println(__buffer);
  
  sprintf(__buffer, "C:%,", gps.course.deg());
  sendMSG(__buffer);
  smartDelay(0);
  
  sprintf(__buffer, "SP:%$\n", gps.speed.kmph());
  sendMSG(__buffer);
  smartDelay(0);
  
  //printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.value()) : "*** ", 6);

  sendMSG("Hello World");
  delay(1000);

} //end of if
   } //end of while
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


