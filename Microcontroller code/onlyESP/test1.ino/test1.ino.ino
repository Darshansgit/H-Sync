#include <Wire.h>                // i2c library for arduino.           
#include <IOXhop_FirebaseESP32.h>    //firebase library
#include <WiFi.h>
#define WIFI_SSID "Darshans wifi"       //wifi ssid and password
#define WIFI_PASSWORD "17523988"
#define FIREBASE_AUTH "https://esp2fb-ff2ff-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_HOST "DHCfscjfu21nAQhMVKXhA9mySuF94D9ipYA99EDR"

volatile byte i2c_data_rx;       // indicates there are available data from the i2c bus. 
volatile uint16_t count;         // indicates the total number of data collected.
volatile uint8_t sys, dia, hr;   // stored the measure values: systolic, diastolic and heart rate.
int sendDataButton= 5;
int GreenLed=4;
int YellowLed=2;
char wifiState;

void setup()
{
  pinMode(sendDataButton,INPUT_PULLUP);        // Triggers when ground connects
  pinMode(GreenLed,OUTPUT); 
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
  Firebase.begin(FIREBASE_AUTH, FIREBASE_HOST);
  
}

void loop()
{
    
    delay(40);
    bool state = digitalRead(sendDataButton);
    if (state==0)                                //When button triggers, we print data
    {
      if(sys==0|| dia==0|| hr==0)
      {
      
      }
        else
        {
          String d1;
          String d2;
          String d3;
           
          d1 = String(sys);
          d2 = String(dia);
          d3 = String(hr);

          String data = d1+"/"+d2+"/"+d3;

          // Serial.println(data);
          
          FBpush(data);
          // Serial.print("Blood Presure Data: ");
          // Serial.print(sys);
          // Serial.print("/");
          // Serial.print(dia);
          // Serial.print("/");
          // Serial.print(hr);
          // Serial.println("");
          count = 0;                             //Count reset 
          sys=0;                                 //Data reset
          dia=0;
          hr=0;
          
          while(digitalRead(sendDataButton)==0)
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

void FBpush(String inData)
{
  
  Firebase.pushString("Users/User1/DataIn", inData);
  
}