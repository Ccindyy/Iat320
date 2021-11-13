// Tutorials used: analog_sensors, CircusPlaygrooundFirmata, accelTap, Hello_Accelerometer

//TABLE OF CONTENTS
//Setup
//.......global variables
//.......void setup()
//............Serial port & library
//............Accelerometer settings
//
//Animations
//.......void rainbowSpin()
//.......void flowerBlink()
//............flower spin
//............flower blink
//.......void pureWhite()
//.......void redSpin()
//
//Accelerometer Detection
//.......dropDetection(void)
//.......void tiltDetection(void)
//
//Compilation
//.......void loop()

//---------------------------------------------------------------------------------Setup---------------------------------------------------------
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 120

uint8_t rainbow = 0;
uint8_t whitePetals = 0;
uint8_t pinkPetals = -1;
uint8_t red = 0;

//states
//These are the order of the animation that the circuit playground will flip through if you hit the left or right buttons to go forward/back through the list. 
//Change their numbers to edit the order.
int state = 0;
const int NEUTRAL = 0;
const int RAINBOW = 1;
const int FLOWER = 2;
const int WHITE = 3;
const int REDSPIN = 4;

//booleans
bool isOn = false; //making sure the state is triggered only once, and not every time the board is tilted

void setup() {
  
  Serial.begin(9600); // Setup serial port.
  CircuitPlayground.begin(); // Setup Circuit Playground library.

  //Accelerometer settings
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_16_G);   // Put in 2, 4, 8 or 16 G for sensitivity. The lower the number, the more sensitive it is.
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD); //detect the number of clicks from 0 to 2. The lower the number, the more sensitive it is.
  
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), dropDetection, FALLING); // have a procedure called when a tap is detected
}

//-------------------------------------------------------------------------------Animations---------------------------------------------------------
void rainbowSpin() {
  
  //Every time the rainbow counter increases, the circuit playground wil increase in the number of lights.
  //Go the other direction: If you want to reverse the diction, put 'rainbow--' instead to make it count down.
  rainbow++; 

  //Once the counter reaches 11, the rainbow resets to 0 and clears the pixels on the board so it can start over. 
  //Go the other direction: Change  '11' to '0', and 'rainbow = 10'.
  if (rainbow == 11) {
    rainbow = 0;
    CircuitPlayground.clearPixels();
  }

  //The following line of code sets the light number and color.
  CircuitPlayground.setPixelColor(rainbow, CircuitPlayground.colorWheel(25 * rainbow));
}

void flowerBlink() {
  //There are 2 types of animation I made for flowerBlink. One is for the white and pink petals to spin in a circle, and the other is to have them stay in place and blink.
  //If you want to switch between the animations, just flip the switch on circuit playground.

  //Flower spin
  if (CircuitPlayground.slideSwitch()) { //if the switch is flipped, this animation will play. Otherwise, Flower blink will play
    //To change the direction it spins, follow the direction given in rainbowSpin().
  whitePetals++;
  pinkPetals++;

  if (whitePetals > 11) { //you can change the animation by playing around with these numbers and when the white or pink petals will reset
    whitePetals = 0;
    CircuitPlayground.clearPixels();
  }
  if (pinkPetals > 12){
    pinkPetals = -1;
    CircuitPlayground.clearPixels();
  }

  CircuitPlayground.setPixelColor(whitePetals, 255, 255, 255);
  CircuitPlayground.setPixelColor(pinkPetals, 255, 50, 100);
  
  } else { 
    //Flower blink

    CircuitPlayground.clearPixels(); //turn this off if you don't want it to blink
    delay(500); //this number controls how long the lights turn off
    
  CircuitPlayground.setPixelColor(0, 255, 255, 255);
  CircuitPlayground.setPixelColor(1, 255, 50, 100);
  CircuitPlayground.setPixelColor(2, 255, 255, 255);
  CircuitPlayground.setPixelColor(3, 255, 50, 100);
  CircuitPlayground.setPixelColor(4, 255, 255, 255);
  CircuitPlayground.setPixelColor(5, 255, 50, 100);
  CircuitPlayground.setPixelColor(6, 255, 255, 255);
  CircuitPlayground.setPixelColor(7, 255, 50, 100);
  CircuitPlayground.setPixelColor(8, 255, 255, 255);
  CircuitPlayground.setPixelColor(9, 255, 50, 100);
  delay(1000); //this number controls how long the lights stay on

  } 
}

void pureWhite() {
  
  //Every pixel will be white
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);
  }
}

void redSpin() {
  //This is the same code as rainbowSpin(), except the only color is red. If you want to reverse the direction, follow the instructions in rainbowSpin().
  red++; 
  
  if (red == 10) {
    red = 0;
    CircuitPlayground.clearPixels();
  }

  //To change the color, change the last 3 numbers in the brackets to the rgb values.
  CircuitPlayground.setPixelColor(red, 255, 0, 0);
}

//-------------------------------------------------------------------------------Accelerometer Detection---------------------------------------------------------

void dropDetection(void) {
  //Rather than sensing freefall, I made the accelerometer detect when it impacts something. To avoid it beeping with every little tap, I decreased the sensitivity to 16G in the Setup section.
  
  Serial.print("Tap! "); //This is to troubleshoot in the serial monitor to see if the accelerometer detects being hit
  CircuitPlayground.playTone(700, 1000); //the first number controls pitch and the second controls duration.

}

void tiltDetection(void) {
  //Declare XYZ
  float X = CircuitPlayground.motionX();
  float  Y = CircuitPlayground.motionY();
  float  Z = CircuitPlayground.motionZ();

  //Printing the XYZ coordinates for troubleshooting
  Serial.print("X: ");
  Serial.print(X);
  Serial.print("  Y: ");
  Serial.print(Y);
  Serial.print("  Z: ");
  Serial.println(Z);

  //Adjust the directions accordingly. The current direction is when the usb cable is facing me, so switch directions if you want the board facing another way.
  //You can also change the animation that plays by editing the number of the state (you can find the corresponding animation in the global variables
  if (X < -8 && Y < 0){
    Serial.print("left");
    if (isOn == false){
      isOn = true;
      state = 1;
    }
    delay(500);
  }
  
  if (X > 8 && Y < 0) {
    Serial.print("right");
    if (isOn == false){
      isOn = true;
      state = 2;
    }
    delay(500);
  }
  
  if (X < 0 && Y > 8 && Z < 0) {
    Serial.print("up");
    if (isOn == false){
      isOn = true;
      state = 3;
    }
  }
  
  if (X < 0 && Y < -8 && Z < 1) {
    Serial.print("down");
    if (isOn == false){
      isOn = true;
      state = 4;
    }
  }

}

//-------------------------------------------------------------------------------Compilation---------------------------------------------------------

void loop() {
  //Everything is compiled here.
 
  tiltDetection();
  //dropDetection();
  
  switch (state) {
    
    case NEUTRAL:
    CircuitPlayground.clearPixels();
    if (CircuitPlayground.leftButton()) state = 4;
    if (CircuitPlayground.rightButton()) state = 1;
    isOn = false;
    break;
    
    case RAINBOW:
      rainbowSpin();
      if (CircuitPlayground.leftButton()) state = 0;
      if (CircuitPlayground.rightButton()) state = 2;
      isOn = false;
      break;

    case FLOWER:
      flowerBlink();
      if (CircuitPlayground.leftButton()) state = 1;
      if (CircuitPlayground.rightButton()) state = 3;
      isOn = false;
      break;

    case WHITE:
      pureWhite();
      if (CircuitPlayground.leftButton()) state = 2;
      if (CircuitPlayground.rightButton()) state = 4;
      isOn = false;
      break;

    case REDSPIN:
      redSpin();
      if (CircuitPlayground.leftButton()) state = 3;
      if (CircuitPlayground.rightButton()) state = 0;
      isOn = false;
      break;
  }
  

  delay(100);
}
