/* Simple Stepper Motor Homing code
 
Created by Yvan / https://Brainy-Bits.com
This code is in the public domain...
You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/

// Define the Pins used
#define step_pin 5    // Pin 5 connected to Steps pin on EasyDriver
#define dir_pin 6     // Pin 6 connected to Direction pin
#define MS1 2         // Pin 3 connected to MS1 pin
#define MS2 3         // Pin 4 connected to MS2 pin
#define sleep_pin 8   // Pin 8 connected to SLEEP pin

#define x_pin A0      // Pin A0 connected to joystick x axis pin

#define home_switch 9 // Pin 9 connected to Home Switch (MicroSwitch)

int direction;    // Variable to set Rotation (CW-CCW) of the motor
int steps;        // Used to set HOME position after Homing is completed

void pulse(){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(20);         // Minimum STEP Pulse Width 1.0uS
    digitalWrite(step_pin, LOW);       // Step pulse (rising edge).
} 

void setup() {
   pinMode(MS1, OUTPUT);
   pinMode(MS2, OUTPUT);
   pinMode(dir_pin, OUTPUT);
   pinMode(step_pin, OUTPUT);
   pinMode(sleep_pin, OUTPUT);
   
   pinMode(x_pin, INPUT);

   pinMode(home_switch, INPUT_PULLUP);
   
   digitalWrite(sleep_pin, HIGH);  // Wake up EasyDriver
   delay(5);  // Wait for EasyDriver wake up
   

/* Configure type of Steps on EasyDriver:
// MS1 MS2
//
// LOW LOW = Full Step //
// HIGH LOW = Half Step //
// LOW HIGH = A quarter of Step //
// HIGH HIGH = An eighth of Step //
*/

   digitalWrite(MS1, LOW);      // Configures to Full Steps
   digitalWrite(MS2, LOW);    // Configures to Full Steps



// Start Homing procedure of Stepper Motor at startup

  while (digitalRead(home_switch)) {  // Do this until the switch is activated   
    digitalWrite(dir_pin, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(step_pin, HIGH);
    delay(3);                       // Delay to slow down speed of Stepper
    digitalWrite(step_pin, LOW);
    delay(3);   
}

  while (!digitalRead(home_switch)) { // Do this until the switch is not activated
    digitalWrite(dir_pin, LOW); 
    digitalWrite(step_pin, HIGH);
    delay(10);                          // More delay to slow even more while moving away from switch
    digitalWrite(step_pin, LOW);
    delay(10);   
  }

  steps=0;  // Reset position variable to zero

  digitalWrite(dir_pin, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is clockwise).
pulse();
  /*Slowly turns the motor 1600 steps*/
  for (int i = 0; i < 20; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(700);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(700);
  }
   
}

void loop() {

// Enable movement of Stepper Motor using the Joystick

digitalWrite(dir_pin, LOW); //Writes the direction to the EasyDriver DIR pin. (HIGH is clockwise).
pulse();
  /*Slowly turns the motor 1600 steps*/
  for (int i = 0; i < 1820; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(700);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(700);
  }
 
  delay(2000); //Pauses for a second (the motor does not need to pause between switching direction, so you can safely remove this)
 
  digitalWrite(dir_pin, HIGH); //Writes the direction to the EasyDriver DIR pin. (LOW is counter clockwise).
  pulse();
  /*Turns the motor fast 1600 steps*/
  for (int i = 0; i < 1820; i++){
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(700);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(700);
  }

  delay(2000);
}
   
