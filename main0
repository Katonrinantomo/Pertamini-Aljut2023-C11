#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long myTime;
const byte RELAY = 10;
const byte BUTTON = 11;
const byte batasHarga = 7;
const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {9, 8, 7, 6}; 
byte colPins[cols] = {5, 4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

int cursor = 3;
char counter[batasHarga];
byte inputKey = 0;
float showNumber = 0;
int toRound;

void (* resetFunc) (void) = 0;

void setup()
{
  lcd.begin();         
  lcd.backlight();
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  digitalWrite(RELAY, HIGH);
  start_display("Masukkan Nominal","Input");
}

void loop()
{
  digitalWrite(RELAY, HIGH);
  char customKey = keypad.getKey();
  if (customKey=='#'){
    start_display("Silakan Isi","NozzleReady");
  } else if (customKey == '*') {
      // memset(counter, 0, sizeof(counter));
      // cursor = 3;
      // inputKey = 0;
      // showNumber = 0;
      // toRound = 0;
      resetFunc();
  } else if (customKey) {
    if (cursor <= 9){
    counter[inputKey]=customKey;
    lcd.setCursor(cursor,1);
    lcd.print(counter[inputKey]);
    inputKey++;
    cursor++;
    }
  }
  
  if ((int(showNumber) != 0) && (int(showNumber)%1000==0)) {
        toRound = int(showNumber)/1000;
  }
  if (digitalRead(BUTTON)==HIGH){
      int prCounter = atoi(counter);
      if (showNumber <= prCounter){
        digitalWrite(RELAY, LOW);
        myTime = millis();
        Serial.println(myTime);
        lcd.setCursor(0, 1);
        lcd.print(showNumber);
        showNumber+=100;
        delay(29);
        // showNumber+=(4.4*(toRound+1))*0.815-(toRound+1);
        // Serial.println((4.4*(toRound+1))*0.815-(toRound+1));
    }
  }
  
}

void start_display(char message[],char idleState[]) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  if (idleState=="Input") {
    lcd.print("Rp.");
  } else if (idleState=="NozzleReady") {
    lcd.clear();
    lcd.print(message);
    lcd.setCursor(0, 1);
    } else if (idleState=="End"){
      lcd.print("Terima Kasih");
    }
}
