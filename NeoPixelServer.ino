#include <EEPROM.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <WiFiManager.h>     // https://github.com/tzapu/WiFiManager
#include <DNSServer.h>
#include <Adafruit_NeoPixel.h>

const char *ssid      = "your_ssid"; //empty
const char *password  = "your_password";  //empty

String webSite,javaScript,XML;

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 5
#define NUMPIXELS 32
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int pwm5 = 0;
int pwm6 = 0;
int pwm7 = 0;
int pwm8 = 0;
int pwm9 = 0;

String passw = "z";
bool rightPassword = false;
String year = "2017";
String refreshPage = "45";
String mainHeading   = "Noams ESP experiment";
String subHeading    = "Everything is coming to you from 4MB memory device";
String menuName = "ESP8266";
String title     = "Esp8266 by Noam";
String copyrights = "SystemArt";
String webpage       = ""; //init webpage
String Email = "noamriter@hotmail.com";
int port = 80; // Change the port to the one you open
String PublicIpAddress = "0"; //change it to your public IP. Open a rout/port on your ESP in router (TCP/UDP), Change the port to the one you open
String IpAddress = "0";
int openWifiManager;


unsigned long currentMillis  = 0;
unsigned long previousMillis = 0;
long intervalNeoPixel = 20;  // refreshing rate  neopixel

bool theaterChaseBool = false;
bool oneColorBool = false;
bool rainbowBool = false;
bool rainbowCycleBool = false;
bool theaterChaseRainbowBool = false;
uint32_t color;

uint16_t cycleCounter =0;
uint16_t innrecycleCounter =0;

ESP8266WebServer server(port);

void setup()
{
  pinMode(14,OUTPUT);
  pinMode(0,OUTPUT);  
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);

  analogWrite(14, 0);
  analogWrite(0, 0);
  analogWrite(2, 0);
  analogWrite(12, 0);
  analogWrite(13, 0);

  #if defined (__AVR_ATtiny85__)
   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();
  strip.show();

  Serial.begin(115200);
  EEPROM.begin(500);
  int openWifiManager = EEPROM.read(35);
  Serial.println(openWifiManager);
  WiFiManager wifiManager;
 if(openWifiManager == 1)
     {
      wifiManager.resetSettings();
      EEPROM.write(35, 0);
      EEPROM.commit();
     }
  wifiManager.setTimeout(30);
  if(!wifiManager.autoConnect("Noams ESP!")) {
    Serial.println("failed to connect and timeout!");
    delay(5000);
    ESP.reset(); 
    delay(150000);
  }
  Serial.println("WiFi connected!");
  server.begin(); 
  Serial.println("Webserver started!"); 
  Serial.println("Your local IP address: http://"+WiFi.localIP().toString()+":" + port);  // Print local IP address

  if(PublicIpAddress == "0")
  {
    IpAddress = WiFi.localIP().toString()+":" + port;
    }
  else
  {
    IpAddress = PublicIpAddress + ":" + port;
    }
  
  Serial.println("Your divice IP address: http://"+ IpAddress);  // Print divice variable IP address.
  
  server.on("/",         Product); // IP/
  server.on("/homepage", homepage);   // IP/homepage
  server.on("/Product", Product);      // IP/Product
  server.on("/Portfolio", Portfolio);      // IP/Portfolio
  server.on("/Services", Services);      // IP/Services
  server.on("/Aboutus", Aboutus);      // IP/Aboutus
  server.on("/Contact", Contact);      // IP/Contact
  server.on("/RestartWifiManager", RestartWifiManager);     //IP/RestartWifiManager
  server.on("/PinValue", PinValue);  //IP/PinValue
  server.on("/NeoPixelPage", NeoPixelPage);  //IP/PinValue
  server.on("/startShow", startShow);  //IP/startShow
  server.on("/Password", Password);  //IP/PasswordValue
}

void loop() {
  server.handleClient();
  // if any av the button is called need to time neo pixels change without delay
  currentMillis = millis();
  if(theaterChaseBool)
  {
      theaterChase();
  }

  if(oneColorBool)
  {
    colorWipe();
  }

  if(rainbowBool)
  {
    rainbow();
  }

  if(rainbowCycleBool)
  {
    rainbowCycle();
  }

  if (theaterChaseRainbowBool)
  {
    theaterChaseRainbow();
  }
 // ESPDelay(10); // delay for the system to not crush
}

void ESPDelay(int ms) 
{
 int i;
 for(i=1;i!=ms;i++) 
   {
     delay(1);
    if(i%100 == 0) 
    {
       ESP.wdtFeed(); 
       yield();
    }
  }
}
