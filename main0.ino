#include <LiquidCrystal_I2C.h>                  //memanggil library LCD
#include <Keypad.h>                            //memanggil library Keypad
#include <Wire.h>                             //memanggil lirary serial komunikaai 

// Konfigurasi Modul

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);         // setting alamat 12C(0X27), besar karakter untuk LCD 16X2 

// Keypad
const byte ROWS = 4;
const byte COLUMNS = 4;
char keys[ROWS][COLUMNS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLUMNS] = {5, 4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLUMNS );


// Inisialisasi
#define RELAY 10
#define BUTTON 11
#define BUZZER 12
#define SHELL_BUTTON 13
char hargaBeli[7]; // Max 9999999 atau 7 Digit
byte cursor = 3;
byte nominal = 0;
unsigned int counter = 0;
unsigned int counterLimit = 0;
bool nozzleReady = false;
enum LCD_STATE {INPUTNOMINAL, NOZZLEREADY, INVALID};

// Fungsi Reset
void (* resetFunc) (void) = 0;

void setup()
{
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SHELL_BUTTON, INPUT);
  Serial.begin(9600);

  lcd.begin();         
  lcd.backlight();
  digitalWrite(RELAY, HIGH);
  start_display("Masukkan Nominal", INPUTNOMINAL);
}

void loop()
{
  if(digitalRead(SHELL_BUTTON)==HIGH) {
    return;
  }
  digitalWrite(RELAY, HIGH);
  char customKey = keypad.getKey();
  if (customKey=='A') {
    setHargaBeli("5000");
  } else if (customKey=='B') {
    setHargaBeli("10000");
  } else if (customKey=='C') {
    setHargaBeli("15000");
  } else if (customKey=='D') {
    setHargaBeli("20000");
  } else if (customKey=='#'){
    counterLimit = atoi(hargaBeli);
    if (counterLimit < 1000) {
      start_display("Minimal 1000", INVALID);
    } else {
      start_display("Silakan Isi", NOZZLEREADY);
    }
  } else if (customKey == '*') {
      resetFunc();
  } else if (customKey) {
    if (cursor <= 9){
      hargaBeli[nominal]=customKey;
      lcd.setCursor(cursor,1);
      lcd.print(hargaBeli[nominal]);
      nominal++;
      cursor++;
    }
    Serial.println(customKey);
  }
  
  if ((digitalRead(BUTTON)==HIGH) && nozzleReady){
      if (counter <= counterLimit){
        digitalWrite(RELAY, LOW);
        lcd.setCursor(0, 1);
        lcd.print(counter);
        counter+=100;
        delay(35);
      }
  }
  
}

// Fungsi Mode LCD
void start_display(char message[], LCD_STATE lcdState) {
  lcd.clear();
  lcd.setCursor(0, 0);

  switch (lcdState) {
    case INPUTNOMINAL:
      lcd.print(message);
      lcd.setCursor(0, 1);
      lcd.print("Rp.");
      break;
    case NOZZLEREADY:
      nozzleReady = true;
      lcd.clear();
      lcd.print(message);
      lcd.setCursor(0, 1);
      break;
    case INVALID:
      tone(BUZZER, 4000);
      delay(100);
      noTone(BUZZER);
      lcd.clear();
      lcd.print(message);
      delay(1500);
      resetFunc();
      break;    
  }
}

void setHargaBeli(String nominal) {
  memset(hargaBeli, 0, sizeof(hargaBeli));
  for(int i = 0; i<=nominal.length(); i++) {
    hargaBeli[i] = nominal[i];
  }

}
