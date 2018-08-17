#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)

const int trigPin = 4;
const int echoPin = 5;
// (Create an instance of a radio, specifying the CE and CS pins. )
RF24 myRadio (7, 8); // "myRadio" is the identifier you will use in following methods
/*-----( Declare Variables )-----*/
long duration;
int distance;
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
int dataTransmitted;  // Data that will be Transmitted from the transmitter

void setup()   /****** SETUP: RUNS ONCE ******/
{ pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
  //Serial.begin(115200);
  //delay(1000);
  //Serial.println(F("RF24/Simple Transmit data Test"));
  //dataTransmitted = 100; // Arbitrary known data to transmit. Change it to test...
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MIN);
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power

  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  delay(1000);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // Clears the trigPin
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 // Sets the trigPin on HIGH state for 10 micro seconds
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 // Reads the echoPin, returns the sound wave travel time in microseconds
 duration = pulseIn(echoPin, HIGH);
 // Calculating the distance
 distance= duration*0.034/2;
 dataTransmitted = distance;
   myRadio.write( &dataTransmitted, sizeof(dataTransmitted) ); //  Transmit the data
  delay(500);

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/


//*********( THE END )***********

