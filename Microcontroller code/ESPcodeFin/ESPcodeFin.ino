#include <Wire.h>                // i2c library for arduino.           
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "time.h"
#include <WiFi.h>
#define WIFI_SSID "Darshans wifi"       //wifi ssid and password
#define WIFI_PASSWORD "17523988"

#define API_KEY "AIzaSyA6X7xLIIT0wPb8eMvGS2NIiLsmYrkiJ0M"
#define DATABASE_URL "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app/"


volatile byte i2c_data_rx;       // indicates there are available data from the i2c bus. 
volatile uint16_t count;         // indicates the total number of data collected.
volatile uint8_t sys, dia, hr;   // stored the measure values: systolic, diastolic and heart rate.

int sendDataButton= 5;
int GreenLed=32;
int BlueLed=27;

FirebaseJson json;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOk = false;

String hrPath = "/HearRate";
String sysPath = "/Systolic";
String diaPath = "/Diastolic";
String timePath = "/timestamp";

String parentPath;

int timeStamp;

const char* ntpServer = "pool.ntp.org";

void setup()
{
  pinMode(sendDataButton,INPUT_PULLUP);        // Triggers when ground connects
  pinMode(GreenLed,OUTPUT); 
  pinMode(BlueLed,OUTPUT); 
  Serial.begin(115200);
  Wire.begin(0x50);                           // the address of the EEPROM is 0x50. The arduino should be the same.            
  Wire.onReceive(receiveEvent);               // this is the interrupt initialization for the i2c data.

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);       // Initializing everything needed for wifi.
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("Connected: ");
  Serial.println(WiFi.localIP());
  digitalWrite(GreenLed, HIGH);


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

void loop()
{ 
    timeStamp = getTime();
    bool state = digitalRead(sendDataButton);
    if (state==0)                                //When button triggers, we print data
    {
      if(sys==0|| dia==0|| hr==0 || timeStamp ==0)
      {
      
      }
        else
        {

          int newtimeStamp = getTime();
          parentPath = "/Users/User1/" + String(newtimeStamp);

          json.set(hrPath.c_str(), hr);
          json.set(sysPath.c_str(), sys);
          json.set(diaPath.c_str(), dia);
          json.set(timePath, newtimeStamp);

          bool sentState= Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json);

          if(sentState == HIGH)
          {
            Serial.print("ok");
            digitalWrite(BlueLed,HIGH);
            delay(800);
            digitalWrite(BlueLed,LOW);
            delay(600);
            digitalWrite(BlueLed,HIGH);
            delay(800);
            digitalWrite(BlueLed,LOW);
          }
          else{
            Serial.println(fbdo.errorReason().c_str());
          }


          count = 0;                             //Count reset 
          sys=0;                                 //Data reset
          dia=0;
          hr=0;
          
          while(digitalRead(sendDataButton)==0)   //debouncing 
          {

          }
        }
    }
}

void receiveEvent(int iData)                 // Interrupt service routine.
{
  while ( iData-- )
  {
    i2c_data_rx = Wire.read();
    
    // Serial.println(i2c_data_rx);          Debugging 
    // Serial.println(count);
    
    count++;

    if (count == 461)
    {
      sys = i2c_data_rx;
    }
    if (count == 462)
    {
      dia = i2c_data_rx;
    }
    if (count == 463)
    {
      hr = i2c_data_rx;
    }
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
