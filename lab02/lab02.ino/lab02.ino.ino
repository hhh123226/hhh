//ESP32 实验2 基础IO-LED闪烁
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  delay(800);
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  delay(800);
}
