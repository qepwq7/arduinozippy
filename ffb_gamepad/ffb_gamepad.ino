/*
 Based on NicoHood extensions for Arduino IDE > 1.6.0

 Press physical buttons to press USB Gamepad buttons.
 This can be used for a simple SNES Controller.

 Make sure the Gamepad report is set in:
 sketchbook/hardware/HID/avr/variants/hid_descriptors/hid_descriptors.h
*/

#define DEBUG false // set to true to show serial messages

//Define button pins, pin 0 is unused as it seems that a controller cannot have a "Button 0"
const int pinButton[7] = {0, 11, 12, 18, 19, 20, 21};
int count = 0;

void setup(){
  if (DEBUG)             
    Serial.begin(9600);
//Define pins in array as INPUT_PULLUP
  for (count=0;count<7;count++) {
    pinMode(pinButton[count], INPUT_PULLUP);
  }
// Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {
// check each button and press Gamepad if needed
  for (count=0;count<7;count++) {
    if (!digitalRead(pinButton[count]))
      Gamepad.press(count);
    else
      Gamepad.release(count);
  }
  
//Axis  
  Gamepad.yAxis(0);
  Gamepad.xAxis(0);
  //Gamepad.yAxis
    //Yaxis (analogRead(A2), 0, 1023, -32768, 0 ) + map( analogRead(A0), 0, 1023, 0, 32767 ));

   //Gamepad.xAxis(map( analogRead(A1), 0, 1023, -32768, 32767 ));
   //Gamepad.yAxis(map( analogRead(A2), 0, 1023, -32768, 32767 ));
   //Gamepad.rxAxis(map( analogRead(A0), 0, 1023, -32768, 32767 ));
   //Gamepad.ryAxis(map( analogRead(A3), 0, 1023, -32768, 32767 ));
   
 //  Gamepad.xAxis( (analogRead(A1) << 5) - (analogRead(A3) << 5) );
 //  Gamepad.yAxis( (analogRead(A2) << 5) - (analogRead(A0) << 5) );
int axisx ;
int axisy ;

int leftx = analogRead(A1) << 5;
int rightx = analogRead(A3) << 5;

int lefty = analogRead(A2) << 5;
int righty = analogRead(A0) << 5;

  //Gamepad.xAxis(random(0));
  //  Gamepad.ryAxis(random(0xFFFF));
// Gamepad.xAxis(-32768);
 //left = map(analogRead(A1), 0, 1023, 32, 32736);
 
//CEnter treshold

axisx = leftx - rightx;
 if (abs(axisx) < 128) 
   Gamepad.xAxis(0);
    
    
  axisy = lefty - righty;
 if (abs(axisy) < 128) 
  Gamepad.yAxis(0);
  
if ((leftx) > 30000 && (rightx) > 3000)
Gamepad.xAxis(0);
if ((leftx) < 1000 && (rightx) > 3000)
Gamepad.xAxis(-32768);

if ((rightx) < 1000 && (leftx) > 3000)
Gamepad.xAxis(32767);

if ((lefty) > 30000 && (righty) > 3000)
Gamepad.yAxis(0);
if ((lefty) < 1000 && (righty) > 3000)
Gamepad.yAxis(-32768);

if ((righty) < 1000 && (lefty) > 3000)
Gamepad.yAxis(32767);

 //if (abs(axisy) > 29000)
 //Gamepad.yAxis(32767);
 //if (abs(axisy) > -29000)
   // Gamepad.yAxis(-32768);
    
 //if (abs(leftx) < 29000 && abs(rightx) > 29000) 
//Gamepad.xAxis(0);
 //if (abs(axisx) < -29000)
  //  Gamepad.xAxis(-32768);
  // write the information to the host now!
  Gamepad.write();
if (DEBUG) {
  Serial.print("leftx:");
  Serial.println(leftx);
  Serial.print("rightx:");
  Serial.println(rightx);
 //delay(250);
 }
}
