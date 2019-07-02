#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "utility/debug.h"
#include "utility/socket.h"
#include <PCF8574.h>
#include <Wire.h>

// PINY
#define ADAFRUIT_CC3000_IRQ   2  
#define ADAFRUIT_CC3000_VBAT  7
#define ADAFRUIT_CC3000_CS    10

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIVIDER); // you can change this clock speed

#define WLAN_SSID       "Domek24"
#define WLAN_PASS       "marek2103"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define LISTEN_PORT           80 

#define ZWCZ 0
#define ZWZ  1
#define ZWA  2
#define ZWB  3
#define ZW1  4
#define ZW2  5
#define ZWM  6
#define ZWK  7
#define S1  0
#define S2  1
#define S3  2
#define S4  3
#define S5  4

PCF8574 expander;
PCF8574 expander2;    

Adafruit_CC3000_Server httpServer(LISTEN_PORT);

char line1[100];
char buffer[100];

void setup(void)
{
  Serial.begin(115200);
  Serial.println(F("Rozpoczynam!\n\n")); 

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

  Serial.println("Ustawiam Porty");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  expander.begin(0x20);
  expander2.begin(0x24);
  expander.pinMode(0, OUTPUT);
  expander.pinMode(1, OUTPUT);
  expander.pinMode(2, OUTPUT);
  expander.pinMode(3, OUTPUT);
  expander.pinMode(4, OUTPUT);
  expander.pinMode(5, OUTPUT);
  expander.pinMode(6, OUTPUT);
  expander.pinMode(7, OUTPUT);
  expander2.pinMode(0, OUTPUT);
  expander2.pinMode(1, OUTPUT);
  expander2.pinMode(2, OUTPUT);
  expander2.pinMode(3, OUTPUT);
  expander2.pinMode(4, OUTPUT);
  expander2.pinMode(5, OUTPUT);
  expander2.pinMode(6, OUTPUT);
  expander2.pinMode(7, OUTPUT);
  expander.digitalWrite(0,HIGH);
  expander.digitalWrite(1,HIGH);
  expander.digitalWrite(2,HIGH);
  expander.digitalWrite(3,HIGH);
  expander.digitalWrite(4,HIGH);
  expander.digitalWrite(5,HIGH);
  expander.digitalWrite(6,HIGH);
  expander.digitalWrite(7,HIGH);
  expander2.digitalWrite(0,HIGH);
  expander2.digitalWrite(1,HIGH);
  expander2.digitalWrite(2,HIGH);
  expander2.digitalWrite(3,HIGH);
  expander2.digitalWrite(4,HIGH);
  expander2.digitalWrite(5,HIGH);
  expander2.digitalWrite(6,HIGH);
  expander2.digitalWrite(7,HIGH);
  
  
  
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Initialise the module
  Serial.println(F("\nInicjacja..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Nie moge rozpoczac! Sprawdz przewody?"));
    while(1);
  }
  
  Serial.print(F("\nProba bodlaczenia do sieci: ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Blad!"));
    while(1);
  }
   
  Serial.println(F("Podlaczono!"));
  
  Serial.println(F("Zapytanie DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
  
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  
  httpServer.begin();
  
  Serial.println(F("Nasluch"));
}

  
void loop(void)
{
  Adafruit_CC3000_ClientRef client = httpServer.available();

    if (client) 
  {
    if (client.connected()) 
    {
      readHeader();
      if (pageNameIs("/1/1"))
      {
        expander2.digitalWrite(S1,HIGH);
        Serial.println(F("1 na w"));
      }
      else if (pageNameIs("/1/0"))
      {
        expander2.digitalWrite(S1,LOW);
        Serial.println(F("1 na n"));
      }
      
      else if (pageNameIs("/2/1"))
      {
        expander2.digitalWrite(S2,HIGH);
        Serial.println(F("2 na w"));
      }
      else if (pageNameIs("/2/0"))
      {
        expander2.digitalWrite(S2,LOW);
        Serial.println(F("2 na n"));
      }
      
      else if (pageNameIs("/3/1"))
      {
        expander2.digitalWrite(S3,HIGH);
        Serial.println(F("3 na w"));
      }
      else if (pageNameIs("/3/0"))
      {
        expander2.digitalWrite(S3,LOW);
        Serial.println(F("3 na n"));
      }
      
      else if (pageNameIs("/4/1"))
      {
        expander2.digitalWrite(S4,HIGH);
        Serial.println(F("4 na w"));
      }
      else if (pageNameIs("/4/0"))
      {
        expander2.digitalWrite(S4,LOW);
        Serial.println(F("4 na n"));
      }
      
      else if (pageNameIs("/5/1"))
      {
        expander2.digitalWrite(S5,HIGH);
        Serial.println(F("5 na w"));
      }
      else if (pageNameIs("/5/0"))
      {
        expander2.digitalWrite(S5,LOW);
        Serial.println(F("5 na n"));
      }
      else if (pageNameIs("/zwCZ")){
        zwrotnica(ZWCZ);
      }
      else if (pageNameIs("/zwZ")){
        zwrotnica(ZWZ);
      }
      else if (pageNameIs("/zwA")){
        zwrotnica(ZWA);
      }
      else if (pageNameIs("/zwB")){
        zwrotnica(ZWB);
      }
      else if (pageNameIs("/zw1")){
        zwrotnica(ZW1);
      }
      else if (pageNameIs("/zw2")){
        zwrotnica(ZW2);
      }
      else if (pageNameIs("/zwM")){
        zwrotnica(ZWM);
      }
      else if (pageNameIs("/zwK")){
        zwrotnica(ZWK);
      }
      
        client.fastrprintln(F("HTTP/1.1 200 OK"));
        client.fastrprintln(F("Content-Type: text/html"));
        client.println();
        client.fastrprintln(F("<html><head><title>Sterowanie</title>"));
        client.fastrprintln(F("<script>"));
        client.fastrprint(F("function zwrotnica(stan){"));
        client.fastrprint(F("if (stan == 1){"));
        client.fastrprint(F("window.location.href = \"http://192.168.0.3/zwrotnica\";}"));
        client.fastrprint(F("else if (stan == 0){window.location.href = \"http://192.168.0.3/zwrotnica1\";"));
        client.fastrprint(F("}}function szesc(stan){if  (stan == 1)"));
        client.fastrprint(F("{window.location.href = \"http://192.168.0.3/6/1\";"));
        client.fastrprint(F("}else if (stan == 0){window.location.href"));
        client.fastrprint(F(" = \"http://192.168.0.3/6/0\";}}"));
        client.fastrprint(F("</script>"));
        client.fastrprint(F("</script>"));
        client.fastrprintln(F("<style type=\"text/css\">.przyciskon"));
        client.fastrprintln(F("{display:block;width:120px;height: 79px;"));
        client.fastrprintln(F("background-color:#37d500;float: left;text-align: center;font-size:16px;"));
        client.fastrprintln(F("padding-top:41;margin: 5px 5px 5px 5px;} .przyciskof{display:block;"));
        client.fastrprintln(F("width: 120px;height: 79px;background-color:red;float: left;text-align: center;"));
        client.fastrprintln(F("font-size:16px;padding-top:41;margin: 5px 5px 5px 5px;} "));
        client.fastrprintln(F("</style><div class=\"przyciskon\" onclick=\"zwrotnica(1)\">Zwrotnica cz/z</div>"));
        client.fastrprintln(F("<div class=\"przyciskof\" onclick=\"zwrotnica(0)\">Zwrotnica cz/z</div>"));
        client.fastrprintln(F("<div style=\"clear: both\"></div><br><div class=\"przyciskon\" onclick=\"szesc(1)\">6</div>"));
        client.fastrprintln(F("<div class=\"przyciskof\" onclick=\"szesc(0)\">6</div><div style=\"clear: both\"></div>"));
        client.fastrprintln(F("</head><body>"));
        client.fastrprintln(F("</body></html>"));
      client.stop();            
    }
  }

  
}


// Tries to read the IP address and other connection details
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}



void readHeader()
{
  readRequestLine(line1);
  while (readRequestLine(buffer) > 1 && buffer[0] != '\n') {}
}

int readRequestLine(char *line)
{
  Adafruit_CC3000_ClientRef client = httpServer.available();
  char ch;
  int i = 0;
  while (ch != '\n' && i < 100 && client.available())
  {
    if (client.available())
    {
      ch = client.read();
      line[i] = ch;
      i ++;
    }
  }
  line[i] = '\0'; 
  return i;
}

boolean pageNameIs(char* name)
{
   // nazwa strony rozpoczyna się od znaku na czwartej pozycji
   // kończy się spacją
   int i = 4;
   char ch = line1[i];
   while (ch != ' ' && ch != '\n' && ch != '?')
   {
     if (name[i-4] != line1[i])
     {
       return false;
     }
     i++;
     ch = line1[i];
   }
   return true;
}
void zwrotnica (int port){
  expander.digitalWrite(port,LOW);
  Serial.print(port);
  Serial.println(F(" na n"));
  delay(600);
  expander.digitalWrite(port,HIGH);
  Serial.print(port);
  Serial.println(F(" na w"));
}

