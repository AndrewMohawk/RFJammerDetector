/* Simple Script to 'detect' jammers, really just looks at the average analog in values   
 * from a cheap 433mhz RX component and then decides if its been held 'low' ( like a remote has been pressed )
 * for too many seconds.
 * 
 * Wiring is relatively straight forward:
 * 
 * Datapin of 433mhz RX -> analog 'inPin' ( default *analog* 2 )
 * Green LED -> 'greenLED' ( default 2 )
 * Red LED -> 'redLED' ( default 3)
 * Vibration Motor -> 'buzzPin' ( default 11 )
 * 
*/

int numSamples = 300; // num samples to take every loop
int jamTimeMS = 300; // how long we need high samples before triggering
int highVal = 105; // what the 'high' value is ( default noise )
int lowVal  = 50; // what the 'low' value is ( remote being pressed )

#define greenLED 2
#define redLED 3

int inPin = 2;
int buzzPin = 11;
int buzzAmount = 200;

long total = 0;
long inputVal = 0;
float val;                           
unsigned long jamTimer = 0;
unsigned long stableTimer = 0;


void setup() {
   Serial.begin(115200);            
   Serial.println("*trumpets* Started Jam Detector!");
   pinMode(greenLED,OUTPUT);
   pinMode(redLED,OUTPUT);
   digitalWrite(greenLED,HIGH);
 
  
 }

void loop() {
  for(int i = 0; i < numSamples; i++)
  {     
    total += analogRead(inPin);
  }                                   

  val = total / numSamples;           
  val = constrain(val, 0, 1023);     //this constrains the variable value to between two numbers 0 and 1023, the max value on a analog input                                       
  val = map(val, 0, 1023, 0, 255);   //the map statement tells the program to map out 0-100 to 0-255, 255 is the max on a analog output
  
  
    if (val > highVal)
    {   
       
      if (stableTimer == 0)
      {
        stableTimer = millis();
        Serial.print(millis());
        Serial.println(": Stable Timer Started");
      }
      else
      {
        if(millis() - stableTimer > 300)
        {          
          if(jamTimer > 0)
          {
            digitalWrite(greenLED,HIGH);
            digitalWrite(redLED,LOW);
            analogWrite( buzzPin , 0 );
            Serial.print(millis());Serial.println(": Jam Timer Ended");
            
          }
          jamTimer = 0;

        }
      }
    }

    if (val < lowVal)
    {
       stableTimer = millis();        
      if(jamTimer == 0)
      {
        Serial.print(millis());Serial.println(": Jam Timer Started");
        jamTimer = millis();
        
      }
      else
      {
        if (millis() - jamTimer > jamTimeMS)
        {
          Serial.print(millis());Serial.println(": JAM Detected!");
          digitalWrite(greenLED,LOW);
          digitalWrite(redLED,HIGH);
          analogWrite( buzzPin , buzzAmount );
         
        }
      }

    }    
    total = 0;                  
    delay(1);                        
}
