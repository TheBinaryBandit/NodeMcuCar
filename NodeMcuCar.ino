//这是一段使用NodeMCU控制小车的代码，包含了一个基于ESPAsyncWebServer库的Web服务器，可以通过WiFi连接控制小车的移动。
// 小车的运动可以通过局域网WLAN访问地址进行控制，使用L298N驱动器、ESP8266 (CP2102)和11.1V锂电池，只需要连接相同的网络，就可以通过手机或电脑来实现控制。
// 代码通过#include指令引入了ESP8266WiFi、ESPAsyncWebServer和ESPAsyncTCP三个库。
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>

// 使用宏定义，定义ESP8266引脚(D8,D7,D6,D5,D4,D3)，它们用于控制小车的电机和方向。
#define ENA 14      // L298N: ENA -> ESP8266:D5
#define ENB 12      // L298N :ENB -> ESP8266:D6
#define IN_1 15     // L298N: IN1 -> ESP8266:D8
#define IN_2 13     // L298N: IN2 -> ESP8266:D7
#define IN_3 2      // L298N: IN3 -> ESP8266:D4
#define IN_4 0      // L298N: IN4 -> ESP8266:D3


// 定义WiFi的用户名和密码，PARAM_dir参数。
const char *ssid = "";
const char *password  = "";
const char *PARAM_dir = "dir";

//创建一个AsyncWebServer 80端口，可以通过该端口访问服务器。
AsyncWebServer server(80);

// 定义一个HTML页面，其中包含了小车控制的相关控件，这里使用HTML创建UI界面，Javascript建立调用函数。
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<link rel="shortcut icon" href="#" />

    <title>WiFi 遥控小车</title>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            background-color: rgb(0,0,0);
            color:rgb(254,220,0);
            font-family: Arial;
            text-align: center;
        }
        h2{
            font-size: 5.0rem;
        }
        button {
            text-align: center;
            height: auto;
            font-size: 10px;
            margin: 10px;
            padding: 20px 40px;
            border-radius: 5px;
            background-color: rgb(254,220,0);
            color: rgb(0,0,0);
            border: none;
            cursor: pointer;
            transition: all 0.2s ease-in-out;          
        }
        .parent {
            display: flex;
            justify-content: center;
            align-items: center;
        }
        button:active {
            background-color: rgb(212, 29, 29);
        }  
    </style>
</head>
<body>
  <h2>NodeMCU小车控制</h2>
  <p>小车速度控制</p>
  <label for="speedSlider">速度控制器: </label>
  <input type="range" min="0" max="255" value="0" class="slider" id="speedSlider">
  <div class="parent">
    <button class="button" onclick="sendCommand('F', speedCar)" id="F">前进</button>
  </div>
  <div class="parent">
    <button class="button" onclick="sendCommand('L', speedCar)" id="L">左转</button>
    <button class="button" onclick="sendCommand('S', speedCar)" id="S">停止</button>
    <button class="button" onclick="sendCommand('R', speedCar)" id="R">右转</button>
  </div>
  <div class="parent">
    <button class="button" onclick="sendCommand('B', speedCar)" id="B">后退</button>
  </div>
  <script>
     let speedCar = 0;
let direction = 'S';

let sendCommand = function(dir, speedCar) {
  let xhr = new XMLHttpRequest();
  xhr.open("GET", "/direction?dir=" + dir + "&speedCar=" + speedCar, true);
  xhr.send();
};

let slider = document.getElementById("speedSlider");

let updateSpeed = function() {
  speedCar = slider.value;
  console.log(speedCar);
};

slider.oninput = function() {
  updateSpeed();
};

let loop = setInterval(function() {
  if (direction !== 'S') {
    sendCommand(direction, speedCar);
  }
}, 100);

let setDirection = function(dir) {
  if (dir === direction) {
    direction = 'S';
    sendCommand(direction, speedCar);
  } else {
    direction = dir;
  }
};

document.getElementById('F').onclick = function() {
  setDirection('F');
};

document.getElementById('L').onclick = function() {
  setDirection('L');
};

document.getElementById('S').onclick = function() {
  setDirection('S');
};

document.getElementById('R').onclick = function() {
  setDirection('R');
};

document.getElementById('B').onclick = function() {
  setDirection('B');
};
    </script>
</body>
</html>
)rawliteral";

// 在setup函数中，首先进行了串口初始化，然后将ENA、ENB、IN_1、IN_2、IN_3和IN_4等引脚设置为输出模式。
// 接下来，使用WiFi.begin连接WiFi网络，然后等待连接成功。
// 最后，设置服务器路由，使其能够响应对根路径/的HTTP GET请求，并返回HTML页面。
void setup()
{
 Serial.begin(115200);

 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 

  // 接下来，使用WiFi.begin连接WiFi网络，然后等待连接成功。
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // 打印出本地IP地址便于访问
  Serial.println(WiFi.localIP());

  // 设置服务器路由，使其能够响应对根路径/的HTTP GET请求，并返回HTML页面。
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
   request->send_P(200, "text/html", index_html);
   Serial.print("get success!");
  }); 


// 在服务器对象上设置了一个名为“direction”的HTTP GET路由，该路由通过request对象的getParam函数来获取speedCar和dir参数的值，
// 分别表示小车的速度和方向。
server.on("/direction", HTTP_GET, [](AsyncWebServerRequest *request) {
  int speedCar =0;
  String dir = ""; 

// 如果获取成功，则分别将speedCar和dir打印到串口中，并通过ENA、ENB、IN_1、IN_2、IN_3和IN_4等引脚控制小车的运动。

  if(request->hasParam("speedCar")){
    speedCar = request->getParam("speedCar")->value().toInt();
    Serial.print("get speedCar: ");Serial.println(speedCar);
    }
       if(request->hasParam("dir")){
       dir = request->getParam("dir")->value().c_str();
       Serial.print("get dir: ");Serial.println(dir);
       }
    
    handleDirection(dir,speedCar);

     request->send(200, "text/html", "Received direction parameter: " + dir + "Recive Car Speed: " + speedCar);
   
  });
  server.begin();
  }

  void handleDirection(String dir, int speedCar){
    if (dir == "F") {
      Serial.println("Moving forward...");
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      }


      else if(dir =="L"){
      Serial.println("Moving goLeft...");
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      }
       else if(dir =="S"){
      Serial.println("Moving stopRobot...");
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      }
       else if(dir =="R"){
      Serial.println("Moving goRight...");
       digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      }


      else if(dir =="B"){
       Serial.println("Moving goBack...");
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
        
      }
      
    }
    


void loop(){

}
