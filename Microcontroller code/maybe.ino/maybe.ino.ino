#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include "time.h"

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Darshans wifi"
#define WIFI_PASSWORD "17523988"

// Insert Firebase project API Key
#define API_KEY "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app"

// Define Firebase objects
FirebaseData fbdo;
FirebaseConfig config;

// Database main path (to be updated in setup with the user UID)
String databasePath;
// Database child nodes
String hrNode = "/heartrate";
String sysNode = "/systolicP";
String diaNode = "/diastolicP";
String timePathNode = "/timestamp";

// Parent Node (to be updated in every loop)
String parentPath;

int timestamp;

FirebaseJson json;

const char* ntpServer = "pool.ntp.org";

// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 180000;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  digitalWrite(4, HIGH);
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}

void setup() {
  pinMode(4, OUTPUT);

  Serial.begin(115200);

  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config);

  // Update database path
  databasePath = "/UsersData/" + "/readings";
}

void loop() {
  delay(10000);

  int hrData = 80;
  int sysData = 120;
  int diaData = 80;
  //Get current timestamp
  timestamp = getTime();

  parentPath = databasePath + "/" + String(timestamp);

  json.set(tempPath.c_str(), hrData);
  json.set(humPath.c_str(), sysData;
  json.set(presPath.c_str(), diaData);
  json.set(timePath, String(timestamp));
  Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json);
}