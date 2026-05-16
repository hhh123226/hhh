#define LED_A 2    // 第一个LED 板载
#define LED_B 13   // 第二个LED 外接GPIO13

const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_A, freq, resolution);
  ledcAttach(LED_B, freq, resolution);
}

void loop() {
  // A变亮 B变暗
  for(int duty=0; duty<=255; duty++){
    ledcWrite(LED_A, duty);
    ledcWrite(LED_B, 255 - duty);
    delay(8);
  }
  // A变暗 B变亮
  for(int duty=255; duty>=0; duty--){
    ledcWrite(LED_A, duty);
    ledcWrite(LED_B, 255 - duty);
    delay(8);
  }
}
