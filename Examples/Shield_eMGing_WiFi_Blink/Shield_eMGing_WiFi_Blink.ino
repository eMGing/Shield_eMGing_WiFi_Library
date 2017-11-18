/*
 Ejemplo BLINK para Shield eMGing WiFi con módulo ESP8266
 Este proyecto hace titilar alternadamente el LED del módulo
 ESP8266 y el LED "L" del Shield eMGing Wifi
 
 El LED AZUL del módulo esta conectado al GPIO2 que es el PIN de TXD
 del módulo, por lo tanto con este proyecto no se puede usar Serial.print()
 al mismo tiempo
 
*/
#define LED_MODULE 2
#define LED_SHIELD 14

void setup() {
  pinMode(LED_MODULE, OUTPUT);     // Initialize the LED_MODULE pin as an output
  pinMode(LED_SHIELD, OUTPUT);     // Initialize the LED_SHIELD pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_MODULE, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(LED_SHIELD, LOW);   // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_MODULE, HIGH);  // Turn the LED off by making the voltage HIGH
  digitalWrite(LED_SHIELD, HIGH);
  delay(1000);                      // Wait for a second (to demonstrate the active low LED)
}
