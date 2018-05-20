# usb camera with Cypress
usb camera with Cypress是一款简单的相机软件，该软件专用于基于Cypress usb控制芯片的cmos相机，由于下位机没有实现UVC格式的图像传输，因此，该软件通过CyAPI.lib提供的数据传输接口实现图像数据流的接收。
## 开发环境
使用vs2013 + Qt5.5.0插件开发，用到第三方库CyAPI.lib以及opencv2.4.11，界面采用Qt框架。
## 注意
opencv需要自行下载，并配置，主要是修改opencv.props和opecv_release.props两个配置文件
## develop_spectrometer分支， 光谱仪的开发分支
1. 简单实现与光谱仪的通信
2. 根据光谱仪硬件，适配初始控制
3. 修改基本框架，usb控制端点数据发送函数会在设备和GUI两个线程中调用，增加互斥
4. 增加图像镜像控制，波长slider下方显示刻度
5. 修改曝光控制，增加折线映射图像数据，增加状态栏显示软件运行状态
6. 利用QCustomPlot添加光谱曲线绘制功能
7. 增加打开相机时关于界面所示相机参数的设置
8. 获取参考光时，添加曝光、模拟增益自调节功能
9. 在界面添加参考光像素均值上下界的设置功能，方便测试
## 说明
模拟增益相关的逻辑错误在release_spectrometer分支修复，当前分支依然存在该bug，以此说明，该分支可废弃
