/*
Shield eMGing Wifi test
Ejemplo de control de Shield eMGing Relay por WiFi
Controla 4 relays desde tu celular!
Cambia los datos para tu conexión de wifi y listo !
*/

#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>

const char* ssid = ""; // Ingresa AQUI el nombre de tu red Wifi
const char* password = ""; // Ingresa AQUI el PASSWORD

//Mac address should be different for each device in your LAN
//byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress arduino_ip ( 192,  168,   0,  200);         // Cambia los datos de IP de acuerdo a tu RED 
IPAddress dns_ip     (  192, 168,   0,   1);          // Cambia la dirección de tu DNS
IPAddress gateway_ip (  192, 168,   0,   1);          // Cambia la dirección de tu GATEWAY
IPAddress subnet_mask(255, 255, 255,   0);

WiFiServer server(80);

// D0=16, D1=5, D2=4, D3=0, D4=2, D5=14 , D6=13, D7=12, D8=15, D9=3, D10=1

// PARA LA CONFIGURACIÓN STANDARD DEL SHIELD EMGING RELAY, UTILIZA ESTOS PINES
const int RELAY4 = 2;  //D4
const int RELAY3 = 0;  //D3
const int RELAY2 = 4;  //D2
const int RELAY1 = 5;  //D1

String readStrings = "";

bool state_relay1 = true;
bool state_relay2 = true;
bool state_relay3 = true;
bool state_relay4 = true;


void setup(void){

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  delay(100);
    digitalWrite(RELAY1, HIGH);
    delay(100);
    digitalWrite(RELAY2, HIGH);
    delay(100);
    digitalWrite(RELAY3, HIGH);
    delay(100);
    digitalWrite(RELAY4, HIGH);
    
  Serial.begin(115200);
  WiFi.config(arduino_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
  
}

void loop(void){
 // put your main code here, to run repeatedly:
  WiFiClient client = server.available(); // client class WiFiClient Server.available() 
  
  if(client){ // client
  Serial.println("Yes client"); // Yes client Serial
  
    while(client.connected()){ // client loop 
       if(client.available()){
        char c = client.read(); // char
       
       
       if(readStrings.length() < 100){ // readStrings 100 readStrings server
         readStrings += c;
       }
    
        if(c=='\n'){                      // ARMA EL HTML DE ACUERDO DE TU NECESIDAD
            Serial.println(readStrings); // Serial
            client.print("HTTP/1.1 200 OK\r\n"); //send new page
            client.print("Content-Type: text/html\r\n\r\n"); 
            client.print("<!DOCTYPE HTML>\r\n");
            client.print("<HTML>\r\n");//html tag
            client.print("<HEAD>\r\n"); //
//            client.print("<meta http-equiv='refresh' content='10'/>\r\n");
            client.print("<meta name='apple-mobile-web-app-capable' content='yes' />\r\n");
            client.print("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />\r\n");
            client.print("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />\r\n");
            client.print("<TITLE>eMGing WiFi</TITLE>\r\n");
            client.print("</HEAD>\r\n");
            client.print("<BODY>\r\n");// body web
            client.print("<H1>Test eMGing.com.ar </H1>\r\n"); 
            client.print("<H2>Test de Control de luces con Shield eMGing WiFi + Shield eMGing Relay</H2>\r\n"); 
            client.print("<hr />\r\n");
            client.print("<br />\r\n");  
            client.print("<H2>Seleccione la luz a Encender/Apagar</H2>\r\n");
            client.print("<br />\r\n");  
            client.print("<a href=\"/?relay1on\"><font color = \"green\">LUZ 1 On</font></a>\r\n");// link server relay
            client.print("<a href=\"/?relay1off\"><font color = \"red\">LUZ 1 Off</font></a><br />\r\n");   
            client.print("<br />\r\n");     
            client.print("<a href=\"/?relay2on\"><font color = \"green\">LUZ 2 On</font></a>\r\n");
            client.print("<a href=\"/?relay2off\"><font color = \"red\">LUZ 2 Off</font></a><br />\r\n");   
            client.print("<br />\r\n"); 
            client.print("<a href=\"/?relay3on\"><font color = \"green\">LUZ 3 On</font></a>\r\n");
            client.print("<a href=\"/?relay3off\"><font color = \"red\">LUZ 3 Off</font></a><br />\r\n");    
            client.print("<br />\r\n"); 
            client.print("<a href=\"/?relay4on\"><font color = \"green\">LUZ 4 On</font></a>\r\n");
            client.print("<a href=\"/?relay4off\"><font color = \"red\">LUZ 4 Off</font></a><br />\r\n");   
            client.print("<br />\r\n"); 
            client.print("<br />\r\n");
            client.print("<a href=\"/?relayallon\"><font color = \"green\">LUCES TODAS ENCENDIDAS</font></a>\r\n");
            client.print("<br />\r\n");
            client.print("<br />\r\n");
            client.print("<a href=\"/?relayalloff\"><font color = \"red\">LUCES TODAS APAGADAS</font></a>\r\n");
            client.print("<br />\r\n");
            client.print("</BODY>\r\n");
            client.print("</HTML>\n");
            
            delay(1);
            
            client.stop(); // client stop
            
            
           
            if(readStrings.indexOf("?relay1on") > 0){
              Serial.println("1 on");
              state_relay1=false;
              digitalWrite(RELAY1,LOW);
            }
            
            if(readStrings.indexOf("?relay1off") >0){
              Serial.println("1 off");
              state_relay1=true;
              digitalWrite(RELAY1,HIGH);
            }
            
            if(readStrings.indexOf("?relay2on") >0){
              Serial.println("2 on");
              state_relay2=false;
              digitalWrite(RELAY2,LOW);
            }
            if(readStrings.indexOf("?relay2off")>0){
              Serial.println("2 off");
              state_relay2=true;
              digitalWrite(RELAY2,HIGH);
            }
            if(readStrings.indexOf("?relay3on")>0){
              digitalWrite(RELAY3,LOW);
              state_relay3=false;
              Serial.println("3 on");
            }
            if(readStrings.indexOf("?relay3off")>0){
              digitalWrite(RELAY3,HIGH);
              state_relay3=true;
              Serial.println("3 off");
            }
            if(readStrings.indexOf("?relay4on")>0){
              digitalWrite(RELAY4,LOW);
              state_relay4=false;
              Serial.println("4 on");
            }
            if(readStrings.indexOf("?relay4off")>0){
              digitalWrite(RELAY4,HIGH);
              state_relay4=true;
              Serial.println("4 off");
            }

            if(readStrings.indexOf("?relay1")>0){
              if(state_relay1==false){
                state_relay1=true;
                digitalWrite(RELAY1, LOW);
              }
              else{
                state_relay1=false;
                digitalWrite(RELAY1, HIGH);
              }
            }

            if(readStrings.indexOf("?relay2")>0){
              if(state_relay2==false){
                state_relay2=true;
                digitalWrite(RELAY2, LOW);
              }
              else{
                state_relay2=false;
                digitalWrite(RELAY2, HIGH);
              }
            }

            if(readStrings.indexOf("?relay3")>0){
              if(state_relay3==false){
                state_relay3=true;
                digitalWrite(RELAY3, LOW);
              }
              else{
                state_relay3=false;
                digitalWrite(RELAY3, HIGH);
              }
            }

            if(readStrings.indexOf("?relay4")>0){
              if(state_relay4==false){
                state_relay4=true;
                digitalWrite(RELAY4, LOW);
              }
              else{
                state_relay4=false;
                digitalWrite(RELAY4, HIGH);
              }
            }
            
            if(readStrings.indexOf("?relayallon")>0){
              digitalWrite(RELAY1,LOW);
              digitalWrite(RELAY2,LOW);
              digitalWrite(RELAY3,LOW);
              digitalWrite(RELAY4,LOW);
            }
            if(readStrings.indexOf("?relayalloff")>0){
              digitalWrite(RELAY1,HIGH);
              digitalWrite(RELAY2,HIGH);
              digitalWrite(RELAY3,HIGH);
              digitalWrite(RELAY4,HIGH);
            }
          readStrings = "";
        }//if(c == '\n')
       }//if(client.available())
      }//while(client.connected())
    }//if(client)
}//void loop()
