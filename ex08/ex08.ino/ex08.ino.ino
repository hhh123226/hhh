#include <WiFi.h>
#include <WebServer.h>

// -------------------------- 配置区 --------------------------
const char* ssid = "Redmi K70";      
const char* password = "zkk123580";  
const int TOUCH_PIN = T0;              
const int LED_PIN = 2;                 
const int TOUCH_THRESHOLD = 30;        
// -----------------------------------------------------------

WebServer server(80);
bool systemArmed = false;   // 系统布防状态
bool alarmTriggered = false;// 报警触发状态

// 网页前端
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>ESP32 安防报警器</title>
    <style>
        body {
            text-align: center;
            margin-top: 80px;
            font-family: Arial, sans-serif;
        }
        button {
            font-size: 24px;
            padding: 15px 30px;
            margin: 10px;
            cursor: pointer;
            border: none;
            border-radius: 8px;
            color: white;
        }
        #armBtn {
            background-color: #28a745;
        }
        #disarmBtn {
            background-color: #dc3545;
        }
    </style>
</head>
<body>
    <h2>ESP32 安防报警器控制端</h2>
    <button id="armBtn" onclick="armSystem()">布防(Arm)</button>
    <button id="disarmBtn" onclick="disarmSystem()">撤防(Disarm)</button>

    <script>
        function armSystem() {
            fetch("/arm")
                .then(res => res.text())
                .then(msg => alert(msg));
        }
        function disarmSystem() {
            fetch("/disarm")
                .then(res => res.text())
                .then(msg => alert(msg));
        }
    </script>
</body>
</html>
)HTML";

// 根目录请求处理
void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

// 布防请求处理
void handleArm() {
    systemArmed = true;
    alarmTriggered = false; // 布防时重置报警状态
    server.send(200, "text/plain", "系统已布防！");
}

// 撤防请求处理
void handleDisarm() {
    systemArmed = false;
    alarmTriggered = false;
    digitalWrite(LED_PIN, LOW); // 撤防时关闭LED
    server.send(200, "text/plain", "系统已撤防！");
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // 连接WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi连接成功！");
    Serial.print("Web控制端IP地址：");
    Serial.println(WiFi.localIP());

    // 注册路由
    server.on("/", handleRoot);
    server.on("/arm", handleArm);
    server.on("/disarm", handleDisarm);

    // 启动Web服务器
    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient(); // 处理客户端请求

    // 布防状态下检测触摸触发报警
    if (systemArmed && !alarmTriggered) {
        int touchValue = touchRead(TOUCH_PIN);
        Serial.print("当前触摸值：");
        Serial.println(touchValue);
        
        if (touchValue < TOUCH_THRESHOLD) {
            alarmTriggered = true;
            Serial.println("报警触发！");
        }
    }

    // 报警状态下LED高频闪烁
    if (alarmTriggered) {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
}
