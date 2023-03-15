# NodeMcuCar
**项目介绍：** 
本项目利用ESP8266 Wi-Fi模块和L298N驱动板控制一辆四轮小车运动。该小车使用L298N驱动器控制四个直流电机的方向和速度。通过局域网Wi-Fi连接到网页，用户可以通过手机或电脑上的网页控制小车的移动。  
![banner](https://github.com/TheBinaryBandit/NodeMcuCar/blob/main/NodeMcuCar.png)  
  
  
  ---
  
**该项目的材料清单包括：**
1.  ESP8266Wi-Fi模块（CP2102+数据线） x 1 
2.  MB-102面包板 x 1
3.  20cm杜邦线若干（公对母）
4.  智能小车底盘（单层4WD）x 1
5.  11.1V 电池 x 1
> 以上这些材料，淘宝或者拼多多购买就行了。

------------
**项目环境搭建以及Arduino库:**
1. 下载和安装Arduino IDE  
你可以从官方网站下载Arduino IDE，然后按照指示安装它。请注意这里我的版本是__1.8.19 Arduino IDE__，若下载最新版本的Arduino IDE可能存在开发板兼容问题。
</br>**官方网站：https://www.arduino.cc/en/software**  
  
2. 安装ESP8266支持  
打开Arduino IDE，然后从菜单中选择“文件” -> “首选项”。在打开的首选项对话框中输入以下网址，然后单击“OK”：  
</br>**http://arduino.esp8266.com/stable/package_esp8266com_index.json**  
  
![首选项](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-open-preferences.png?w=197&quality=100&strip=all&ssl=1)
  
![输入](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-enter-URL.png?w=722&quality=100&strip=all&ssl=1)  

  

3.    接下来，从菜单中选择“工具” -> “开发板” -> “开发板管理器”，然后在搜索框中输入“ESP8266”。单击搜索结果中的“esp8266 by ESP8266 Community”以安装支持。


![工具栏](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-open-boards-manager.png?w=671&quality=100&strip=all&ssl=1)  

![搜索esp8266](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-search-ESP8266.png?w=786&quality=100&strip=all&ssl=1)  

![安装](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/ESP8266-Board-add-on-in-Arduino-IDE-installed.png?w=786&quality=100&strip=all&ssl=1)  
  
  
 
4.    选择开发板

从菜单中选择“工具” -> “开发板”，然后选择NodeMCU开发板。在同一菜单中，选择ESP8266 Boards->Node MCU 1.0 (ESP12E Module)。  

![esp12E Module](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-select-board.png?w=669&quality=100&strip=all&ssl=1)  
  
  
  
5.    Arduino库  
为了让代码能够控制小车和使用ESP8266的Wi-Fi功能，你需要使用以下Arduino库：  
* ESPAsyncTCP.h   
> 库是ESPAsyncTCP.h，它是ESP8266上的异步TCP库，提供了一组函数用于处理TCP连接、发送和接收数据等操作。该库通常与ESPAsyncWebServer.h一起使用，以创建异步Web服务器。
* ESP8266WiFi.h   
> ESP8266WiFI.h这个库是用于ESP8266 Wi-Fi模块的Arduino库，它允许你在ESP8266上创建一个Wi-Fi访问点或连接到现有的Wi-Fi网络。该库提供了一组函数，可用于设置Wi-Fi模式、连接到Wi-Fi网络、获取IP地址等操作。
* ESPAsyncWebServer.h  
> ESPAsyncWebServer.h这个库是一个基于ESPAsyncTCP库的异步Web服务器库，它允许你在ESP8266上创建一个Web服务器并处理HTTP请求。该库提供了一组函数，用于创建Web服务器、处理HTTP请求、发送HTTP响应等操作。
  
  
安装这3个库的方法有2种。  
第1种方法:  
1.打开Arduino IDE，进入“工具”菜单，选择“管理库”选项。  
2.在弹出的“库管理器”对话框中，搜索需要安装的库。输入关键字“ESPAsyncTCP”或“ESPAsyncWebServer”，然后点击搜索按钮。  
3.在搜索结果中找到对应的库，并点击“安装”按钮。  
4.安装完成后，你就可以在Arduino IDE的“文件”菜单中选择“示例”选项，找到对应的示例代码进行学习和实验了。  
第2种方法:  
1.去Google直接搜索ESPAsyncTCP和ESPAsyncWebServer下载zip文件包。下载ESPAsyncWebServer的源代码，并将它解压到一个临时文件夹中。  
2.打开Arduino IDE，进入“文件”菜单，选择“首选项”选项，找到“Sketchbook位置”选项。  
3.在“Sketchbook位置”选项中，找到“libraries”文件夹，并进入该文件夹。  
4.在“libraries”文件夹中创建一个新的文件夹，命名为“ESPAsyncWebServer”。  
5.将解压后的ESPAsyncWebServer源代码中的所有文件和文件夹复制到“ESPAsyncWebServer”文件夹中。  
6.重启Arduino IDE，你就可以在“文件”菜单中选择“示例”选项，找到ESPAsyncWebServer库的示例代码进行学习和实验了。  

----

### **连接线引脚图（ESP8266和L298N驱动）**  
  

| ESP8266      | L298N驱动     | 
| ---------- | :-----------: | 
| D3     |   IN4   |     
| D4     |   IN3   |  
| D5     |   ENA   |  
| D6     |   ENB   | 
| D7     |   IN2   |  
| D8     |   IN1   |  
  
请将买来的ESP8266开发板插在MB-102面包板上,请看下图:   

![面包板使用](https://srituhobby.com/ezoimgfmt/i0.wp.com/srituhobby.com/wp-content/uploads/2021/03/8-5.jpg?w=1024&ssl=1&ezimgfmt=ng:webp/ngcb1)  
  
将公杜邦线(尖头)插在ESP8266开发板的D3口，母线插在L298N的IN4口。以此类推，根据连接线引脚图对接线路。  
__提示：__ ESP8266的D5口需要插在L298N的ENA口（在IN1口旁边，需要把帽盖用钳子拔开），ESP8266的D6口需要插在L298N的ENB口（在IN4的旁边，需要把帽盖用钳子拔开）  
  

   ----  

  
## **代码部分**

![ESP8266引脚图](https://upload-images.jianshu.io/upload_images/1396375-621620a4b07dbc3e.png?imageMogr2/auto-orient/strip|imageView2/2/w/791/format/webp)    
  
```C 
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
```  
   
   
     
     
