# NodeMcuCar
## **项目介绍：** 
本项目利用ESP8266 Wi-Fi模块和L298N驱动板控制一辆四轮小车运动。该小车使用L298N驱动器控制四个直流电机的方向和速度。通过局域网Wi-Fi连接到网页，用户可以通过手机或电脑上的网页控制小车的移动。

## **该项目的材料清单包括：**
</br>1. ESP8266Wi-Fi模块（CP2102+数据线） x 1 
</br>2. MB-102面包板 x 1
</br>3. 20cm杜邦线若干（公对母）
</br>4. 智能小车底盘（单层4WD）x 1
</br>5. 9v电池 x 1
> 以上这些材料，淘宝或者拼多多购买就行了。

------------
## **项目环境搭建以及Arduino库:**
</br>1. 下载和安装Arduino IDE
>你可以从官方网站下载Arduino IDE，然后按照指示安装它。官方网站：https://www.arduino.cc/en/software

</br>2. 安装ESP8266支持
打开Arduino IDE，然后从菜单中选择“文件” -> “首选项”。在打开的首选项对话框中输入以下网址，然后单击“OK”：
>http://arduino.esp8266.com/stable/package_esp8266com_index.json
接下来，从菜单中选择“工具” -> “开发板” -> “开发板管理器”，然后在搜索框中输入“ESP8266”。单击搜索结果中的“esp8266 by ESP8266 Community”以安装支持。
