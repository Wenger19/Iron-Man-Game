#include <LiquidCrystal.h>
 int SwipePin = A2;
 
 int EasyPin = 18;
 int MedPin = 2;
 int HardPin = 3;
 int BluePin = 19;
 int WhitePin = 21;
 int BuzzerPin = 8;
 int GreenLEDPin = 7;
 int YellowLEDPin = 6;
 int RedLEDPin = 5;
 int BlueLEDPin = 4; 
 
 int ranNum = 0;
 int ranMax = 8;
 int ranMin = 4;
 
 int SwipeV;
 int Swipes;
 
 bool TimesUp;
 bool LvlSelect;
 bool Gameplay;
 
 bool Easy;
 bool Med;
 bool Hard;
 bool Blue;
 bool White;
 
 bool EasyGP;
 bool MedGP;
 bool HardGP;
 
 int GameClock10;
 int pin1;
 int pin2;
 int ones;
 int tens;
 int L;

 int countones;
 int Lives;      
 bool Block = 1;
 bool AtkEnemy;
 int CursorLT;
 int FlashTime;
 bool OutOfLives;
 int Score;
 
LiquidCrystal lcd(52, 50, 48, 46, 44, 51);

byte Heart[8] = {
0b00000,
0b01010,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000,
0b00000
};


void setup() {
  
 randomSeed(analogRead(0));
 pinMode(SwipePin,INPUT);
 lcd.begin(16, 2);
 lcd.createChar(0, Heart);
 lcd.setCursor(0, 0);                       
 lcd.print("The Avengineers");
 lcd.setCursor(1, 1);                       
 lcd.print("Iron Man Game");
 delay(3500);
 lcd.clear();
 
 attachInterrupt(0, Yellow_ISR, RISING);
 attachInterrupt(1, Red_ISR, RISING);
 attachInterrupt(4, Blue_ISR, RISING);
 attachInterrupt(5, Green_ISR, RISING);
 attachInterrupt(2, White_ISR, RISING);

 for (int i = 30; i <= 43 ; i++)
{
 pinMode(i, OUTPUT);                //Set all pins from 0 to 13 as OUTPUT
}
 
 pinMode(7, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(8, OUTPUT);
 
 pinMode(19, INPUT);
 pinMode(3, INPUT);
 pinMode(18, INPUT);
 pinMode(2, INPUT);
 pinMode(21, INPUT);

}

const int number[11] = {0b1000000, 0b1001111, 0b0010010, 0b0000110, 0b0001101, 0b0100100, 0b0100000, 0b1001110, 0b0000000, 0b0000100, 0b1111111};
// Number array from 0-9

  void display_tens(const int tens)
{
  if (Lives > 0)
  {
  int pin1, a, ones;   
  for (pin1 = 30, a = 0; pin1 < 37; pin1++, a++) // tens = pin1
  {
    digitalWrite(pin1, bitRead(number[tens], a));
  }
  for (ones = 0; ones < 10; ones++)         // Increments Ones Place 7 SEG
  {
    display_ones(ones);
    delay(900);
    countones = countones + 1;
    lcd.clear();
    
    if (Lives > 0)
    {
      for (L=10;L<=CursorLT;L++)
      {
          lcd.setCursor(L, 0);
          lcd.write(byte(0));

          lcd.setCursor(0, 0);  
          lcd.print("Swipes: ");
          lcd.print(Swipes);

          lcd.setCursor(0, 1);
          lcd.print("Score: ");
          lcd.print(Score);
      }
    }
    else if (Lives <= 0)
    {
          EasyGP = 0;
          MedGP = 0;
          HardGP = 0;
          tone(BuzzerPin, 400, 500);
          tone(BuzzerPin, 400, 250);
          lcd.clear();
          lcd.setCursor(4, 0);  
          lcd.print("Game Over");
          delay(4500);
          lcd.clear();
          TimesUp = 1;
          Gameplay = 0;
          break;
     }

    if (countones == FlashTime)
    {
    AtkEnemy = digitalRead(ranNum);
      if (AtkEnemy == HIGH)
      {
        tone(BuzzerPin, 200, 500);
        Lives = Lives-1;
        CursorLT = CursorLT-1;
      }
      
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);  
    delay(50);

    ranNum = random(ranMin, ranMax);
    digitalWrite(ranNum,HIGH);
    countones = 0;
    }
    else if (ones == 0 && tens == 0)
    {
        ranNum = random(ranMin, ranMax);
        digitalWrite(ranNum,HIGH);
        countones = 0;
    }
  }
}
}


void display_ones(const int x)
{ 
  int pin2, b;
  for (pin2 = 37, b = 0; pin2 <= 43; pin2++, b++) // ones = pin2
  {
    digitalWrite(pin2, bitRead(number[x], b));
  }
 }

void loop() {

  for (int i=30; i<=43; i++) 
  {
    digitalWrite(i, HIGH);
  }

 delay(150);
 SwipeV = analogRead(SwipePin);
 Easy = digitalRead(EasyPin);
 Med = digitalRead(MedPin);
 Hard = digitalRead(HardPin);
 Blue = digitalRead(BluePin);
 White = digitalRead(WhitePin);
 delay(150);
 
  if (SwipeV <= 300)                        // Detect Swipe
 {
  delay(100);
  Swipes = Swipes + 1;
  TimesUp = 0;
  LvlSelect = 1;
  delay(100);
  lcd.clear();
 }

 if (TimesUp == 1 || Swipes == 0)            // Ready for New Game
   {                                         // Waiting for Swipe
    Score = 0;
    lcd.setCursor(2, 0);                       
    lcd.print("Please Swipe");
    
    for (int i=30; i<=43; i++) 
    {
      digitalWrite(i, HIGH);
    }
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
   }

 else if (LvlSelect == 1)                    // Level Selection
  {                                          // Waiting for Difficulty Button Press
    lcd.setCursor(0, 0);                       
    lcd.print("Please Select a");

    lcd.setCursor(5, 1);                       
    lcd.print("Level");
      
      if (Easy == 1)                         // Easy Countdown
      {
        GameClock10 = 9;
        EasyGP = 1;
        Lives = 6;
        CursorLT = 15;
        FlashTime = 10;
        lcd.clear();
        LvlSelect = 0;
        lcd.setCursor(6, 0);                       
        lcd.print("Easy");
        lcd.setCursor(0, 1);                       
        lcd.print("Game Starts in 5");
        delay(3000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("5");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("4");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("3");
        delay(1000);
        
        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("2");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("1");
        delay(1000);

        lcd.clear();
        lcd.setCursor(7, 0);                       
        lcd.print("Go!");
        delay(1000);

        Gameplay = 1;
        lcd.clear();
      }
      else if (Med == 1)                     // Medium Countdown
      {
        GameClock10 = 6;
        MedGP = 1;
        Lives = 4;
        CursorLT = 13;
        FlashTime = 7;
        lcd.clear();
        LvlSelect = 0;
        lcd.setCursor(5, 0);                       
        lcd.print("Medium");
        lcd.setCursor(0, 1);                       
        lcd.print("Game Starts in 5");
        delay(3000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("5");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("4");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("3");
        delay(1000);
        
        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("2");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("1");
        delay(1000);

        lcd.clear();
        lcd.setCursor(7, 0);                       
        lcd.print("Go!");
        delay(1000);

        Gameplay = 1;
        lcd.clear();
      }
      else if (Hard == 1)                      // Hard Countdown
      {
        GameClock10 = 4;
        HardGP = 1;
        Lives = 3;
        CursorLT = 12;
        FlashTime = 4;
        lcd.clear();
        LvlSelect = 0;
        lcd.setCursor(6, 0);                       
        lcd.print("Hard");
        lcd.setCursor(0, 1);                       
        lcd.print("Game Starts in 5");
        delay(3000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("5");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("4");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("3");
        delay(1000);
        
        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("2");
        delay(1000);

        lcd.clear();
        lcd.setCursor(8, 0);                       
        lcd.print("1");
        delay(1000);

        lcd.clear();
        lcd.setCursor(7, 0);                       
        lcd.print("Go!");
        delay(1000);

        Gameplay = 1;
        lcd.clear();
      }
  }
  
 while (Gameplay == 1)               // Gameplay
 {
 
  if (EasyGP == 1)                // Easy Gameplay
  {
        if (White == 1)
    {
      Score = Score + 250;
    }
    
    for (int tens = 0; tens <= GameClock10; tens++)
      if (tens < GameClock10)
      {
          display_tens(tens);
      }
      else if (tens == GameClock10)
      {
      EasyGP = 0;
      MedGP = 0;
      HardGP = 0;
      tone(BuzzerPin, 400, 500);
      tone(BuzzerPin, 400, 250);
      lcd.clear();
      lcd.setCursor(4, 0);  
      lcd.print("Game Over");
      delay(4500);
      lcd.clear();
      TimesUp = 1;
      Gameplay = 0;
      }
  }
  else if (MedGP == 1)              // Medium Gameplay
  {
    for (int tens = 0; tens <= GameClock10; tens++)
      if (tens < GameClock10)
      {
          display_tens(tens);
      }
      else if (tens == GameClock10)
      {
      EasyGP = 0;
      MedGP = 0;
      HardGP = 0;
      tone(BuzzerPin, 400, 500);
      tone(BuzzerPin, 400, 250);
      lcd.clear();
      lcd.setCursor(4, 0);  
      lcd.print("Game Over");
      delay(4500);
      lcd.clear();
      TimesUp = 1;
      Gameplay = 0;
      }
  }
  
  else if (HardGP == 1)             // Hard Gameplay
  {
  for (int tens = 0; tens <= GameClock10; tens++)
    if (tens < GameClock10)
    {
        display_tens(tens);
    }
    else if (tens == GameClock10)
    {
      EasyGP = 0;
      MedGP = 0;
      HardGP = 0;
      tone(BuzzerPin, 400, 500);
      tone(BuzzerPin, 400, 250);
      lcd.clear();
      lcd.setCursor(4, 0);  
      lcd.print("Game Over");
      delay(4500);
      lcd.clear();
      TimesUp = 1;
      Gameplay = 0;
    }
  }

}
}

void Yellow_ISR() 
  {
    delay(50);
    digitalWrite(BuzzerPin, HIGH);
    delay(5000);
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(YellowLEDPin, LOW);
  }
void Red_ISR() 
  {
    delay(50);
    digitalWrite(BuzzerPin, HIGH);
    delay(5000);
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(RedLEDPin, LOW);
  }
void Blue_ISR() 
  {
    delay(50);
    digitalWrite(BuzzerPin, HIGH);
    delay(5000);
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(BlueLEDPin, LOW);
  }
void Green_ISR() 
  {
    delay(50);
    digitalWrite(BuzzerPin, HIGH);
    delay(5000);
    digitalWrite(BuzzerPin, LOW);
    digitalWrite(GreenLEDPin, LOW);
  }
void White_ISR() 
  {
    delay(100);
    Score = Score + 250;
    delay(100);
    digitalWrite(BuzzerPin, HIGH);
    delay(2500);
    digitalWrite(BuzzerPin, LOW);
  }
