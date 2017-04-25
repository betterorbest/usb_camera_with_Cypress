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

	bool openUSBCamera();
	void closeUSBCamera();
	void readData();

	void setResolution(int height, int width);
	void saveData();

	void whetherPausingUSBCamera(bool flag);

	void changeWidthTo8bitsPerPixel(bool flag);
	void changeImageToColor(bool flag);

	void changeWavelength(unsigned short wavelen);
	
	void sendSettingCommand(uchar u1, uchar u2, uchar u3, uchar u4);

	void setSavingPath(QString path);
	QString getSavingPath();
	void takeImage();
	void takeSpectrumImage();

	void setHorizontalMirror();
	void setVerticalMirror();
signals:
	void wavelengthChanged(unsigned short wavelen);

private:
	CyDevice m_camera;
	ImageProcess m_imageProcess;
	QWidget *m_mainWindow;
	int m_imageHeight;
	int m_imageWidth;

	QThread m_receiveThread;
	QThread m_imageProcessThread;



public:
	bool openSpectrometer();
	bool setWavelength(unsigned short wavelen);

	void setLowIlluminationChecked(bool flag);


	
};

#endif