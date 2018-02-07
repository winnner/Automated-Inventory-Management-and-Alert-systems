#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include "hx711.h"
char ssid[] = "nothing";  //my network ssid name
char pass[] = "0000000000"; //my network ssid password
char server[] ="192.168.43.165"; //ip address of my server(laptop)
hx711 scale(4, 3);//(Dout, Clk)
int numberOfBox;
WiFiClient client;
void setup(void)
{
Serial.begin(115200);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print("not connected");
}
Serial.println("");
Serial.println("WiFi connected");
}
void loop()
{
 numberOfBox=scale.getGram()/500;
if (client.connect(server , 139))
{
Serial.print("connected with server\n");
client.print("GET /Project/write_data.php?");
client.print("value=");
client.print(numberOfBox);
client.print("Host:  192.168.43.165");
client.println(" HTTP/1.1");
client.print("Connection: close");
client.println();
client.println();
client.stop();
}
else
{
Serial.println("connection failed");
}
delay(10000);
}

