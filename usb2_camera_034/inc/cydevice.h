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
	CyDevice();
	~CyDevice();
	void initialize(int width, int height, int pixelWidth, int bufferNum);
	void setMaxDataSavingSpace(int width, int height, int bufferNum);
	void initializeTransfer(int packetNum, int xferQueSize, int timeOut);

	bool openDevice(HANDLE hnd);
	void closeDevice();
	
	void enableReceving();
	void disableReceving();
	
	bool sendControlCode(int code, int timeOut=100);
	bool sendRequestCode(int code, uchar *buf, LONG bufLen, int timeOut=100);

	void setWidth(int width);
	void setHeight(int height);

	//void setPauseFlag(bool flag);

	void changeWidthTo8bitsPerPixel();
	void changeWidthTo16bitsPerPixel();

	void receiveData(LONG sizePerXfer, int xferQueueSize, int timeOut, int wavelen=0);

	bool isReceving();

	bool configRegister(uchar* buf, int len);

signals:
	//void completeFrameTransmission(unsigned char *data);
	void completeFrameTransmission();
	void deviceStateToBeShown(QString state, int timeOut = 0);

public slots:
	void receiveData();
	void changeWavelength(unsigned short wavelen);

private:
	int m_whichBuffer;
	int m_height;
	int m_width;
	LONG m_size;
	UCHAR **m_dataBuffer;
	ImageData *m_imageBuffer;
	int m_bufferNum;
	bool m_recevingFlag;
	//bool m_pauseFlag;
	int m_bitsPerPixel;
	bool m_widthPerPixelChanged;

	QMutex m_mutex;

	CCyUSBDevice *m_device;
	CCyUSBEndPoint *m_dataInEndPoint;
	CCyControlEndPoint *m_controlEndPoint;

	//初始化时传输参数
	int m_packetNum;
	int m_xferQueSize;
	int m_timeOut;

/*************LCTF代码部分，不采用继承*******************/
public:
	bool openLCTF();
	bool setWavelength(unsigned short wavelen);

};


inline void CyDevice::setWidth(int width)
{
	m_width = width;
}

inline void CyDevice::setHeight(int height)
{
	m_height = height;
}

inline void CyDevice::initializeTransfer(int packetNum, int xferQueSize, int timeOut)
{
	m_packetNum = packetNum;
	m_xferQueSize = xferQueSize;
	m_timeOut = timeOut;
}


#endif