// ex02 millis() 实现1Hz LED闪烁（ESP32 GPIO2）
const int ledPin = 2;
unsigned long previousMillis = 0;
const long interval = 500;   // 500ms切换一次，1Hz频率
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  // 非阻塞判断时间
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}