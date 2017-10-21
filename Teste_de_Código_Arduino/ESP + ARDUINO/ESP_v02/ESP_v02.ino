#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial wifi(10, 11); //RX, TX

void setup() {

  //Seta ambas seriais para a velocidade de 9600
  Serial.begin(9600);
  //(em alguns casos a velocidade do seu esp8266 pode estar diferente desta)
  wifi.begin(9600);

  //declara os pinos como saida
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  //Envia o comandos AT

  // reseta o modulo
  SendCommand("AT+RST\r\n", 2000, DEBUG);
  // configure as access point e estação (ambos)
  SendCommand("AT+CWMODE=3\r\n", 1000, DEBUG);
  //conecta ao roteador com a senha
  //(esta configuração deve ser feita, pois o seu roteador tem nome diferente do meu e senha)
  SendCommand("AT+CWJAP=\"Kamuy\",\"cgla48123456789\"r\n", 10000, DEBUG);
  //Retorna o IP ao qual está conectado e o IP de Station
  SendCommand("AT+CIFSR\r\n", 1000, DEBUG);
  //Habilita multiplas conexões
  SendCommand("AT+CIPMUX=1\r\n", 1000, DEBUG);
  //Habilita ao servidor a porta 80
  SendCommand("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  Serial.println("Servidor inicado!");
}

void loop() {

  if (wifi.available()) {

    if (wifi.find("+IPD,")) {
      delay(1000);
      int connectionId = wifi.read() - 48;
      wifi.find("pin=");
      int pinNumber = (wifi.read() - 48) * 10;
      pinNumber += (wifi.read() - 48);

      int secondNumber = (wifi.read() - 48);
      if (secondNumber >= 0 && secondNumber <= 9) {

        pinNumber *= 10;
        pinNumber += secondNumber;
      }
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, !digitalRead(pinNumber));

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId;
      closeCommand += "\r\n";

      //Encerra a conexao
      SendCommand(closeCommand, 1000, DEBUG);
    }
  }
}





