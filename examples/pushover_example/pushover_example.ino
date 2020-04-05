/*
    Example sketxh using myPushover library. This lib is an extended version of this lib
    * https://github.com/ArduinoHannover/Pushover
    
    Ths example runs on a ESP32

 */

#include <WiFi.h>     // used for pushover
#include <myPushover.h>

//----------------------------------------------------
// fill in your own credentials for wifi and pushover
const char* wifi_ssid =       "AAAAAAAAAAA" ;
const char* wifi_password =   "BBBBBBBBBBB";
String Token     = "XXXXXXXXX"; 
String Userkey   = "YYYYYYYYY";
//----------------------------------------------------

char bufpush [60];
int returncode;
//------------------------------------------------
// displays at startup the Sketch running in the Arduino
void display_Running_Sketch (void){
  String the_path = __FILE__;
  int slash_loc = the_path.lastIndexOf('/');
  String the_cpp_name = the_path.substring(slash_loc+1);
  int dot_loc = the_cpp_name.lastIndexOf('.');
  String the_sketchname = the_cpp_name.substring(0, dot_loc);

  Serial.print("\n************************************");
  Serial.print("\nRunning Sketch: ");
  Serial.println(the_sketchname);
  Serial.print("Compiled on: ");
  Serial.print(__DATE__);
  Serial.print(" at ");
  Serial.print(__TIME__);
  Serial.print("\n");
  Serial.print("************************************\n");
}


//---------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
  display_Running_Sketch();
  //connect to WiFi
  Serial.printf("Connecting to %s / %s ", wifi_ssid,wifi_password );

  WiFi.begin(wifi_ssid, wifi_password);
  returncode = waitForWifi();

  if (returncode == 0)  Serial.println ("wifi ok, lets try to send a message...");
  else {
    Serial.println ("restart esp32...");
    vTaskDelay(1000 / portTICK_PERIOD_MS);               // wait, to prevent fast rebbot sequence
    ESP.restart();
  }
  int temp = 22;
  sprintf (bufpush, "Current Temperatur %d", temp);
 // Serial.println (bufpush);

 // pushover stuff ---------------
  myPushover po = myPushover(Token,Userkey);
  po.setHTML (true);
  po.setDevice("myiphone,myipad");
  po.setTitle ("Pushover Example");
  po.setMessage(bufpush);
  po.setPriority(0);  
  po.setSound("bike");
  po.setDebug (true);           // set debug for lib
  returncode = po.send();
  Serial.print ("Returncode: "); Serial.println (returncode); //should return 0 on success
  if (returncode == 0) Serial.println ("message sent ok");
  else Serial.println ("error message send");

  Serial.println ("setup ended");
}

//-------------------------------------------------
void loop() {
  delay(200);
}


//------------------------------------------------
int waitForWifi() {
  Serial.print ("\n");
  Serial.print("Waiting for WiFi.");

int retries;
 
   retries = 0;
   while (WiFi.status() != WL_CONNECTED)  { 
    retries++;
    if (retries > 40) break;      // max number retries
  // Pause the task for 300ms
    vTaskDelay(300 / portTICK_PERIOD_MS);
    Serial.print  ("."); 
   }
    
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println ("connected");
    return (0);
  }
  // no connection...
  Serial.println  ("\nno wifi connection");
  return (1);
}

// end of code ----------------------------------------------
