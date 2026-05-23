#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Redmi K70";
const char* password = "zkk123580";

WebServer server(80);
const int ledPin = 2;     // D2引脚 GPIO2
int brightness = 0;        // 亮度值 0~255

// 主页面：滑块+输入框+开关按钮
void handleRoot() {
  String html = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<title>ESP32 滑块调亮度</title>
<style>
body{text-align:center;font-size:20px;margin-top:40px;}
button{font-size:18px;padding:8px 20px;margin:10px;}
input[type="range"]{width:400px;height:20px;margin:20px 0;}
</style>
</head>
<body>
<h2>ESP32 网页控制LED亮度</h2>

<a href="/on"><button>🔆 开灯</button></a>
<a href="/off"><button>🌑 关灯</button></a>

<p>拖动滑块调节亮度：</p>
<form action="/set" method="POST">
    <input type="range" name="val" min="0" max="255" value=")HTML" + String(brightness) + R"HTML(" 
           oninput="this.form.submit()">
</form>

<p>当前亮度值：)HTML" + String(brightness) + R"HTML(</p>
</body>
</html>
)HTML";

  server.send(200, "text/html", html);
}

// 接收亮度值
void handleSetBright() {
  if (server.hasArg("val")) {
    brightness = server.arg("val").toInt();
    brightness = constrain(brightness, 0, 255); // 限制0~255
    analogWrite(ledPin, brightness);
    Serial.print("亮度更新：");
    Serial.println(brightness);
  }
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

// 一键最亮
void handleOn() {
  brightness = 255;
  analogWrite(ledPin, 255);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

// 一键熄灭
void handleOff() {
  brightness = 0;
  analogWrite(ledPin, 0);
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功 IP：" + WiFi.localIP().toString());

  // 绑定路由
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/set", HTTP_POST, handleSetBright);

  server.begin();
  Serial.println("Web服务器启动完成");
}

void loop() {
  server.handleClient();
}
