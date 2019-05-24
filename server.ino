#include <ESP8266WiFi.h>                                                 // including the library
const char* ssid = "K V MOHAN(SRC)";                           //network name  
const char* password = "makemehappy";                     //password
WiFiServer server(80);                                                       //creating an instance to WiFiServer
void setup() {
  pinMode(4,OUTPUT);                                                       //declaring a digital pin for light
  pinMode(05, OUTPUT);                                                   // a digital pin to connect buzzer
  Serial.begin(115200);                                                     // turning on the Serial monitor
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);                                         // connecting to the network 
  while (WiFi.status() != WL_CONNECTED)               // loops till it gets connected
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   server.begin(115200);                                                // Start the server
  Serial.println("Server started");
  Serial.println(WiFi.localIP());                                  // printing the IP address of server
}

void loop()
{
    while(WiFi.status() == WL_CONNECTED)
{
  WiFiClient client = server.available();                   // taking the available client and storing in
                                                                                            //client 
  if (!client) {
    return;
  }
  Serial.println("new client");
   while(!client.available())                                        //waits till the client gets available
   {
    delay(1);
  }
  String req = client.readStringUntil('\r');             //reading the request from client
  Serial.println(req);
  client.flush();                                                             //waits till the characters in buffer of client
                                                                                       // have been sent                                                                                                                                  
  int val,val2;
  if (req.indexOf("/flash/0") != -1)                           // checking the request againest several
    val = 0;                                                                         // conditions
  else if (req.indexOf("/flash/1") != -1)
    val = 1;
  else if (req.indexOf("/buzzer/0") != -1)
    val2=0;
  else if(req.indexOf("/buzzer/1") != -1)
    val2=1;
    else {
    return;
  }
    digitalWrite(05, val);                                                // writing the pins according to the values
    digitalWrite(04,val2);
  client.flush();
  String s = "done ";
  s+=req;
  client.print(s);                                                              // sending the response to the client
  delay(1);
}
Serial.println("wifi disconnected");

 }


