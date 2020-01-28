unsigned long currentTime  = 0; //this variable will be overwritten by millis() each iteration of loop
unsigned long pastTime     = 0; //no time has passed yet
int           currentState = 0; //the default state
unsigned long seconds = 0;
int lastBPM = 0;




int pin = A2;

double beatSignal = 0;
double beatSignalTemp = 0;
int bpm = 0;
unsigned long lastTime = 0;

void setup(){
    
    Serial.begin(9600);
    pinMode(pin, INPUT);
    
}

void loop(){
    
    pastTime    = currentTime; //currentTime at this point is the current time from the previous iteration, this should now be pastTime
 currentTime = millis();    //currentTime is now the current time (again).
 
 unsigned long timePassed = currentTime - pastTime; //this is roll-over proof, if currentTime is small, and pastTime large, the result rolls over to a small positive value, the time that has passed

         if ( timePassed >= 1000 );           // increasing variable "seconds" every second 
            { 
               seconds ++;
               pastTime = currentTime;
            }
       
        //else
          //{
            //seconds = 0;                            
          //}                                                  
     
       if ( seconds == 60 )                         // sending signal HIGH ( or low ) to relay when "seconds" reaches 60 and reseting variable
           { 
            Serial.print("minute");
            delay(200);
             seconds = 0; 
             lastBPM = bpm;
             bpm = 0;
          
           }
         

    beatSignal = analogRead(pin);
    // beatSignal = 10;
    Serial.print("raw: ");
    Serial.println(beatSignal);
    Serial.print("temp: ");
    Serial.println(beatSignalTemp);
    Serial.println(seconds);
        Serial.print("bpm: ");
        Serial.println(lastBPM);

     if (beatSignalTemp < (beatSignal-20)){
         Serial.println("BADUM");
         bpm++;
     }
    delay(100);
    
    unsigned long now = millis();
	if (now == 1000) {
		
	}
	
	Serial.printlnf("%lu", now);
    
    beatSignalTemp = beatSignal;

}