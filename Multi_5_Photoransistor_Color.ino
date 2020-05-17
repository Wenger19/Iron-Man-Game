

const int NUMreadings = 10;     //Averaging size
int readings1[NUMreadings];
int readings2[NUMreadings];//
int readings3[NUMreadings];
int readings4[NUMreadings];//
int readings5[NUMreadings];//
int trigsep = 300;               //Threshold to trigger interrupts

int PHOTO1 = 0;                 //Current reading
int IndexPT1 = 0;               //Index of current reading
int avgPT1 = 0;                 //Current average
int totalPT1 = 0;               //The running total

int PHOTO2 = 0;                 //Current reading
int IndexPT2 = 0;               //Index of current reading
int avgPT2 = 0;                 //Current average
int totalPT2 = 0;               //The running total

int PHOTO3 = 0;                 //Current reading
int IndexPT3 = 0;               //Index of current reading
int avgPT3 = 0;                 //Current average
int totalPT3 = 0;               //The running total

int PHOTO4 = 0;                 //Current reading
int IndexPT4 = 0;               //Index of current reading
int avgPT4 = 0;                 //Current average
int totalPT4 = 0;

int PHOTO5 = 0;                 //Current reading
int IndexPT5 = 0;               //Index of current reading
int avgPT5 = 0;                 //Current average
int totalPT5 = 0;

int green = 255;                  // LED Strip colors
int blue = 255;
int red = 255;

int colorburst = 1500;           //Delay time for color after a hit

int photo1IN = A8;             // Phototransistor pin delcation
int photo2IN = A9;
int photo3IN = A10;
int photo4IN = A11;
int photo5IN = A12;

int greenPin = 45;              //LED strip ppin declaration
int bluePin = 44;
int redPin = 46;

int diff1 = 0;
int diff2 = 0;
int diff3 = 0;
int diff4 = 0;
int diff5 = 0;

void setup() {
  delay(10);
  Serial.begin(9600);
  //pinMode(photo1IN, INPUT);     // phototransistor input declaration

  pinMode(greenPin, OUTPUT);    // pin modes for LED Strip
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);

  for (PHOTO1 = 0; PHOTO1 < NUMreadings; PHOTO1++) {    //resets array
    readings1[PHOTO1] = 0;
  }
  for (PHOTO2 = 0; PHOTO2 < NUMreadings; PHOTO2++) {    //resets array
    readings2[PHOTO2] = 0;
  }
  for (PHOTO3 = 0; PHOTO3 < NUMreadings; PHOTO3++) {    //resets array
    readings3[PHOTO1] = 0;
  }
  for (PHOTO4 = 0; PHOTO4 < NUMreadings; PHOTO4++) {    //resets array
    readings4[PHOTO4] = 0;
  }
  for (PHOTO5 = 0; PHOTO5 < NUMreadings; PHOTO5++) {    //resets array
    readings5[PHOTO5] = 0;
  }
}
void loop() {
  //delay(10);
  analogWrite(greenPin, 0);
  analogWrite(redPin, 0);
  analogWrite(bluePin, 0);

  totalPT1 = totalPT1 - readings1[IndexPT1];     //Smoothing process
  readings1[IndexPT1] = analogRead (photo1IN);
  totalPT1 = totalPT1 + readings1[IndexPT1];
  IndexPT1 = IndexPT1 + 1;
  if (IndexPT1 >= NUMreadings) {
    IndexPT1 = 0;
  }

  totalPT2 = totalPT2 - readings2[IndexPT2];     //Smoothing process
  readings2[IndexPT2] = analogRead (photo2IN);
  totalPT2 = totalPT2 + readings2[IndexPT2];
  IndexPT2 = IndexPT2 + 1;
  if (IndexPT2 >= NUMreadings) {
    IndexPT2 = 0;
  }

  totalPT3 = totalPT3 - readings3[IndexPT3];     //Smoothing process
  readings3[IndexPT3] = analogRead (photo3IN);
  totalPT3 = totalPT3 + readings3[IndexPT3];
  IndexPT3 = IndexPT3 + 1;
  if (IndexPT3 >= NUMreadings) {
    IndexPT3 = 0;
  }
  totalPT4 = totalPT4 - readings4[IndexPT4];     //Smoothing process
  readings4[IndexPT4] = analogRead (photo4IN);
  totalPT4 = totalPT4 + readings4[IndexPT4];
  IndexPT4 = IndexPT4 + 1;
  if (IndexPT4 >= NUMreadings) {
    IndexPT4 = 0;
  }
  totalPT5 = totalPT5 - readings5[IndexPT5];     //Smoothing process
  readings5[IndexPT5] = analogRead (photo5IN);
  totalPT5 = totalPT5 + readings5[IndexPT5];
  IndexPT5 = IndexPT5 + 1;
  if (IndexPT5 >= NUMreadings) {
    IndexPT5 = 0;
  }

  avgPT1 = totalPT1 / NUMreadings;          //Window Average or smoothing
  PHOTO1 = analogRead(photo1IN);            //Raw analong value
  diff1 = PHOTO1 - avgPT1;

  avgPT2 = totalPT2 / NUMreadings;          //Window Average or smoothing
  PHOTO2 = analogRead(photo2IN);            //Raw analong value
  diff2 = PHOTO2 - avgPT2;                   //diff1erence between the two.

  avgPT3 = totalPT3 / NUMreadings;          //Window Average or smoothing
  PHOTO3 = analogRead(photo3IN);            //Raw analong value
  diff3 = PHOTO3 - avgPT3;

  avgPT4 = totalPT4 / NUMreadings;          //Window Average or smoothing
  PHOTO4 = analogRead(photo4IN);            //Raw analong value
  diff4 = PHOTO4 - avgPT4;

  avgPT5 = totalPT5 / NUMreadings;          //Window Average or smoothing
  PHOTO5 = analogRead(photo5IN);            //Raw analong value
  diff5 = PHOTO5 - avgPT5;


  if (PHOTO1 >= trigsep + avgPT1) {
    analogWrite(redPin, red);
    delay(colorburst);
    Serial.println("Sent1");
    analogWrite(redPin, 0);
  }
  if (PHOTO2 <= -trigsep + avgPT2) {
    analogWrite(bluePin, blue);
    delay(colorburst);
    Serial.println("Sent2");
    analogWrite(bluePin, 0);
  }
  if (PHOTO3 >= trigsep + avgPT3) {
    analogWrite(greenPin, green);
    delay(colorburst);
    Serial.println("Sent3");
    analogWrite(greenPin, 0);
  }
  if (PHOTO4 >= trigsep + avgPT4) {
    green = 127;
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    delay(colorburst);
    Serial.println("Sent4");
    analogWrite(greenPin, 0);
    analogWrite(redPin, 0);
    green = 255;
  }
  if (PHOTO5 >= trigsep + avgPT5) {
    analogWrite(bluePin, blue);
    analogWrite(redPin, red);
    delay(colorburst);
    Serial.println("Sent5");
    analogWrite(bluePin, 0);
    analogWrite(redPin, 0);
  }



  //Serial.print(" Input photo_1 signal:  ");
  Serial.print("photo1: ");
  Serial.print(PHOTO1);
  Serial.print("     ");
  Serial.print(avgPT1);
  Serial.print("     ");
  Serial.print(diff1);
  Serial.print("   photo2: ");
  Serial.print(PHOTO2);
  Serial.print("     ");
  Serial.print(avgPT2);
  Serial.print("     ");
  Serial.print(diff2);
  Serial.print("  photo3: ");
  Serial.print(PHOTO3);
  Serial.print("     ");
  Serial.print(avgPT3);
  Serial.print("     ");
  Serial.print(diff3);
  Serial.print("  photo4: ");
  Serial.print(PHOTO4);
  Serial.print("     ");
  Serial.print(avgPT4);
  Serial.print("     ");
  Serial.print(diff4);
  Serial.print("  photo5: ");
  Serial.print(PHOTO5);
  Serial.print("     ");
  Serial.print(avgPT5);
  Serial.print("     ");
  Serial.println(diff5);

}
