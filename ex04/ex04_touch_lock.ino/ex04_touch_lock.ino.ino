#define TOUCH_PIN 4       // 触摸引脚 T0=GPIO4
#define LED_PIN 2         // 板载LED引脚
#define TOUCH_THRESHOLD 20 // 触摸阈值

bool ledState = false;          // LED开关状态
bool lastTouchState = false;    // 上一次触摸状态
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;// 防抖延时50ms

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState); // 初始化LED状态
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);
  bool currentTouchState = (touchValue < TOUCH_THRESHOLD);
  unsigned long currentTime = millis();

  // 软件防抖逻辑
  if (currentTouchState != lastTouchState) {
    lastDebounceTime = currentTime;
  }

  // 防抖完成后，边缘检测：只有松开→按下瞬间才翻转LED
  if ((currentTime - lastDebounceTime) > debounceDelay) {
    if (currentTouchState && !lastTouchState) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }

  lastTouchState = currentTouchState;
  delay(20);
}
