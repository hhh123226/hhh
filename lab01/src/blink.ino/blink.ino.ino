// 定义板载LED引脚（ESP32 DevKit默认板载LED引脚为2）
#define LED_PIN 2

// setup() 函数：仅在程序启动时执行一次
void setup() {
  // 初始化串口通信，波特率设置为115200
  Serial.begin(115200);
  // 将LED引脚设置为输出模式
  pinMode(LED_PIN, OUTPUT);
}

// loop() 函数：程序启动后循环执行
void loop() {
  // 串口输出调试信息
  Serial.println("HELLO ESP32!");
  
  // 点亮LED
  digitalWrite(LED_PIN, HIGH);
  // 保持点亮状态1000毫秒（1秒）
  delay(1000);
  
  // 熄灭LED
  digitalWrite(LED_PIN, LOW);
  // 保持熄灭状态1000毫秒（1秒）
  delay(1000);
}
