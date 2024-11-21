/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

int ledEntrance = 9;           // the PWM pin the LED is attached to
int ledFirstFloor = 13;     //the digital pin that the LED chain is connected to
int ledSecondFloor = 12; 
int ledThirdFloor = 14;     //the digital pin that the third floor LED chain is connected to. 
int buttonPin = 3;  
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
volatile int floor_level = 0;
bool stateEntrance = HIGH;
bool stateFirstFloor = HIGH;     //The state of the LED chain
bool stateSecondFloor = HIGH;     //The state of the second-floor LED chain
bool stateThirdFloor = HIGH;     //The state of the second-floor LED chain

void turnOnFirstFloor()
{
  int offTime = random(0, 100);
  int offTurns = random(0, 20);
  for(int i = 0; i<offTurns; i++)
  {
    analogWrite(ledFirstFloor, 0);
    delay(offTime);
    analogWrite(ledFirstFloor, 200);
    delay(offTime);
  }
  analogWrite(ledFirstFloor, 0);
  delay(offTime*10);
  analogWrite(ledFirstFloor, 200);
}

void turnOnSecondFloor()
{
  int offTime = random(0, 100);
  int offTurns = random(0, 20);
  for(int i = 0; i<offTurns; i++)
  {
    analogWrite(ledSecondFloor, 0);
    delay(offTime);
    analogWrite(ledSecondFloor, 210);
    delay(offTime);
  }
  analogWrite(ledSecondFloor, 0);
  delay(offTime*10);
  analogWrite(ledSecondFloor, 210);
}

void turnOnThirdFloor()
{
  int offTime = random(0, 100);
  int offTurns = random(0, 20);
  for(int i = 0; i<offTurns; i++)
  {
    analogWrite(ledThirdFloor, 0);
    delay(offTime);
    analogWrite(ledThirdFloor, 180);
    delay(offTime);
  }
  analogWrite(ledThirdFloor, 0);
  delay(offTime*10);
  analogWrite(ledThirdFloor, 210);
  delay(offTime);
}

void turnOnEntrance()
{
  analogWrite(ledEntrance, brightness);
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
   fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void floorBlinking()
{
  int blinkingFloor = random(0, 4);
  int offTime = random(1, 20);
  Serial.println("Blinking");
  Serial.println(offTime*100000);
  switch(blinkingFloor)
  {
    case 0:
    {
      analogWrite(ledEntrance, 0);
      delay(offTime);
      analogWrite(ledEntrance, 190);
      delay(offTime);
    }
    case 1:
    {
      analogWrite(ledFirstFloor, 0);
      delay(offTime);
      analogWrite(ledFirstFloor, 200);
      delay(offTime);
    }
    case 2:
    {
      analogWrite(ledSecondFloor, 0);
      delay(offTime);
      analogWrite(ledSecondFloor, 210);
      delay(offTime);
    }
    case 3:
    {
      analogWrite(ledThirdFloor, 0);
      delay(offTime);
      analogWrite(ledThirdFloor, 220);
      delay(offTime);
    }
    case 4:
    {
      delay(offTime*1000);
    }
  }
}

void turnOnFloors()
{
  int floorNumber = random(1, 3);
  switch(floorNumber)
  {
    case 1:
    {
      turnOnFirstFloor();
      break;
    }
    case 2:
    {
      turnOnSecondFloor();
      break;
    }
    case 3:
    {
      turnOnThirdFloor();
      break;
    }
  }
}

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(ledEntrance, OUTPUT);
  pinMode(ledFirstFloor, OUTPUT);
  pinMode(ledSecondFloor, OUTPUT);
  pinMode(ledThirdFloor, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  for(int i = 0; i< 51; i++)
  {
    turnOnEntrance();
  }
  for(int i = 1; i < 3; i++)
  {
    turnOnFloors();
  }
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkButton, LOW);
  Serial.begin(57600);
}

void checkButton() {
  floor_level++;
  turnOffFloor();
}

void turnOffFloor()
{
  switch(floor_level)
  {
    case 1:
    {
      analogWrite(ledFirstFloor, 0);
      analogWrite(ledSecondFloor, 210);
      analogWrite(ledThirdFloor, 220);
      break;
    }
    case 2:
    {
      analogWrite(ledFirstFloor, 190);
      analogWrite(ledSecondFloor, 0);
      analogWrite(ledThirdFloor, 220);
      break;
    }
    case 3:
    {
      analogWrite(ledFirstFloor, 190);
      analogWrite(ledSecondFloor, 210);
      analogWrite(ledThirdFloor, 0);
      break;
    }
    case 4:
    {
      analogWrite(ledFirstFloor, 190);
      analogWrite(ledSecondFloor, 210);
      analogWrite(ledThirdFloor, 220);
      floor_level = 0;
      break;
    }
  }
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("Running");
  Serial.println(floor_level);
  floorBlinking();
}
