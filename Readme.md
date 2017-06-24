# usb camera with Cypress
usb camera with Cypress是一款简单的相机软件，该软件专用于基于Cypress usb控制芯片的cmos相机，由于下位机没有实现UVC格式的图像传输，因此，该软件通过CyAPI.lib提供的数据传输接口实现图像数据流的接收。
## 开发环境
使用vs2013 + Qt5.5.0插件开发，用到第三方库CyAPI.lib以及opencv2.4.11，界面采用Qt框架。
## 注意
opencv需要自行下载，并配置，主要是修改opencv.props和opecv_release.props两个配置文件
## release_spectrometer分支， 光谱仪的发行分支
1. 在光谱仪开发分支基础上，修改界面布局，去掉数字增益、帧率、温度显示