int led = 3;
int laser = 2;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(laser, OUTPUT);
  digitalWrite(laser, HIGH);
  Serial.begin(9600);

}

void loop() {
  int ldr = analogRead(A0);
  Serial.print(ldr);
  Serial.println(" ");

  if (ldr < 80) {
    digitalWrite(led, HIGH);

  } else {
    digitalWrite(led, LOW);
  }
  delay(500);
}




