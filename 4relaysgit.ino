// This is a simple sketch i've made for using an esp8266 with onboard oled (ideaspark and similar) to change the status of four ports
// D0, D1, D2, D3 (GPIO 16, 5, 4, 0) via wifi using BLYNK iot and a simple mobile widget (D0 as output is not recommended, but it works
// fine for me). Virtual pins used: V0 (D0), V1 (D1), V3 (D2), V4 (D3). The ports are shown on the display.
// you can use it drive four relays on your board with your mobile or to do everything else.... Have fun! Pupazzino 2025. 
// Pupazzino1 on ig.



#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
// your on board oled may need different values, try SCL 14 SDA 12 with some "clones" of ideaspark.
#define OLED_RESET     -1   
#define SCREEN_ADDRESS 0x3C 
#define OLED_SDA 12       
#define OLED_SCL 14       

#define BLYNK_TEMPLATE_ID           "your Blynk template id" 
#define BLYNK_TEMPLATE_NAME         "your Blynk Device"
#define BLYNK_AUTH_TOKEN            "your Blynk token"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 *display;
// Your WiFi credentials.
// Set password to "" for open networks and write me your full address if you still have an open wifi network :-).
char ssid[] = "your wifi ssid";
char pass[] = "your wifi password";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
 // Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
 // Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
 // Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}


  void setup()
{
  pinMode(16, OUTPUT); //Initialise digital pin D0 as an output pin
  pinMode(5, OUTPUT); // Initialise digital pin D1 as an output pin
  pinMode(4, OUTPUT); // Initialise digital pin D2 as an output pin
  pinMode(0, OUTPUT); // Initialise digital pin D3 as an output pin
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  //all off
  Blynk.virtualWrite(0, 0);
  Blynk.virtualWrite(1, 0);
  Blynk.virtualWrite(3, 0);
  Blynk.virtualWrite(4, 0);
  //display 
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  Wire.begin(OLED_SDA, OLED_SCL);
  display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display->clearDisplay();
  
  display->setTextSize(1);
  display->setTextColor (WHITE, BLACK);
  display->setCursor(0, 0);
  display->println("D0 is now off                      ");
  display->setCursor(0, 17);
  display->println("D1 is now off                      ");
  display->setCursor(0, 34);
  display->println("D2 is now off                      ");
  display->setCursor(0, 51);
  display->println("D3 is now off                      ");
  
  
  display->display();
 
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  
}

BLYNK_WRITE(V0) // Executes when the value of virtual pin V0 (D0) changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(16,HIGH);  // Set digital pin  HIGH
   
  
  display->setCursor(0, 00);
  display->println("                                   ");
  
  display->setCursor(0, 0);
  display->println("D0 is now on                       ");
  display->display();
  }
  else
  {
    // execute this code if the switch widget is now OFF
  digitalWrite(16,LOW);  // Set digital pin  LOW  
 
  display->setCursor(0, 0);
  display->println("                                   ");
  
  display->setCursor(0, 0);
  display->println("D0 is now off                      ");  
  display->display();
  }
}
 
 BLYNK_WRITE(V1) // Executes when the value of virtual pin V1 (D1) changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(5,HIGH);  // Set digital pin  HIGH
  
  display->setCursor(0, 17);
  display->println("                                   ");
  
  display->setCursor(0, 17);
  display->println("D1 is now on                       ");
  display->display();
  }
  
  else
  {
    // execute this code if the switch widget is now OFF
    digitalWrite(5,LOW);  // Set digital pin  LOW    
 
  display->setCursor(0, 17);
  display->println("                                   ");
  
  display->setCursor(0, 17);
  display->println("D1 is now off                      ");
  display->display();
  }
  
}
BLYNK_WRITE(V3) // Executes when the value of virtual pin V3 (D2) changes
{
  if(param.asInt() == 1)
  {
    // execute this code if the switch widget is now ON
    digitalWrite(4,HIGH);  // Set digital pin  HIGH
 
  display->setCursor(0, 34);
  display->println("                                   ");
 
  display->setCursor(0, 34);
  display->println("D2 is now on                       ");
  display->display();
  }
  
  else
  {
    // execute this code if the switch widget is now OFF
  digitalWrite(4,LOW);  // Set digital pin  LOW    
 
  display->setCursor(0, 34);
  display->println("                                   ");
  
  display->setCursor(0, 34);
  display->println("D2 is now off                      ");
  display->display();
  }
  
}
BLYNK_WRITE(V4) // Executes when the value of virtual pin V4 (D3) changes
{
  if(param.asInt() == 1)
  {
  // execute this code if the switch widget is now ON
  digitalWrite(0,HIGH);  // Set digital pin  HIGH
 
  display->setCursor(0, 51);
  display->println("                                   ");
  
  display->setCursor(0, 51);
  display->println("D3 is now on                       ");
  display->display();
  }
  else
  {
   // execute this code if the switch widget is now OFF
  digitalWrite(0,LOW);  // Set digital pin  LOW    
 
  display->setCursor(0, 51);
  display->println("                                   ");
 
  display->setCursor(0, 51);
  display->println("D3 is now off                      ");
  display->display();
  }
}
 

void loop()
{
  
  Blynk.run();
  timer.run();
  
  
}
