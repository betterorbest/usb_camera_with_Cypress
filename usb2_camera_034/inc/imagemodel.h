#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "cydevice.h"
#include "imageprocess.h"
#include <QtWidgets>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
class ImageModel: public QObject
{
	Q_OBJECT

public:
	ImageModel(QWidget *mainWindow);
	~ImageModel();
	void initialize(int width, int height, int pixelWidth, int bufferNum, bool isColor);
	void initializeTransfer(int packetNum, int xferQueSize, int timeOut);
	void initializeDual(int visibleWidth, int visibleHeight, int infraWidth, int infraHeight, bool isColor, ImageProcess::InfraredColor infraColor);

	bool openUSBCamera();
	void closeUSBCamera();
	void readData();

	void setResolution(int height, int width);
	void saveData();

	void whetherPausingUSBCamera(bool flag);

	void changeWidthTo8bitsPerPixel(bool flag);
	void changeImageToColor(bool flag);
	void changeResolution(int width, int height, int req);
	void changeResolution(int width, int height, int req, long sizePerXfer, int xferQueueSize, int timeOut);
	
	void sendSettingCommand(uchar u1, uchar u2, uchar u3, uchar u4);

	void setSavingPath(QString path);
	void takeImage();

	void setInfraredColor(ImageProcess::InfraredColor color);
signals:
	void resolutionChanged(int width, int height, int req, long sizePerXfer, int xferQueueSize, int timeOut);

private:
	CyDevice m_camera;
	ImageProcess m_imageProcess;
	QWidget *m_mainWindow;
	int m_imageHeight;
	int m_imageWidth;

	QThread m_receiveThread;
	QThread m_imageProcessThread;




	
};

#endif