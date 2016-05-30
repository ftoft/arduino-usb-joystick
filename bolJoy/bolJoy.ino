/*
Arduino Leonardo Joystick!
 
 */

JoyState_t joySt;
int xAxis = A0;
int yAxis = A1;
int zRotAxis = A4;
int throttle = A2;

const int buttonPin0 = 0;
const int buttonPin1 = 1;
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int buttonPin7 = 7;

const int RUN_CYCLES = 250;

int cycles = 0;
int stateUp = 0;
int stateDown = 0;
boolean flapsDown = LOW;
boolean flapsUp = LOW;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(buttonPin0, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);

  joySt.xAxis = 0;
  joySt.yAxis = 0;
  joySt.zRotAxis = 0;
  joySt.throttle = 0;
  joySt.hatSw = 8;
  joySt.buttons1to8 = 0;
  joySt.buttons9to16 = 0;
  joySt.buttons17to24 = 0;
  
  Serial.begin(9600);
}

void flaps()
{
  if(flapsUp == HIGH) 
  {    
    cycles--;
    if(cycles <= 0) 
    {
      flapsUp = LOW;
    }    
  }
  
  if(digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateUp == 1 && stateDown == 0)
    stateUp = 0;
  else if(!digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateUp == 2 && stateDown == 0)
    stateUp = 1;
  else if(!digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateUp == 3 && stateDown == 0)
    stateUp = 2;  
  else if(!digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateUp == 0 && stateDown == 0)
    stateUp = 1;
  else if(!digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateUp == 1)
    stateUp = 2;
  else if(digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateUp == 2)
    stateUp = 3;
  else if(digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateUp == 3)
    {
      stateUp = 0;
      flapsUp = HIGH;
      cycles = RUN_CYCLES;
    }
  
  if(flapsDown == HIGH) 
  {
    cycles--;
    if(cycles <= 0) 
    {
      flapsDown = LOW;
    }    
  }
    
  if(digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateDown == 1 && stateUp == 0)
    stateDown = 0;
  else if(digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateDown == 2  && stateUp == 0)
    stateDown = 1;
  else if(!digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateDown == 3 && stateUp == 0)
    stateDown = 2;  
  else if(digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateDown == 0 && stateUp == 0)
    stateDown = 1;
  else if(!digitalRead(buttonPin0) && !digitalRead(buttonPin1) && stateDown == 1)
    stateDown = 2;
  else if(!digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateDown == 2)
    stateDown = 3;
  else if(digitalRead(buttonPin0) && digitalRead(buttonPin1) && stateDown == 3)
    {
      stateDown = 0;
      flapsDown = HIGH;
      cycles = RUN_CYCLES;
    }
}

void loop()
{
  joySt.xAxis = analogRead(xAxis)/4-128;//random(255);
  joySt.yAxis = analogRead(yAxis)/4-128;//random(255);
  joySt.zRotAxis = analogRead(zRotAxis)/4-128;//random(255);
  joySt.throttle = analogRead(throttle)/4-128;//random(255);

  //joySt.throttle++;

  flaps();  

  joySt.buttons1to8 = flapsDown | flapsUp << 1 | !digitalRead(buttonPin2) << 2 | 
    !digitalRead(buttonPin3) << 3 | !digitalRead(buttonPin4) << 4 | !digitalRead(buttonPin5) << 5 |
    !digitalRead(buttonPin6) << 6 | !digitalRead(buttonPin7) << 7;

  //joySt.buttons <<= 1;
  //if (joySt.buttons == 0)
    //joySt.buttons = 1;

  //joySt.hatSw1++;
  joySt.hatSw++;

  //if (joySt.hatSw1 > 8)
    //joySt.hatSw1 = 0;
  if (joySt.hatSw > 8)
    joySt.hatSw = 0;

    
  delay(250);

  //if (joySt.throttle > 127)
    //digitalWrite(13, HIGH);
  //else
    //digitalWrite(13, LOW);


  // Call Joystick.move
  Joystick.setState(&joySt);

}

