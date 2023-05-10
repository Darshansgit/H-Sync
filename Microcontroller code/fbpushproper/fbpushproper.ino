#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "time.h"


#define WIFI_SSID "Darshans wifi"
#define WIFI_PASSWORD "17523988"

#define API_KEY "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M"
#define DATABASE_URL "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define led1 4
#define button 5

FirebaseJson json;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOk = false;
unsigned long sendDataPrevMillis = 0;

String hrPath = "/hr";
String sysPath = "/sys";
String diaPath = "/dia";
String timePath = "/timestamp";

String parentPath;

int timeStamp;

const char* ntpServer = "pool.ntp.org";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while (WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected!!" + WiFi.localIP());
  digitalWrite(led1,HIGH);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "","")){
    Serial.printf("signup OK");
    signupOk = true;
  }
  else
  {
    Serial.printf("%S\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  configTime(0, 0, ntpServer);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(Firebase.ready() && signupOk && (millis()- sendDataPrevMillis >5000 || sendDataPrevMillis ==0 ))
  {
    sendDataPrevMillis = millis();
    int hr = 80;
    int sys = 120;
    int dia = 80;
    timeStamp = getTime();
    parentPath = "/Users/User1/" + String(timeStamp);

    json.set(hrPath.c_str(), hr);
    json.set(sysPath.c_str(), sys);
    json.set(diaPath.c_str(), dia);
    json.set(timePath, String(timeStamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    
    // if(Firebase.RTDB.setInt(&fbdo,"Users/User1/hr",hr))
    // {
    //   Serial.println();
    //   Serial.print(hr+"  "); Serial.print(fbdo.dataPath());
    //   Serial.println("(" + fbdo.dataType() + ")");
    // }
    // else{
    //   Serial.println("Failed"+ fbdo.errorReason());
    // }
      
    // if(Firebase.RTDB.setInt(&fbdo,"Users/User1/sys",sys))
    // {
    //   Serial.println();
    //   Serial.print(sys+"  "); Serial.print(fbdo.dataPath());
    //   Serial.println("(" + fbdo.dataType() + ")");
    // }
    // else{
    //   Serial.println("Failed"+ fbdo.errorReason());
    // }
      
    // if(Firebase.RTDB.setInt(&fbdo,"Users/User1/dia",dia))
    // {
    //   Serial.println();
    //   Serial.print(dia+"  "); Serial.print(fbdo.dataPath());
    //   Serial.println("(" + fbdo.dataType() + ")");
    // }
    // else{
    //   Serial.println("Failed"+ fbdo.errorReason());
    // }
  }
} 

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}