#include "cydevice.h"
#include "qmessagebox.h"
#include "qdebug.h"

CyDevice::CyDevice()
	:m_device(nullptr),
	m_dataBuffer(nullptr),
	//m_pauseFlag(false),
	m_whichBuffer(0)
{

}

CyDevice::~CyDevice()
{
	if (m_dataBuffer != nullptr)
	{
		for (int i = 0; i < m_bufferNum; ++i)
		{
			if (m_dataBuffer[i] != nullptr)
			{
				delete[] m_dataBuffer[i];
				m_dataBuffer[i] = nullptr;
			}	
		}
		delete[] m_dataBuffer;
		m_dataBuffer = nullptr;
	}
	
	if (m_imageBuffer != nullptr)
	{
		delete m_imageBuffer;
		m_imageBuffer = nullptr;
	}
		
	if (m_device != nullptr)
	{
		delete m_device;
		m_device = nullptr;
	}
		
}

void CyDevice::initialize(int width, int height, int pixelWidth, int bufferNum)
{
	setMaxDataSavingSpace(width, height, bufferNum);
	m_width = width;
	m_height = height;
	m_bitsPerPixel = pixelWidth;
	m_bufferNum = bufferNum;
}


void CyDevice::setMaxDataSavingSpace(int width, int height, int bufferNum)
{
	//TODO 内存分配异常保护代码
	int size = height * width * 2;
	m_dataBuffer = new uchar*[bufferNum];
	ImageFifo::setFifoSize(bufferNum);
	for (int i = 0; i < bufferNum; ++i)
	{
		m_dataBuffer[i] = new uchar[size];
	}

	m_imageBuffer = new ImageData[bufferNum];
}

bool CyDevice::openDevice(HANDLE hnd)
{ 
	if (m_device != nullptr) return false;
	m_device = new CCyUSBDevice(hnd);
	if (!m_device->Open(0))
	{
		delete m_device;
		m_device = nullptr;
		return false;
	}
	
	//m_dataInEndPoint = m_device->BulkInEndPt;
	m_dataInEndPoint = m_device->EndPointOf(0x83);
	m_controlEndPoint = m_device->ControlEndPt;



	sendControlCode(0xb2);    //usb设备初始化

	m_mutex.lock();
	if (m_bitsPerPixel <= 8)
	{
		sendControlCode(0xb8);    //发送8位图像数据
	}
	else
	{
		sendControlCode(0xb9);    //发送12位图像数据
	}
	m_mutex.unlock();
	
	sendControlCode(0xb4);    //清空设备帧缓存

	//m_dataInEndPoint->SetXferSize(m_size);

	m_whichBuffer = 0;
	return true;
}

void CyDevice::closeDevice()
{
	//DWORD x = GetCurrentThreadId();
	if (m_device != nullptr)
	{
		delete m_device;
		m_device = nullptr;
	}
}




void CyDevice::enableReceving()
{
	m_mutex.lock();
	m_recevingFlag = true;
	m_mutex.unlock();
}

void CyDevice::disableReceving()
{
	m_mutex.lock();
	m_recevingFlag = false;
	m_mutex.unlock();
}

bool CyDevice::sendControlCode(int code, int timeOut)
{
	m_controlEndPoint->TimeOut = timeOut;
	m_controlEndPoint->Target = TGT_DEVICE;
	m_controlEndPoint->ReqType = REQ_VENDOR;
	m_controlEndPoint->Direction = DIR_TO_DEVICE;
	m_controlEndPoint->Value = 0;
	m_controlEndPoint->Index = 0;

	UCHAR buf = 0;
	LONG len = 0;
	m_controlEndPoint->ReqCode = code;
	return m_controlEndPoint->XferData(&buf, len);
}

bool CyDevice::sendRequestCode(int code, uchar *buf, LONG bufLen, int timeOut)
{
	QMutexLocker mutexLocker(&m_mutex);
	m_controlEndPoint->TimeOut = timeOut;
	m_controlEndPoint->Target = TGT_DEVICE;
	m_controlEndPoint->ReqType = REQ_VENDOR;
	m_controlEndPoint->Direction = DIR_TO_DEVICE;
	m_controlEndPoint->Value = 0;
	m_controlEndPoint->Index = 0;

	m_controlEndPoint->ReqCode = code;
	return m_controlEndPoint->XferData(buf, bufLen);
}


//void CyDevice::setPauseFlag(bool flag)
//{
//	m_pauseFlag = flag;
//}

void CyDevice::changeWidthTo8bitsPerPixel()
{
	m_mutex.lock();
	sendControlCode(0xb8);
	m_bitsPerPixel = 8;
	m_mutex.unlock();
}

void CyDevice::changeWidthTo16bitsPerPixel()
{
	m_mutex.lock();
	sendControlCode(0xb9);
	m_bitsPerPixel = 12;
	m_mutex.unlock();
}

void CyDevice::changeResolution(int width, int height, int req)
{
	m_mutex.lock();
	if (sendControlCode(req))
	{
		m_width = width;
		m_height = height;
	}
	m_recevingFlag = true;
	m_mutex.unlock();
}

void CyDevice::receiveData()
{
	//初始传输1280 * 960
	//changeResolution(1280, 960, 0xa1);
	//sendControlCode(0xa1);
	//receiveData(m_width * m_height / 10, 10, 200);
	//receiveData(m_width * m_height, 1, 1000);
	//receiveData(1024 * 400, 2, 1500);
	receiveData(m_dataInEndPoint->MaxPktSize * m_packetNum, m_xferQueSize, m_timeOut);
	//receiveData(m_width * m_height / 24, 24, 1000);
	//receiveData(120 * 1024, 10, 50);
	//初始传输640 * 480
	//changeResolution(640, 480, 0xa2);
	//sendControlCode(0xb1);
	//receiveData(76800, 4, 200);
}

void CyDevice::receiveData(LONG sizePerXfer, int xferQueueSize, int timeOut)
{
	//如果MaxPktSize=1024，那么sizePerXfer就是MaxPktSize的倍数，每次接的包数不能太小，也不能太大
	//太小，数据会接不到；太大，数据会来不及接
	//USHORT size = m_dataInEndPoint->MaxPktSize * 2;
	m_dataInEndPoint->SetXferSize(sizePerXfer);
	uchar *data;
	data = m_dataBuffer[m_whichBuffer];

	LONG sizePerDataXfer;
	OVERLAPPED* inOverlaps = new OVERLAPPED[xferQueueSize];
	UCHAR **inContexts = new UCHAR*[xferQueueSize];

	int transfer_count_finished;
	int transfer_count_begun;
	int transfer_count_limit;

	for (int i = 0; i < xferQueueSize; ++i)
	{
		//inOverlaps[i].hEvent = CreateEvent(NULL, false, false, L"CYUSB_IN");   无法接收数据在1024size与2queuesize下, 未知原因
		inOverlaps[i].hEvent = CreateEvent(NULL, false, false, NULL);
	}

	bool currentFrameDropped;
	
	
	while (m_recevingFlag)
	{
		currentFrameDropped = false;
		/**********receive frames in the loop*****************/
		m_mutex.lock();
		m_imageBuffer[m_whichBuffer].m_data = data;
		m_imageBuffer[m_whichBuffer].m_bitsPerPixel = m_bitsPerPixel;
		m_imageBuffer[m_whichBuffer].m_imageHeight = m_height;
		m_imageBuffer[m_whichBuffer].m_imageWidth = m_width;
		m_size = m_bitsPerPixel > 8 ? m_width * m_height * 2 : m_width * m_height;

		//sendControlCode(0xb4);
		sendControlCode(0xb5);

		m_mutex.unlock();

		transfer_count_finished = 0;
		sizePerDataXfer = sizePerXfer;     // FinishDataXfer will modify value of sizePerDataXfer, do the copy
		transfer_count_limit = m_size / sizePerDataXfer;
		if (transfer_count_limit < xferQueueSize)
			xferQueueSize = transfer_count_limit;


		for (int i = 0; i < xferQueueSize; ++i)
		{
			inContexts[i] = m_dataInEndPoint->BeginDataXfer(data + i * sizePerXfer, sizePerDataXfer, &inOverlaps[i]);
			if (m_dataInEndPoint->NtStatus || m_dataInEndPoint->UsbdStatus)      //BeginDataXfer failed
			{
				//TODO 
				//做些BeginDataXfer失败的事
				//BeginDataXfer failed and handle the error
				m_dataInEndPoint->Abort();
				for (int j = 0; j < xferQueueSize; ++j)
				{
					CloseHandle(inOverlaps[j].hEvent);
				}
				qDebug() << "BeginDataXfer failed!";
				delete[] inOverlaps;
				delete[] inContexts;
				inOverlaps = nullptr;
				inContexts = nullptr;

				return;
				
			}
		}

		transfer_count_begun = xferQueueSize;

		int i = 0;

		/*******receive a frame in the loop***********/
		while (true)
		{
			if (!m_dataInEndPoint->WaitForXfer(&inOverlaps[i], timeOut))
			{
				m_dataInEndPoint->Abort();
				if (m_dataInEndPoint->LastError == ERROR_IO_PENDING)
					WaitForSingleObject(inOverlaps[i].hEvent, timeOut);

				currentFrameDropped = true;
				//TODO
				qDebug() << "WaitForXfer failed!" << ", finished num is:" << transfer_count_finished <<",  begun number is:" << transfer_count_begun;
				//break;
			}

			if (!m_dataInEndPoint->FinishDataXfer(data + transfer_count_finished * sizePerXfer, sizePerDataXfer, &inOverlaps[i], inContexts[i]))
			{
				//TODO
				currentFrameDropped = true;
				qDebug() << "FinishDataXfer failed!";
				//break;
			}

			//qDebug() << "xfer succeed" << transfer_count_finished << "  " << transfer_count_begun;
			++transfer_count_finished;

			sizePerDataXfer = sizePerXfer;

			if (!currentFrameDropped && transfer_count_begun < transfer_count_limit)
			{

				inContexts[i] = m_dataInEndPoint->BeginDataXfer(data + transfer_count_begun * sizePerXfer, sizePerDataXfer, &inOverlaps[i]);
				if (m_dataInEndPoint->NtStatus || m_dataInEndPoint->UsbdStatus)      //BeginDataXfer failed
				{
					//TODO 
					//做些BeginDataXfer失败的事
					//BeginDataXfer failed and handle the error
					m_dataInEndPoint->Abort();
					for (int j = 0; j < xferQueueSize; ++j)
					{
						CloseHandle(inOverlaps[j].hEvent);
					}
					delete[] inOverlaps;
					delete[] inContexts;
					inOverlaps = nullptr;
					inContexts = nullptr;

					qDebug() << "BeginDataXfer in loop failed!";
					return;
					//TODO 
					//做些BeginDataXfer失败的事
				}

				++transfer_count_begun;
			}

			++i;

			if (i == xferQueueSize)
				i = 0;
				

			if (currentFrameDropped && transfer_count_finished == transfer_count_begun)
				break;

			if (!currentFrameDropped && transfer_count_finished == transfer_count_limit)
			{
				//emit completeFrameTransmission();
				//if (!m_pauseFlag)
				//{
				if (ImageFifo::inFifo(&m_imageBuffer[m_whichBuffer]))
				{
					++m_whichBuffer;
					if (m_whichBuffer == m_bufferNum)
						m_whichBuffer = 0;
					data = m_dataBuffer[m_whichBuffer];
				}
				//}

				break;
			}

		}

	}

	m_dataInEndPoint->Abort();
	for (int i = 0; i < xferQueueSize; ++i)
	{
		CloseHandle(inOverlaps[i].hEvent);
	}

	delete[] inOverlaps;
	delete[] inContexts;
	inOverlaps = nullptr;
	inContexts = nullptr;
}

void CyDevice::changeResolution(int width, int height, int req, long sizePerXfer, int xferQueueSize, int timeOut)
{
	changeResolution(width, height, req);
	receiveData(sizePerXfer, xferQueueSize, timeOut);
}

bool CyDevice::isReceving()
{
	QMutexLocker locker(&m_mutex);
	return m_recevingFlag;
}

bool CyDevice::configRegister(uchar* buf, int len)
{
	return sendRequestCode(0xb3, buf, len);
}