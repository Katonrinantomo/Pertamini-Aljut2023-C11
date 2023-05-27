#include <LiquidCrystal_I2C.h>       //memanggil library LCD
#include <Keypad.h>                  //memanggil library Keypad
#include <Wire.h>                    //memanggil lirary serial komunikaai LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);   // setting alamat 12C(0X27), besar karakter untuk LCD 16X2 

const byte RELAY = 10;                //inisialisasi pin RELAY yang dihubungkan pompa mini 
const byte BUTTON = 11;               //inisialiasi pin button 
const byte batasHarga = 7;            //inisialisasi variabel batasan nilai yang nanti di inputkan bernilai 7 pada saat ditampilkan di LCD
const byte rows = 4;                  //inisialisasi jumlah baris keypad
const byte cols = 4;                  //inisialisasi jumlah kolom keypad
char keys[rows][cols] = {
  {'1','2','3','A'},                  //inisialisasi baris pertama keypad
  {'4','5','6','B'},                  //inisialisasi baris kedua keypad
  {'7','8','9','C'},                  //inisialisasi baris ketiga keypad
  {'*','0','#','D'}                   //inisialisasi baris keempat keypad
};
byte rowPins[rows] = {9, 8, 7, 6};    //inisialisasi pin digital baris keypad
byte colPins[cols] = {5, 4, 3, 2};    //inisialisasi oin digital kolom keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );    //inisialisasi pin baris, pin kolom, baris, kolom

int cursor = 3;                       //inialisasi cursor LCD bernilai 3
char counter[batasHarga];             //membuat variabel batasHarga menjadi array
byte inputKey = 0;                    //membuat variabel 
int showNumber = 0;                   //

void setup()
{
  lcd.begin();                        //inisialisasi LCD
  lcd.backlight();                    //menghidupkan LCD
  pinMode(RELAY, OUTPUT);             //mengsetup variabel RELAY sebagai OUTPUT
  pinMode(BUTTON, INPUT);             //mengsetup variabel BUTTON sebagai INPUT
  Serial.begin(9600);                 //inialisasi Kode serial di 9600
  start_display("Masukkan Nominal","Input");  //memanggil function start_display, menjadikannya input, lalu menampilkan "masukkan nominal" pada LCD
}

void loop()
{
  char customKey = keypad.getKey();               //menginsialisasi variabel customkey sebagai keypad
  if (customKey=='#'){                            //jika variabel customkey inputan terakhirnya '#', maka lakukan perintah seperti di bawah(ENTER) 
    start_display("Silakan Isi","NozzleReady");   //memanggil function start_display(),minampilkan "silahkan isi" pada LCD
  } else if (customKey == '*') {                  //selain jika variabel customkey inputan terkahirnya '*' maka lakukan perintah seperti di bawah(RESET)
      memset(counter, 0, sizeof(counter));        //menggantikan/mengereset variabel counter menjadi 0, dan mereset/menggantikan array counter
      cursor = 3;                                 //inisialiasi cursor LCD bernilai 3
      inputKey = 0;                               //meng 0 kan variabel
      showNumber = 0;                             //meng 0 kan variabel shownumber
      start_display("Masukkan Nominal","Input");  //memanggil function start_display,lalu mengprint "Masukkan nominal"

  } else if (customKey) {                         //selain jika customkey bernilai/ada (apapun inputan terakhirnya), maka eksekusi perintah dibawah ini
    if (cursor <= 9){                             //jika cursor LCD kurang sama dengan 9, maka eksekusi perintah dibawah ini
    counter[inputKey]=customKey;                  //membuat inputkey(nominalCustom) menjadi array, lalu membuatnya menjadi variabel customkey
    lcd.setCursor(cursor,1);                      //mengseting cursor yang nanti ditampilkan (bervalue 3 yang akan di loop samapi 9 ,1)
    lcd.print(counter[inputKey]);                 //mengprint variabel inputkey(array) yang nanti akan di loop sampai 9
    inputKey++;                                   //looping inputkey sampai 9
    cursor++;                                     //looping cursor(yg ditampilkan di LCD) sampai 9
    }
  }
  
   if ((int(showNumber) !=0) && (int(showNumber)%1000==0)) {
        toRound = int(showNumber)/1000;
  }

  if (digitalRead(BUTTON)==HIGH){                 //jika button HIGH(dipencet), eksekusi instruksi dibawah
      int prCounter = atoi(counter);              //varibel prCounter adalah variabel inputkey (array) yang diubah menjadi integer yg ditanmpung dlm variabel prCounter
      if (showNumber <= prCounter){               //jika nilai showNumber (berapa kali button dipencet) kurang sama dengan dari prCounter(variabel inputan array yg diubah menjadi integer), maka eksekusi perintah dibawah 
        lcd.setCursor(0, 1);                      //menyetting cursor di lCD    
        lcd.print(showNumber);                    //meng print nilai showNummmber (berapa kali button sudah di pencet)
        showNumber++;                             //meng loop agar variabel showNumber bertambah sampai lebih dari prCounter     
    }
  }
  
}

void start_display(char message[],char idleState[]) {     //
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
