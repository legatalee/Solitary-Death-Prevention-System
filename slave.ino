#include <SoftwareSerial.h>
SoftwareSerial HC12(2, 3);

unsigned long prev_time = 0;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(9, INPUT_PULLUP);

  digitalWrite(4, HIGH);
}

void loop() {
  if (digitalRead(5) == HIGH) {
    prev_time = millis();
  }

  unsigned long current_time = millis();
  if (current_time - prev_time > 5000) {
    digitalWrite(LED_BUILTIN, HIGH);

    digitalWrite(4, LOW);
    sendDieSignal();
    digitalWrite(4, LOW);
    prev_time = current_time;
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (digitalRead(9) == LOW) {
    HC12.write("done");
    digitalWrite(4, HIGH);
    delay(300);
  }
}

void sendDieSignal() {
  digitalWrite(4, LOW);
  HC12.write("emg");
  delay(100);
  digitalWrite(4, LOW);
  HC12.write("Human Dead in DIMIGO 2-5");
  Serial.println("send complete!");

  digitalWrite(4, LOW);
}

