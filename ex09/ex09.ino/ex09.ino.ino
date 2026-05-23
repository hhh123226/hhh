#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "Redmi K70";
const char* password = "zkk123580";
#define TOUCH_PIN T0   // T0 = GPIO4 触摸引脚

WebServer server(80);

// 优化后网页：样式更好、带实时提示、中文适配
const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>ESP32 实时触摸仪表盘</title>
    <style>
        body {
            text-align: center;
            margin-top: 100px;
            font-family: "微软雅黑", Arial;
            background-color: #f5f5f5;
        }
        h2 {
            color: #222;
        }
        #data {
            font-size: 60px;
            font-weight: bold;
            color: #0066cc;
        }
        .tip {
            font-size: 18px;
            color: #666;
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <h2>实时触摸传感器仪表盘</h2>
    <p>触摸数值：<span id="data">0</span></p>
    <div class="tip">手靠近引脚 → 数值变小 | 手离开 → 数值恢复</div>

    <script>
        // AJAX 定时拉取触摸数据，100ms刷新一次
        function updateData() {
            fetch("/data")
                .then(response => response.text())
                .then(value => {
                    document.getElementById("data").innerText = value;
                })
                .catch(err => console.log("数据获取失败"));
        }
        // 定时循环获取
        setInterval(updateData, 100);
    </script>
</body>
</html>
)HTML";

// 访问主页，返回网页
void handleRoot() {
    server.send(200, "text/html", htmlPage);
}

// 提供触摸数据接口，网页实时获取
void handleGetData() {
    int touchVal = touchRead(TOUCH_PIN);
    server.send(200, "text/plain", String(touchVal));
}

void setup() {
    Serial.begin(115200);
    Serial.println("正在连接WiFi...");

    // 连接WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // 连接成功打印IP
    Serial.println("\n✅ WiFi连接成功");
    Serial.print("🌐 网页访问地址：");
    Serial.println(WiFi.localIP().toString());

    // 注册网页路由与数据接口
    server.on("/", handleRoot);
    server.on("/data", handleGetData);

    // 启动Web服务器
    server.begin();
    Serial.println("Web仪表盘已启动");
}

void loop() {
    // 持续处理网页请求
    server.handleClient();
}
