

/*
 
 
 Proyecto de prueba eMGing para test de SoftwareSerial

 Recibe mensajes desde el puerto Serie de HARDWARE del Arduino y se lo envía a los 
 puertos Serie de SoftwareSerial, recibe desde SoftwareSerial y lo envía al Serie Hardware.

 El cicuíto:
 * RX es el pin digital número 7 del Arduino(conecta a TX del otro dispositivo)
 * TX es el pin digital número 8 del Arduino(conecta a RX del otro dispositivo)

 Nota:
 NO todos los pines del MEGA o MEGA2560 soporta cambio en los pines de interrupción,
 por lo tanto solo los siguientes pueden utilizarse: RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 NO todos los pines del Leonardo soporta cambio en los pines de interrupción,
 por lo tanto solo los siguientes pueden utilizarse: RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 Para TX pueden usar cualquier PIN sin problemas.
 
 consultas: info@eMGing.com.ar
 web: www.eMGing.com.ar
 FB: @eMGing.com.ar
 Youtube: https://goo.gl/5QtmC8

  */

void setup() {
  // Abre puerto serial de comunicación y espera a que se abra el puerto
  Serial.begin(9600);
  while (!Serial) {
    ; // Espera a que se conecte el puerto. Necesita solo del puerto USB nativo
  }

  Serial.println("Hola Mundo tambien!!");
}

void loop() { // Loop de ejecución de programa
  char c;
  if (Serial.available()) {
    c=Serial.read();
    Serial.write(c);
  }
}
