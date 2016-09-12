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
	ImageModel(QWidget *mainWindow, int height, int width);
	~ImageModel();
	
	bool openUSBCamera();
	void closeUSBCamera();
	void readData();

	void setResolution(int height, int width);
	void saveData();

	void whetherPausingUSBCamera(bool flag);

	void changeWidthTo8bitsPerPixel(bool flag);
	void changeImageToColor(bool flag);
	
	void initialImageFifo();
private:
	CyDevice m_camera;
	ImageProcess m_imageProcess;
	QWidget *m_mainWindow;
	int m_imageHeight;
	int m_imageWidth;

	QThread m_receiveThread;
	QThread m_imageProcessThread;

	uchar** m_imageDataSavingSpace;



	
};

#endif