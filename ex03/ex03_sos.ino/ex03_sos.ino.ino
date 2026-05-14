// ex03 millis() 实现SOS求救信号  ESP32 GPIO2
const int ledPin = 2;
unsigned long prevTime = 0;
unsigned long interval = 0;
bool ledOn = false;

// SOS时序定义
const unsigned long shortOn  = 200;
const unsigned long shortOff = 200;
const unsigned long longOn   = 600;
const unsigned long longOff  = 200;
const unsigned long sospause    = 3000;

int stage = 0;  // 0-2:短闪 3-5:长闪 6-8:短闪 9:停顿

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  unsigned long now = millis();
  if(now - prevTime >= interval){
    prevTime = now;
    switch(stage){
      // 第一组 3次短闪
      case 0: ledOn = true; interval = shortOn; break;
      case 1: ledOn = false; interval = shortOff; break;
      case 2: ledOn = true; interval = shortOn; break;
      // 第二组 3次长闪
      case 3: ledOn = false; interval = longOff; break;
      case 4: ledOn = true; interval = longOn; break;
      case 5: ledOn = false; interval = longOff; break;
      // 第三组 3次短闪
      case 6: ledOn = true; interval = shortOn; break;
      case 7: ledOn = false; interval = shortOff; break;
      case 8: ledOn = true; interval = shortOn; break;
      // 循环停顿
      case 9: ledOn = false; interval = sospause; stage = -1; break;
    }
    digitalWrite(ledPin, ledOn);
    stage++;
  }
}


