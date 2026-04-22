int leds = 13;
int echoPin = 3;
int trigPin = 2;
int inpin = 9;
int button = 0;
int buttonActive = 0;
bool distTrigger;
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leds, OUTPUT);
  pinMode(inpin, INPUT_PULLUP);
  digitalWrite(trigPin, LOW);
  Serial.begin(9600);
  myservo.attach(10);
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(100);

  button = digitalRead(inpin);

  if ((buttonActive == 1) && (button == LOW)) {         // If the button has been activated prev. and is pressed now, do
    buttonActive = 0;                                   // put the button as not active
    Serial.print("button is now UNpressed");            //debugging
  } else if ((buttonActive == 0) && (button == LOW)) {  //if the button has not been activated prev, and is pressed now, do
    buttonActive = 1;                                   // puts the button as active
    Serial.print("button is now pressed");              //debugging
  }
  if ((distance < 20) || (buttonActive == 1)) {  //if distance is less than 20 or button is active
    warning();                                   // our warning signs

  } else if ((distance < 20) && (buttonActive == 0)) {  // if the distance is less than 20 and button is not active
    noWarning();                                        // stop warning signs

  } else if (distance < 20) {  //if distance is less than 20
    warning();                 // start warning
    buttonActive = 1;          //put button to active?

  } else if (buttonActive == 0) {  // if button isnt active
    noWarning();                   // no warning?


  } else {
    noWarning();
  }
}

int warning() {              // our warning
  distTrigger = true;        // sets distance trigger to on
  digitalWrite(leds, HIGH);  // turns on all leds
  tailRattle();              // calls tail rattling function
}

int noWarning() {           // our turn off from warning
  distTrigger = false;      // distance trigger to off
  digitalWrite(leds, LOW);  //turns leds off
  pos = 100;                // sets servo pos
  myservo.write(pos);       // sets servo to pos
}

int tailRattle() {  // its rattling back and forwards
  pos = 140;
  myservo.write(pos);
  delay(70);
  pos = 40;
  myservo.write(pos);
  delay(70);
}



/*
If (distance < 20…){
distTrigger = true;
Digitalwrite(leds, HIGH);
} else if (distance < 20 && distTrigger == true && button == low ){ if distance < 20 and distrigger on, and button is active 
Digitalwrite (leds, LOW)
distTrigger = false;
} 


*/
