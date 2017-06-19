# usb camera with Cypress
usb camera with Cypress是一款简单的相机软件，该软件专用于基于Cypress usb控制芯片的cmos相机，由于下位机没有实现UVC格式的图像传输，因此，该软件通过CyAPI.lib提供的数据传输接口实现图像数据流的接收。
## 开发环境
使用vs2013 + Qt5.5.0插件开发，用到第三方库CyAPI.lib以及opencv2.4.11，界面采用Qt框架。
## 注意
opencv需要自行下载，并配置，主要是修改opencv.props和opecv_release.props两个配置文件
## usb3.0红外可见光双光融合开发分支

 1. 实现红外、可见光图像数据的稳定接收
 - 红外图像分辨率 640 * 512， 像素位宽14位
 - 可见光图像分辨率 1280 * 960， 像素位宽12位
 2. 实现红外、可见光raw数据到图像显示数据的转换
 - 红外图像实现灰度、灰度反转、金属、彩虹三种颜色编码
 - 可见光图像实现12位宽raw数据到彩色图像rgb888的转换
 3. 实现目前测试所需的界面逻辑
 4. camconfig.ini添加Dual域控制软件初始化配置