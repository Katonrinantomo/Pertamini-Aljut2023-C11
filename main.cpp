#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
byte customChar[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[cols] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


int cursor = 3;

void start_display();
void reset();

void setup()
{
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
  start_display();
}

void loop()
{
  char key = keypad.getKey();
  if(key == '*') {
    reset();
    return;
  }

  if(key == '#') {
    bool but = true;
    lcd.clear();
    lcd.print("Harap Menunggu");
    do {
    if (digitalRead(11) == LOW) {
      but = false;
    }
    } while(but);
    // lcd.createChar(0, customChar);
    // lcd.write((byte)0);
    digitalWrite(10, HIGH);
    for (int i = 0; i <= 1000; i++) {
      lcd.setCursor(0, 1);
      lcd.print(i);
      delay(1);
    }
    digitalWrite(10, LOW);
  } 

  if(cursor > 9) {
    return;
  }

  if (key != NO_KEY) {
  lcd.setCursor(cursor, 1);
  lcd.print(key);
  cursor++;
  }

}

void start_display() {
  lcd.setCursor(0, 0);
  lcd.print("Masukkan Nominal");
  lcd.setCursor(0, 1);
  lcd.print("Rp. ");
}

void reset() {
    digitalWrite(10, LOW);
    lcd.clear();
    start_display();
    cursor = 3;
}