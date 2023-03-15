# NodeMcuCar
**项目介绍：** 
本项目利用ESP8266 Wi-Fi模块和L298N驱动板控制一辆四轮小车运动。该小车使用L298N驱动器控制四个直流电机的方向和速度。通过局域网Wi-Fi连接到网页，用户可以通过手机或电脑上的网页控制小车的移动。  

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

---
2. 安装ESP8266支持  
打开Arduino IDE，然后从菜单中选择“文件” -> “首选项”。在打开的首选项对话框中输入以下网址，然后单击“OK”：  
</br>**http://arduino.esp8266.com/stable/package_esp8266com_index.json**  
  
![首选项](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-open-preferences.png?w=197&quality=100&strip=all&ssl=1)
  
![输入](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-enter-URL.png?w=722&quality=100&strip=all&ssl=1)  

---

3.    接下来，从菜单中选择“工具” -> “开发板” -> “开发板管理器”，然后在搜索框中输入“ESP8266”。单击搜索结果中的“esp8266 by ESP8266 Community”以安装支持。


![工具栏](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-open-boards-manager.png?w=671&quality=100&strip=all&ssl=1)  

![搜索esp8266](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-search-ESP8266.png?w=786&quality=100&strip=all&ssl=1)  

![安装](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/ESP8266-Board-add-on-in-Arduino-IDE-installed.png?w=786&quality=100&strip=all&ssl=1)  

---

4.    选择开发板

从菜单中选择“工具” -> “开发板”，然后选择NodeMCU开发板。在同一菜单中，选择ESP8266 Boards->Node MCU 1.0 (ESP12E Module)。  

![esp12E Module](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/07/Install-ESP8266-Board-add-on-in-Arduino-IDE-select-board.png?w=669&quality=100&strip=all&ssl=1)  

---

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

  
## **部分代码讲解：**

![ESP8266引脚图](https://upload-images.jianshu.io/upload_images/1396375-621620a4b07dbc3e.png?imageMogr2/auto-orient/strip|imageView2/2/w/791/format/webp)    
  
```C 
#define ENA 14      // L298N: ENA -> ESP8266:D5  
#define ENB 12      // L298N :ENB -> ESP8266:D6  
#define IN_1 15     // L298N: IN1 -> ESP8266:D8  
#define IN_2 13     // L298N: IN2 -> ESP8266:D7  
#define IN_3 2      // L298N: IN3 -> ESP8266:D4  
#define IN_4 0      // L298N: IN4 -> ESP8266:D3  
``` 
> 使用宏定义，定义ESP8266引脚(D8,D7,D6,D5,D4,D3)，它们用于控制小车的电机和方向。   
  
  
   
---
   
  
```C
const char *ssid = "";
const char *password  = "";
const char *PARAM_dir = "dir";
```
>定义WiFi的用户名和密码，PARAM_dir参数，请注意ssid的赋值是填写你自己家的WIFI名字，例如WiFi名字为：我是帅哥。	:laughing:那么ssid就是填写我是帅哥，然后password是WiFi密码。
  
  
  
---
  
   
```C
const char index_html[] PROGMEM = R"rawliteral()rawliteral()";  
```
    
>这行代码定义了一个名为 __index_html__ 的常量字符数组，使用了C++11引入的原始字面量（Raw String Literal）语法，用于在代码中直接定义多行字符串。  
__const__ 关键字表示 __index_html__ 是一个常量，不能在程序中被修改，只能被读取。  
char表示这是一个字符数组。  
__PROGMEM__ 是一个宏定义，将数据存储在程序存储器中（也称为“程序空间”），而不是RAM中，可以节省RAM的使用，特别适用于内存有限的嵌入式系统。    
__R"rawliteral()__ 是一个C++11引入的原始字面量语法，用于直接定义多行字符串，其中 __rawliteral__ 可以替代为任何非转义字符，如 __R"str()__ 或者 __R"file()__ 等。  
所以这行代码定义了一个空字符串 __indexhml__ 并将其存储在程序存储器中，常用于嵌入式系统中的Web服务器等场景。  
  
  
  
---
    
  
```C
void setup()
{
 Serial.begin(115200);

 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
```
  
>开启串口通信，波特率为115200，以便后面可以通过串口打印调试信息。初始化一些针脚模式，将ENA、ENB、IN_1、IN_2、IN_3、IN_4这几个针脚设置为输出模式，以便控制电机的运动方向和速度。  
其中，ENA和ENB是控制电机转速的PWM针脚，IN_1、IN_2、IN_3、IN_4是控制电机方向的针脚。通过设置这些针脚的输出电平，可以控制电机的转速和方向，从而控制小车的运动。  
  
---
  
  
    
```C
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  // 打印出本地IP地址便于访问
  Serial.println(WiFi.localIP());
```
  
>这段代码是用于连接WiFi并获取本地IP地址的。首先使用WiFi.begin(ssid, password);连接到指定的WiFi网络，其中ssid和password分别是WiFi的名称和密码。然后使用while循环和WiFi.status()函数等待连接成功，当WiFi状态为WL_CONNECTED时退出循环，此时表示已经连接成功。接着使用Serial.println(WiFi.localIP());打印出ESP8266模块所连接的WiFi网络分配的本地IP地址，方便用户访问和控制。  
    
---
  
  
```C  
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
   request->send_P(200, "text/html", index_html);
   Serial.print("get success!");
  });
```C
  
>设置服务器路由，使其能够响应对根路径/的HTTP GET请求，并返回HTML页面。  
  
      
---
  
  
```C
server.on("/direction", HTTP_GET, [](AsyncWebServerRequest *request) {
  int speedCar =0;
  String dir = ""; 
```
  
>在服务器对象上设置了一个名为“direction”的HTTP GET路由，该路由通过request对象的getParam函数来获取speedCar和dir参数的值，分别表示小车的速度和方向。  
  
        
---
  
```C
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
  ```
   
 >如果获取成功，则分别将speedCar和dir打印到串口中，并通过ENA、ENB、IN_1、IN_2、IN_3和IN_4等引脚控制小车的运动。  
   
   
     
     
