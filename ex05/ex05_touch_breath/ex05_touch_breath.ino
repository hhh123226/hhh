#define TOUCH_PIN 4
#define LED_PIN 2
#define TOUCH_THRESHOLD 20

int speedLevel = 1;                // 速度档位 1慢 2中 3快
int delayList[] = {30, 15, 5};     // 对应档位延时
bool lastTouch = false;
unsigned long debounceTime = 0;
unsigned long debounceDelay = 50;

// PWM呼吸灯配置
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  ledcAttach(LED_PIN, freq, resolution); // 绑定PWM通道
}

void loop() {
  int touchVal = touchRead(TOUCH_PIN);
  bool currentTouch = (touchVal < TOUCH_THRESHOLD);
  unsigned long now = millis();

  // 触摸防抖+档位循环切换 1→2→3→1
  if (currentTouch != lastTouch) debounceTime = now;
  if (now - debounceTime > debounceDelay) {
    if (currentTouch && !lastTouch) {
      speedLevel++;
      if (speedLevel > 3) speedLevel = 1;
    }
  }
  lastTouch = currentTouch;

  // 呼吸灯主体
  int delayTime = delayList[speedLevel - 1];
  // 渐亮
  for(int i=0; i<=255; i++){
    ledcWrite(LED_PIN, i);
    delay(delayTime);
  }
  // 渐暗
  for(int i=255; i>=0; i--){
    ledcWrite(LED_PIN, i);
    delay(delayTime);
  }
}
