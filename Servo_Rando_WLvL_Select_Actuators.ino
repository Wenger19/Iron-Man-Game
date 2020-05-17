// Randomly selects one of the six servos,runs it out and back, random selection 
// holds enemey out for desired amount of time
// with random lvl select: EASY, MED, HARD pushbuttons
// with stepper motor 1/5 turn on reset 

#include <Servo.h>
#include <CheapStepper.h>

Servo SERVO1;              //declaration of the servos to arduino 
Servo SERVO2;
Servo SERVO3;
Servo SERVO4;
Servo SERVO5;

CheapStepper Stepper1 (4,5,6,7);    // Declares stepper motor name and int pins
                                    // in1 = 4;... int4 = 7;
                                    
int steppos = 0;                    // Variable for stepper postion
boolean clockwise ;                 // Declares direction variable
int stepcount = 1;                  // Variable used in stepper turing

int pos = 35;   //angular postion declarations
int pos135 = 180;
int originalpos = 0;

int RANDOMSERVO = 0;                //Random number generator 
int randoSmax = 6; 
int randoSmin= 1;

int HARD = LOW;                     //Level select variables
int MED = LOW;
int EASY = LOW;
int lvlselect = 0;
int timer = 0;
int reset = 1;
int rumble = 0;
 
int enemeyexposed = 0;               //Time enemy is exposed
int IN_BT = 1000;                    //Time in between enemies poping out

void setup() {            
  pinMode(22,INPUT);                 // hard push button input pin 
  pinMode(24,INPUT);                 // med push button input pin 
  pinMode(26,INPUT);                 // easy push button input pin 
  
  SERVO1.attach(13);                  // Arudino pins for servo signals
  SERVO2.attach(12);                  // PWM!!!
  SERVO3.attach(11);
  SERVO4.attach(10);
  SERVO5.attach(9);
  randomSeed(analogRead(15)); // Starts random number generator at a random value
                              // For Random servo
  Serial.begin(9600); 
  Serial.println("You Must Select a Level By Pressing & Holding");
  Serial.println("     HARD    or    MED    or    EASY");
}

void loop() { 
      SERVO1.write(originalpos);
      SERVO2.write(originalpos);
      SERVO3.write(originalpos);
      SERVO4.write(originalpos);
      SERVO5.write(originalpos);
  HARD = digitalRead(22); // Reads digital pins attached to push buttons
  MED = digitalRead(26);
  EASY = digitalRead(30);
  delay(20);
  delay(IN_BT);           // Time in between each enemy poping out
  
                 // determines which level was selected, parameters for each are assigned here 
  if (EASY == HIGH && lvlselect == 0){ 
    lvlselect = 1;
    reset = 5;         // 15 second game clock
    enemeyexposed = 4500;
    IN_BT = 500; 
    rumble = 1;
    }
    else if (MED == HIGH && lvlselect == 0) {
    lvlselect = 2;     
    reset = 5;          // 10 second game clock
    enemeyexposed = 3000;
    IN_BT = 500; 
    rumble = 1;
    }
    else if (HARD == HIGH && lvlselect == 0) {
    lvlselect = 3;
    reset = 5;           // 5 second game clock
    enemeyexposed = 1500;
    IN_BT = 500; 
    rumble = 1;
    }
    else { lvlselect = lvlselect;}


  if (lvlselect > 0 && rumble == 1){
      Serial.println(" ");
      Serial.println("        GET READY TO RUMBLE IN:");
      Serial.println(" ");
      Serial.println("                    5 ");
      delay(800);
      Serial.println("                    4 ");
      delay(800); 
      Serial.println("                    3 ");
      delay(800);
      Serial.println("                    2 ");
      delay(800);
      Serial.println("                    1 ");
      delay(800);
      rumble = 0;
    }
    else {lvlselect = lvlselect;}
    

  if (lvlselect > 0){
    Serial.print("Level Selected: ");
  }
    else{
    Serial.println("Please Select a Level!"); 
    }

                // sets up the timer for how long each of will last. 
                // serial.prints can be removed and delay is necessary!
  if (lvlselect == 1 && timer < reset){
     RANDOMSERVO = random(randoSmin,randoSmax);  // picks a random integer between 1 - 6
     timer = timer +1;
     delay(15);
     Serial.print("EASY");
    }  
    else if (lvlselect == 2 && timer < reset){
       RANDOMSERVO = random(randoSmin,randoSmax);  // picks a random integer between 1 - 6
       timer = timer +1;
       delay(15);
       Serial.print("MED");
    } 
    else if (lvlselect == 3 && timer < reset){
       RANDOMSERVO = random(randoSmin,randoSmax);  // picks a random integer between 1 - 6
       timer = timer +1;
       delay(15);
       Serial.print("HARD");
    }
    else {
       timer = timer;
       }

  if (lvlselect > 0){
     Serial.print("     ");            // Prints random servo information.
     Serial.print("Random Servo: ");   
     Serial.println(RANDOMSERVO);
  }
  
                // Triggers randomly selected servo to set in motion
  if (RANDOMSERVO == 1){
    SERVO1.write(pos135);    
    delay(enemeyexposed);
    SERVO1.write(originalpos);
    }
    else if (RANDOMSERVO == 2){
      SERVO2.write(pos);
      delay(enemeyexposed);
      SERVO2.write(originalpos);
    }
    else if (RANDOMSERVO == 3){
      SERVO3.write(pos135);
      delay(enemeyexposed);
      SERVO3.write(originalpos);
    }
    else if (RANDOMSERVO == 4){
      SERVO4.write(pos);
      delay(enemeyexposed);
      SERVO4.write(originalpos);
    }
    else if (RANDOMSERVO == 5){
      SERVO5.write(pos135);
      delay(enemeyexposed);
      SERVO5.write(originalpos);
    }
    else {RANDOMSERVO = 0;}
     
                
  if (timer == reset) {   // resets prarameters for next button select. 
      EASY = LOW;
      MED = LOW;
      HARD = LOW;
      lvlselect = 0;
      RANDOMSERVO = 0;
      IN_BT = 2000;
      timer = 0;
      reset = 1;
      rumble = 0;
      SERVO1.write(originalpos);
      SERVO2.write(originalpos);
      SERVO3.write(originalpos);
      SERVO4.write(originalpos);
      SERVO5.write(originalpos);

      stepcount = stepcount++;
        for (steppos = 820*(stepcount-1); steppos < stepcount*820; steppos++){
        Stepper1.step(clockwise);
          if(steppos == stepcount*820){
            steppos = stepcount*820 + 1;
          }
          if (stepcount == 5){
            stepcount = 0;  
          }
         }

   }
      else {
      timer = timer; 
      reset = reset;
      
      }

}

  
    
    
  
  
       
