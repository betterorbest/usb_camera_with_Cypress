# usb camera with Cypress
usb camera with Cypress是一款简单的相机软件，该软件专用于基于Cypress usb控制芯片的cmos相机，由于下位机没有实现UVC格式的图像传输，因此，该软件通过CyAPI.lib提供的数据传输接口实现图像数据流的接收。
## 开发环境
使用vs2013 + Qt5.5.0插件开发，用到第三方库CyAPI.lib以及opencv2.4.11，界面采用Qt框架。
## 注意
opencv需要自行下载，并配置，主要是修改opencv.props和opecv_release.props两个配置文件
## test_for_hardware分支用于与硬件开发人员协同开发

1. .ini文件中有传输控制的域，方便调试

>     [Camera034]
>     width=1280
>     height=960
>     pixBitswidth=8
>     iscolor=false
> 
>     [Transfer]
>     packetnum=400
>     xferquesize=2
>     timeout=1000
>     buffernum=2

 - packetnum：每个传输事务接收packet的数目，当前packetSize = 1024，每次事务接收
sizePerXfer=packetnum*packetSize字节大小的数据，图像一帧数据大小应当是sizePerXfer的倍数
 - xferquesize：传输事务队列大小，表示接收一帧图像过程中，人为分配的异步进行传输事务的个数
 - buffernum：图像接收缓冲区的大小

2. 在界面增加配置cmos寄存器的功能，删除一些测试不需要的界面逻辑