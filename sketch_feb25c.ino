
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int inPin = 3;
const int touch = 4;
const int pinSound = A0;
const int audio8 = 8;

int note = 1200;
int thresholdValue = 760;

int dotLen = 100;     // length of the morse code 'dot'
int dashLen = dotLen * 3;

int timer = 0;
byte truth = 0;
byte truth2 = 1;

int code[] = {2, 2, 2, 2, 2};
int counter = 0;
int counter_let = 0;

String message = "";
String message2 = "";

String letters_num[] = {"01222",//a
                        "10002",//b
                        "10102",//c
                        "10022",//d
                        "02222",//e
                        "00102",//f
                        "11022",//g
                        "00002",//h
                        "00222",//i
                        "01112",//j
                        "10122",//k
                        "01002",//l
                        "11222",//m
                        "10222",//n
                        "11122",//o
                        "01102",//p
                        "11012",//q
                        "01022",//r
                        "00022",//s
                        "12222",//t
                        "00122",//u
                        "00012",//v
                        "01122",//w
                        "10012",//x
                        "10112",//y
                        "11002"//z
                       };

char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

//byte status_button = LOW;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);         // Use serial for debugging
  //Serial.print(sizeof(letters));
  //digitalWrite(inPin, HIGH);  // Turn on 20k pullup resistors to simplify switch input
}

void loop() {

  while (digitalRead(inPin) == HIGH) {
    timer++;
    Serial.print(timer);
    delay(100);
  }

  if (digitalRead(touch) == HIGH ) {
    readArray();
    resetArray();
    Serial.print("\n");
    delay(1000);

  }
  if (analogRead(pinSound) > thresholdValue) {
    stupidMessage();
  }

  if (counter > 5) {
    lcd.clear();
    lcd.print("Touch Sensor");
    delay(1000);
  }

  if (timer > 0 && timer < 5) {
    dot();
  }
  else if (timer == 0) {
    lcd.clear();
  }
  else {
    dash();
  }
  timer = 0;
}

void dot() {
  code[counter] = 0;
  counter++;
  //lcd.clear();
  //lcd.print("DOT");
  //delay(100);
}

void dash() {
  code[counter] = 1;
  counter++;
  //lcd.clear();
  //lcd.print("DASH");
  //delay(100);
}

void readArray() {
  String mystring = "";
  for (int i = 0; i < 5; i++) {
    mystring += code[i];
  }
  char let = GetChar(mystring);
  Serial.print(mystring);
  message += let;
  message2 += let;

  Serial.print(message.length());

  if (message.length() <= 16) {
    lcd.print(message);
  }
  else {
    message = "";
  }
}

void resetArray() {
  for (int i = 0; i < 5; i++) {
    code[i] = 2;
  }
  counter = 0;
}

char GetChar(String mystring) {
  char let = ' ';
  while (truth == 0 && counter_let < sizeof(letters) - 1) {
    if (mystring == letters_num[counter_let]) {
      truth = 1;
    }
    else {
      counter_let++;
    }
  }
  if (truth) {
    let = letters[counter_let];
    Serial.print(let);
  }
  else {
    Serial.print("Not a letter");
  }
  counter_let = 0;
  truth = 0;
  return let;
}

void hearMessage() {
  for (int i = 0; i < message2.length(); i++) {
    char stuff = message2.charAt(i);
    switch (stuff) {
      case 'A':
        MorseDot();
        MorseDash();
        break;
      case 'B':
        MorseDash();
        MorseDot();
        MorseDot();
        MorseDot();
        break;
      case 'C':
        MorseDash();
        MorseDot();
        MorseDash();
        MorseDot();
        break;
      case 'D':
        MorseDash();
        MorseDash();
        MorseDot();
        break;
      case 'E':
        MorseDot();
        break;
      case 'F':
        MorseDot();
        MorseDot();
        MorseDash();
        MorseDot();
        break;
      case 'G':
        MorseDash();
        MorseDash();
        MorseDot();
        break;
      case 'H':
        MorseDot();
        MorseDot();
        MorseDot();
        MorseDot();
        break;
      case 'I':
        MorseDot();
        MorseDot();
        break;
      case 'J':
        MorseDot();
        MorseDash();
        MorseDash();
        MorseDash();
        break;
      case 'K':
        MorseDash();
        MorseDot();
        MorseDash();
        break;
      case 'L':
        MorseDot();
        MorseDash();
        MorseDot();
        MorseDot();
        break;
      case 'M':
        MorseDash();
        MorseDash();
        break;
      case 'N':
        MorseDash();
        MorseDot();
        break;
      case 'O':
        MorseDash();
        MorseDash();
        MorseDash();
        break;
      case 'P':
        MorseDot();
        MorseDash();
        MorseDash();
        MorseDot();
        break;
      case 'Q':
        MorseDash();
        MorseDash();
        MorseDot();
        MorseDash();
        break;
      case 'R':
        MorseDot();
        MorseDash();
        MorseDot();
        break;
      case 'S':
        MorseDot();
        MorseDot();
        MorseDot();
        break;
      case 'T':
        MorseDash();
        break;
      case 'U':
        MorseDot();
        MorseDot();
        MorseDash();
        break;
      case 'V':
        MorseDot();
        MorseDot();
        MorseDot();
        MorseDash();
        break;
      case 'W':
        MorseDot();
        MorseDash();
        MorseDash();
        break;
      case 'X':
        MorseDash();
        MorseDot();
        MorseDot();
        MorseDash();
        break;
      case 'Y':
        MorseDash();
        MorseDot();
        MorseDash();
        MorseDash();
        break;
      case 'Z':
        MorseDash();
        MorseDash();
        MorseDot();
        MorseDot();
        break;
      default:
        // If a matching character was not found it will default to a blank space
        break;
    }
  }
}

void MorseDot() {
  tone(audio8, note, dotLen); // start playing a tone
  delay(dotLen);              // hold in this position
}

void MorseDash() {
  tone(audio8, note, dashLen);  // start playing a tone
  delay(dashLen);
}
void stupidMessage() {

  lcd.clear();
  lcd.print("Hear message?");
  delay(1000);
  while (truth2) {
    if (digitalRead(inPin) == HIGH) {
      lcd.print("Yes");
      delay(1000);
      hearMessage();
      truth2 = 0;
    }
    else if (digitalRead(touch) == HIGH) {
      lcd.print("No");
      delay(1000);
      truth2 = 0;
    }
  }
  truth2 = 1;
  cleanMessage();
}
void cleanMessage() {
  lcd.clear();
  lcd.print("Clean Message?");
  delay(1000);
  while (truth2) {
    if (digitalRead(inPin) == HIGH) {
      lcd.print("Yes");
      delay(1000);
      cleanMessageHelper();
      truth2 = 0;
    }
    else if (digitalRead(touch) == HIGH) {
      lcd.print("No");
      delay(1000);
      truth2 = 0;
    }
  }
  truth2 = 1;

}
void cleanMessageHelper() {

  lcd.clear();
  Serial.print("Message cleaned\n");
  lcd.print("Message cleaned");
  delay(1000);
  
  message = "";
  message2 = "";
}

