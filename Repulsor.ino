// Setup NeoPixel using the NeoPixel library
#include <Adafruit_NeoPixel.h>
#define PIN 8
#define NUM_LIGHTS  12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, PIN, NEO_GRB + NEO_KHZ800);

// Declare variables for flex sensor and proximity sensor
int flex;
int flexMap;
int shoot = 13;

void setup() 
{
  pinMode(shoot, OUTPUT);
  strip.begin();
  strip.show();  
}

void loop() 
{
  // Read the flex sensor input
  flex = analogRead(A0);
  flexMap = map(flex, 0, 1024, 0, 255);
  delay(100);

  // if and else if statements are the ranges for OFF statement
  if(flexMap > 60)
  {
    uint32_t low = strip.Color(0, 0, 0); 
    uint32_t high = strip.Color(54, 54, 54); 
    for( int i = 0; i<NUM_LIGHTS; i++)
    {
        strip.setPixelColor(i, low);
        strip.show();
    }
    digitalWrite(shoot, low);
   }
   else if(flexMap < 40) 
   {
      uint32_t low = strip.Color(0, 0, 0); 
      uint32_t high = strip.Color(54, 54, 54); 
      for( int i = 0; i<NUM_LIGHTS; i++)
      {
        strip.setPixelColor(i, low);
        strip.show();
      } 
      digitalWrite(shoot, LOW);
   }

   // else statement to turn on NeoPixel and "shoot" 
   // with the proximity sensor
   else
   {
    uint32_t low = strip.Color(0, 0, 0); 
    uint32_t high = strip.Color(54, 54, 54); 
    for( int i = 0; i<NUM_LIGHTS; i++)
    {
      strip.setPixelColor(i,high);
      strip.show();
    }
      digitalWrite(shoot, HIGH); 
   }  
}
