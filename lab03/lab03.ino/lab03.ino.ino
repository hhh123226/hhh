//ESP32 实验3 PWM呼吸灯
const int ledPin = 2;
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  //逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(ledPin, dutyCycle);
    delay(15);
  }
  //逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin, dutyCycle);
    delay(15);
  }
  Serial.println("Breathing cycle completed");
}
