# usb camera with Cypress
usb camera with Cypress是一款简单的相机软件，该软件专用于基于Cypress usb控制芯片的cmos相机，由于下位机没有实现UVC格式的图像传输，因此，该软件通过CyAPI.lib提供的数据传输接口实现图像数据流的接收。
## 开发环境
使用vs2013 + Qt5.5.0插件开发，用到第三方库CyAPI.lib以及opencv2.4.11，界面采用Qt框架。
## 注意
opencv需要自行下载，并配置，主要是修改opencv.props和opecv_release.props两个配置文件
## release_034分支，包含三个项目，还有可能增加，以文件夹加以区分
### 1 usb2_camera_034项目
  相机主程序，不断修改框架，成为master分支
### 2 driver_install_log项目  <small>[博文记录][1]</small>
  Cypress驱动安装，利用github开源库[spdlog][2]可输出安装过程中的信息到文件
### 3 setup_usb2camera_034项目
  整套软件安装项目，利用InstallShield实现，生成setup.exe文件


  [1]: http://blog.csdn.net/zhichitianyago/article/details/53887683?locationNum=1&fps=1
  [2]: https://github.com/gabime/spdlog