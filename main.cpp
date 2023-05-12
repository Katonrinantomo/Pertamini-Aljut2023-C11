#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); 

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

byte cursor = 3;
char counter[batasHarga];
byte inputKey = 0;
int showNumber = 0;

void setup()
{
  lcd.begin();         
  lcd.backlight();    
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT);
  start_display("Masukkan Nominal","Input");
  Serial.begin(9600);
}

void loop()
{
  char customKey = keypad.getKey();
  if (customKey=='#'){
    lcd.clear();
    start_display("Silakan Isi","NozzleReady");
  }
  if (customKey) {

    if ((cursor <= 9) && (0 < customKey <= 9)){
    counter[inputKey]=customKey;
    lcd.setCursor(cursor,1);
    lcd.print(counter[inputKey]);
    inputKey++;
    cursor++;
    }
  }
  
  if (digitalRead(BUTTON)==HIGH){
      int prCounter = atoi(counter);
      if (showNumber <= prCounter){
        lcd.setCursor(0, 1);
        lcd.print(showNumber);
        showNumber++;
    }
  }

  
  // start_display();
  // char customKey = keypad.getKey();
  // static int i=0;
  // if (digitalRead(11)==LOW){
  //   i++;
  //   Serial.print("Zaky Afrizal");
  //   Serial.println(i);
  //   delay(1000);
  // }
  // if (customKey){
  //   if(cursor>9){
  //     return;
  //   }
  //   lcd.setCursor(cursor,1);
  //   Data1[nominal]=customKey;
  //   lcd.print(Data1[nominal]);
  //   cursor++;
  // }
  // switch (customKey)
  // {
  //   case '*':
  //   lcd.clear();
    
  //   break;
    
  // }
  
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

