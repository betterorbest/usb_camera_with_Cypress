1、添加图像数据存储fifo
2、数据接收改为多个BeginDataXfer/WaitForXfer/FinishDataXfer
3、增加图像数据的属性类，以解耦图像处理与图像接收部分，图像处理类从图像fifo中取出图像数据类，通过该图像数据类判断取出的图像像素位宽
4、添加从相机配置文件中读取图像宽和高


the second commit：
1、更改界面（开始使用QSS样式表）
2、添加曝光、增益等功能
3、更改部分代码结构，如将BeginDataXfer的传输size与队列size变为可变的