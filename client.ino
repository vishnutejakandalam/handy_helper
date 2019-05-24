#include <ESP8266WiFi.h>                                            //importing the Wi.Fi library
#include <ESP8266HTTPClient.h>                              //importing the client libraries
#include <BlynkSimpleEsp8266.h>                           //importing the Blynk libraries
BlynkTimer timer;                                                          //creating a timer instance
const char* ssid = "K V MOHAN(SRC)";                  //network name
const char* password = "makemehappy";           //password of the netowrk
char* url;

void setup () {
 pinMode(A0,INPUT);                                                // pin to connect x axis of joystick
 pinMode(13,OUTPUT);                                           // pin to connect the button pin
 Blynk.begin("8c8fb4e6b1b54da3b396e695af813c3a",ssid,password);
                                                                                         // connecting to Blynk server through the                                                                                                                                                                                                                                                                         
                                                                                        // internet  
timer.setInterval(2,hello);	                                    //setting the timer
Serial.begin(115200); 
}

  void loop() {
  Blynk.run();	                                                  
  timer.run();
   }

void hello()
{
  int lv;
  HTTPClient http;                                                       //Declare an object of class HTTPClient
    if(analogRead(A0)==1024)                                 //checking the position of the joystick
    {
      if(digitalRead(13)==0)
      {
        lv =1;
        url="http://192.168.1.100/flash/1";           //preparing the respective url to send                                                                               
                                                                                          //request     
}
 else if(digitalRead(13)==1)
  {
   lv=0;
    url="http://192.168.1.100/flash/0";
    }
 }
   else if(analogRead(A0)<=10)
{ 
  Blynk.notify("I AM HERE");
}
  else if(digitalRead(5) == 0) 
 {
    url=”http://192.168.1.100/buzzer/1”;
 }
else if(digitalRead(5) == 1)
{
   url=”http://192.168.1.100/buzzer/0”;
} 
     digitalWrite(13,lv); 	                           //set the LED accordingly
     http.begin(url);                                                            //sending the request
     int httpCode = http.GET();                                        // Check the returning code                                                             
     if (httpCode > 0) { 
     String payload = http.getString();                         //Get the request response payload
      Serial.println(payload);                                          //Print the response payload
 }
}
