#include "SoftwareSerial.h"
#include <SoftwareSerial.h>
int led = 13;
SoftwareSerial ESP(10, 11); // RX, TX

const int RST = 4;
#define DEBUG true
void setup() {
  pinMode(led, OUTPUT);


  Serial.begin(9600);
  ESP.begin(9600);

 
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  delay(2000);
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
  //Inicia o web server na porta 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  //Pulso em Reset para aceitar comunicacao
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(300);
  digitalWrite(RST, HIGH);
}

void loop() {

  if (ESP.available()) {
    Serial.write(ESP.read());
  }
  if (Serial.available()) {
    ESP.write(Serial.read());
  }
  // Verifica se o ESP8266 esta enviando dados
  if (ESP.available())
  {
    if (ESP.find("+IPD,"))
    {
      delay(300);
      int connectionId = ESP.read() - 48;

      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "</head><h1><u>Controle de luzes.</u></h1>";
      webpage += "<body><button type= button onclick= 'alert'('Hello world!')>LIGAR</button>";
      webpage += "<button type= button onclick= 'alert'('Hello world!')>DESLIGAR</button></body>";

      int a = digitalRead(8);
      webpage += a;
      webpage += "<h2>Porta Digital 9: ";
      int b = digitalRead(9);
      webpage += b;
      webpage += "</h2>";

      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";

      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";

      sendData(closeCommand, 20000, DEBUG);
    }
  }
}
String sendData(String command, const int timeout, boolean debug) {

  // Envio dos comandos AT para o modulo
  String response = "";
  ESP.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (ESP.available())
    {
      // The esp has data so display its output to the serial window
      char c = ESP.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}



