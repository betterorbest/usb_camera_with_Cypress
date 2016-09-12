#ifndef CYDEVICE_H
#define CYDEVICE_H

#include <Windows.h>
#include <QtCore>
#include "CyAPI.h"
#include "imagefifo.h"

class CyDevice: public QObject
{
	Q_OBJECT

public:
	CyDevice(int height, int width);
	~CyDevice();

	bool openDevice(HANDLE hnd);
	void closeDevice();
	void setDataSavingSpace(UCHAR **data, int size);
	void enableReceving();
	void disableReceving();
	
	bool sendControlCode(int code);

	void setWidth(int width);
	void setHeight(int height);

	//void setPauseFlag(bool flag);

	void changeWidthTo8bitsPerPixel();
	void changeWidthTo16bitsPerPixel();
signals:
	//void completeFrameTransmission(unsigned char *data);
	void completeFrameTransmission();

public slots:
	void receiveData();


private:
	int m_height;
	int m_width;
	LONG m_size;
	UCHAR **m_dataBuffer;
	ImageData *m_imageBuffer;
	int m_bufferSize;
	bool m_recevingFlag;
	//bool m_pauseFlag;
	bool m_is8bitsPerPixel;
	bool m_widthPerPixelChanged;

	QMutex mutex;

	CCyUSBDevice *m_device;
	CCyUSBEndPoint *m_dataInEndPoint;
	CCyControlEndPoint *m_controlEndPoint;

	



};


#endif