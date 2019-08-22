


#include <RCSwitch.h>

RCSwitch mySwitch433 = RCSwitch();
RCSwitch mySwitch315 = RCSwitch();

//int sensorPin = A0;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
//int sensorValue = 0;  // variable to store the value coming from the sensor

const int Knock = A0;     
const int ReedSwitch=4;
const int Transmitter433=2;
const int Transmitter315=3;
const int THRESHOLD=400;

// variables will change:
int KnockValue = 0;         // variable for reading the pushbutton status
int ReedValue=0;
int LastReedValue=0;

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
  pinMode(Knock, INPUT);
  pinMode(ReedSwitch,INPUT);
  LastReedValue=digitalRead(ReedSwitch);

  // Transmitter is connected to Arduino Pin #10  
  mySwitch433.enableTransmit(Transmitter433);

  mySwitch315.enableTransmit(Transmitter315);
 
  //FirstKnockTime=millis();
  Serial.begin(9600);
  //B E G F# E high B A F# E G F# D F B
}

void loop() {
  // read the value from the sensor:
  KnockValue = analogRead(Knock);
  Serial.print(KnockValue);
  Serial.print("::");

  //CurrentTime=millis();

  if (KnockValue>THRESHOLD) {

      /* mySwitch433.setPulseLength(362); //362
      mySwitch433.setRepeatTransmit(15);
      mySwitch433.send(15283380,24); // Table
      */
      
      // Magic Hat
      mySwitch315.setPulseLength(325); //362
      mySwitch315.setRepeatTransmit(15);
      mySwitch315.send(2833332,24);
      mySwitch315.send(5003716,24);

      /*
      delay(150);
      mySwitch433.setPulseLength(362); //362
      mySwitch433.setRepeatTransmit(15);
      mySwitch433.send(15283380,24); // Table
      */
  
  }
  
  ReedValue=digitalRead(ReedSwitch);
  if (ReedValue!=LastReedValue) {
    // Magnet has been toggled
    Serial.println("Switching maglock relay");
    mySwitch433.setPulseLength(362); //295); //362
    mySwitch433.setRepeatTransmit(15);
    mySwitch433.send(3141032, 24); //Maglock

    mySwitch433.setRepeatTransmit(30);
    mySwitch433.send(3064036,24); // Book


  }
  LastReedValue=ReedValue;
    
  //Serial.println(ReedValue);
  

  delay(50);
}

/* 
 *  Card Shower Old On': ('7360780','363','315'),
            'Card Shower Old Off': ('7360960', '234', '315'),
            'Rising Card On': ('5078284', '227', '315'),
            'Rising Card Off': ('5078464', '225', '315'),
            'Card Shower New': ('284159', '535', '315'),
            'Table Old Off': ('13058496', '241', '315'),
            'Table Old On': ('13058316', '245', '315'),
            'Card Shower New1': ('2833332','325','315'),
            'Card Shower New2': ('5003716','331','315'),
            'Table': ('15283380', '348','433'),
            'Flying Book': ('3064036', '351', '433'),
            'Lock': ('3141032', '295', '433'),
            'RelayB': ('3141028', '295', '433'),
            'RelayC': ('3141026', '294', '433'),
            'RelayD': ('3141025','295', '433'),
            'Relay1': ('6679343', '308', '433')
*/
