// This #include statement was automatically added by the Particle IDE.
#include <MCP9808.h>

#include "SparkIntervalTimer.h"


MCP9808 mcp = MCP9808();

char publishString[128];


void interruptSetup(void);
void serialOutput();
void serialOutputWhenBeatHappens();
void sendDataToSerial(char symbol, int data );
void ledFadeToBeat();
void arduinoSerialMonitorVisual(char symbol, int data );

extern int pulsePin;
extern int blinkPin;
extern volatile int BPM;;
extern volatile int Signal;;
extern volatile int IBI;
extern volatile boolean Pulse;
extern volatile boolean QS;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0; 
int bpmm;
extern int fadePin;
extern int fadeRate;

float temperature = 0;

void setup(){
     
// 	Spark.variable("getpos", &bpmm, INT);
	pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
	pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
	Serial.begin(115200);             // we agree to talk fast!
	
	  
	Serial.println("MCP9808 test");

	// Wait for the sensor to come up
	while(! mcp.begin()){
	    Serial.println("MCP9808 not found");
	    delay(500);
	}

	// Set resolution to the maximum (slowest conversion)
	mcp.setResolution(MCP9808_SLOWEST);

	Serial.println("MCP9808 OK");
	
	interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
	for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop(){
     // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = BPM;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
    bpmm = average;
    // Serial.println(BPM);
    Serial.println(bpmm);
    	Serial.print("Temp:"); Serial.println(mcp.getTemperature(), 4);
    
    temperature = (mcp.getTemperature());
    
 sprintf(publishString,"%d %f",bpmm,temperature);
        Spark.publish("Heat",publishString);
	delay(1001);
    }
    