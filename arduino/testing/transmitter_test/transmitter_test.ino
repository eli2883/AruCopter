#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

static bool inits = false;

void setup()
{
    Serial.begin(9600);   // Debugging only

    inits = driver.init();
    if (!init)
         Serial.println("init failed");
}

void loop()
{
    if (!init)
         Serial.println("init failed");
         
    const char *msg = "Hello World!";

    //const char *msg_2 = "Unless you are a published theoretical physicist and have earned a Master of Science and two PhDs, have an IQ of 187, and went to college at 11, research String Theory at Caltech, switched disciplines from bosonic string theory to heterotic string theory and reconciled the black hole information paradox using a string network condensate approach, worked on the string theory implications of gamma rays from dark matter annihilations and considered a method for optimizing a 500 GeV particle detector to this end, jointly wrote a paper on supersolids to be presented at an Institute of Experimental Physics topical conference on Bose-Einstein condensates, keep a whiteboard in the living room for scientific theories containing virtual particles in quantum mechanics or series of Riemann zeta functions, then no I will not ask you any questions"
    
    //TODO: look at source for RH_ASK (radiohead)
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    //TODO: find perfect delay (most bytes/min w/ somewhat stability
    delay(1000);
}
