#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


const char* ssid = "wifiname";
const char* password = "wifipassword";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org");

//Week Days
String weekDays[7]={"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

//Month names
String months[12]={"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("\n\nPertamini C-11 Web App\n");
  setup_wifi();
  timeClient.begin();
  timeClient.setTimeOffset(25200);
}

void loop() {
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  
  String formattedTime = timeClient.getFormattedTime();

  // Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  
  // Print complete date:
  String currentDate = String(monthDay) + "-" + String(currentMonth) + "-" + String(currentYear);
  String waktuBeli = formattedTime + " " + currentDate;
  
  String arduinoData;
  if(Serial.available()) {
    arduinoData = Serial.readStringUntil('\n');

    if (WiFi.status() == WL_CONNECTED) {
     WiFiClient client;
     HTTPClient http;

     // HTTP Details
     String serverUrl = "http://localhost:3500/";
     http.begin(client, serverUrl);
     http.addHeader("Content-Type","application/json");

     String body = String(arduinoData);
     Serial.println("POST body: " + body);

     // Send HTTP POST request
     int httpResponseCode = http.POST("{\"nominal\":"+body+",\"waktu\":\""+waktuBeli+"\"}");
     Serial.print("HTTP Response code: ");
     Serial.println(httpResponseCode);

     Serial.print(arduinoData+" ");
     Serial.println(waktuBeli);
     Serial.println();
    http.end();
  }
 }
 delay(5000);
}
