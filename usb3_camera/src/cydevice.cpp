#include "cydevice.h"
#include "qmessagebox.h"
#include "qdebug.h"

#define     PACKETS_PER_TRANSFER				2400                      //1020: 100      034: 120 
#define		PACKETS_SIZE						1024
#define     NUM_TRANSFER_PER_TRANSACTION        1                         //1020: 9       034: 10
#define     TIMEOUT_MILLI_SEC_PER_TRANSFER      50


CyDevice::CyDevice(int height, int width)
	:m_height(height),
	m_width(width),
	m_device(nullptr),
	//m_pauseFlag(false),
	m_is8bitsPerPixel(false)
{
	m_size = m_height * m_width * 2; 
}

CyDevice::~CyDevice()
{
	delete m_imageBuffer;
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
	m_dataInEndPoint = m_device->BulkInEndPt;
	//m_dataInEndPoint = m_device->EndPointOf(0x82);
	m_controlEndPoint = m_device->ControlEndPt;



	sendControlCode(0xb2);    //usb设备初始化

	//mutex.lock();
	//if (m_is8bitsPerPixel)
	//{
	//	sendControlCode(0xb8);    //发送8位图像数据
	//}
	//else
	//{
	//	sendControlCode(0xb9);    //发送8位图像数据
	//}
	//mutex.unlock();
	
	sendControlCode(0xb4);    //清空设备帧缓存

	//m_dataInEndPoint->SetXferSize(m_size);
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

void CyDevice::setDataSavingSpace(UCHAR **data, int size)
{
	m_dataBuffer = data;
	m_bufferSize = size;

	m_imageBuffer = new ImageData[size];
}


void CyDevice::enableReceving()
{
	m_recevingFlag = true;
}

void CyDevice::disableReceving()
{
	m_recevingFlag = false;
}

bool CyDevice::sendControlCode(int code)
{
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

void CyDevice::setWidth(int width)
{
	m_width = width;
}

void CyDevice::setHeight(int height)
{
	m_height = height;
}

//void CyDevice::setPauseFlag(bool flag)
//{
//	m_pauseFlag = flag;
//}

void CyDevice::changeWidthTo8bitsPerPixel()
{
	mutex.lock();
	sendControlCode(0xb8);
	m_is8bitsPerPixel = true;
	mutex.unlock();
}

void CyDevice::changeWidthTo16bitsPerPixel()
{
	mutex.lock();
	sendControlCode(0xb9);
	m_is8bitsPerPixel = false;
	mutex.unlock();
}

void CyDevice::receiveData()
{
	uchar *data;

	//bool flag;

	int count = 0;

	LONG size = m_size;

	int whichBuffer = 0;
	data = m_dataBuffer[whichBuffer];

	LONG sizePerXfer = PACKETS_SIZE * PACKETS_PER_TRANSFER;
	LONG sizePerDataXfer;
	OVERLAPPED inOverlaps[NUM_TRANSFER_PER_TRANSACTION];
	UCHAR *inContexts[NUM_TRANSFER_PER_TRANSACTION];
	int transfer_count;
	int transfer_queue_count;
	int transfer_count_limit;


	//m_dataInEndPoint->SetXferSize(PACKETS_SIZE * PACKETS_PER_TRANSFER);

	for (int i = 0; i < NUM_TRANSFER_PER_TRANSACTION; ++i)
	{
		inOverlaps[i].hEvent = CreateEvent(NULL, false, false, L"CYUSB_IN");
	}


	while (m_recevingFlag)
	{
		bool is8bitsPerPixel;
		/**********receive frames in the loop*****************/
		mutex.lock();
		if (m_is8bitsPerPixel)
		{
			m_size = m_height * m_width;
			m_imageBuffer[whichBuffer].m_data = data;
			m_imageBuffer[whichBuffer].m_bytesPerPixel = 1;
			m_imageBuffer[whichBuffer].m_imageHeight = m_height;
			m_imageBuffer[whichBuffer].m_imageWidth = m_width;
		}
		else
		{
			m_size = m_height * m_width * 2;
			m_imageBuffer[whichBuffer].m_data = data;
			m_imageBuffer[whichBuffer].m_bytesPerPixel = 2;
			m_imageBuffer[whichBuffer].m_imageHeight = m_height;
			m_imageBuffer[whichBuffer].m_imageWidth = m_width;
		}

		//sendControlCode(0xb4);
		sendControlCode(0xb5);

		mutex.unlock();

		transfer_count = 0;
		sizePerDataXfer = sizePerXfer;     // FinishDataXfer will modify value of sizePerDataXfer, do the copy
		transfer_count_limit = m_size / sizePerDataXfer;



		for (int i = 0; i < NUM_TRANSFER_PER_TRANSACTION; ++i)
		{
			inContexts[i] = m_dataInEndPoint->BeginDataXfer(data + i * sizePerDataXfer, sizePerDataXfer, &inOverlaps[i]);
			if (m_dataInEndPoint->NtStatus || m_dataInEndPoint->UsbdStatus)      //BeginDataXfer failed
			{
				qDebug() << "BeginDataXfer failed!";
				return;
				//TODO 
				//做些BeginDataXfer失败的事
			}
		}

		transfer_queue_count = NUM_TRANSFER_PER_TRANSACTION;

		int i = 0;

		/*******receive a frame in the loop***********/
		while (true)
		{
			LONG sizePerXfer = sizePerDataXfer;

			if (!m_dataInEndPoint->WaitForXfer(&inOverlaps[i], TIMEOUT_MILLI_SEC_PER_TRANSFER))
			{
				m_dataInEndPoint->Abort();
				/*if (m_dataInEndPoint->LastError == ERROR_IO_PENDING)
				WaitForSingleObject(inOverlaps[i].hEvent, 2000);*/

				//TODO
				qDebug() << "WaitForXfer failed!" << i << "  " << transfer_count;
				break;
			}

			if (!m_dataInEndPoint->FinishDataXfer(data + transfer_count * sizePerDataXfer, sizePerDataXfer, &inOverlaps[i], inContexts[i]))
			{
				//TODO
				qDebug() << "FinishDataXfer failed!";
				break;
			}

			//qDebug() << "xfer succeed" << transfer_count << "  " << transfer_queue_count;
			++transfer_count;

			if (transfer_queue_count < transfer_count_limit)
			{

				inContexts[i] = m_dataInEndPoint->BeginDataXfer(data + transfer_queue_count * sizePerDataXfer, sizePerDataXfer, &inOverlaps[i]);
				if (m_dataInEndPoint->NtStatus || m_dataInEndPoint->UsbdStatus)      //BeginDataXfer failed
				{
					qDebug() << "BeginDataXfer in loop failed!";
					return;
					//TODO 
					//做些BeginDataXfer失败的事
				}


				++transfer_queue_count;
			}

			++i;

			if (i == NUM_TRANSFER_PER_TRANSACTION)
				i = 0;

			if (transfer_count == transfer_count_limit)
			{
				emit completeFrameTransmission();
				//if (!m_pauseFlag)
				//{
				if (ImageFifo::inFifo(&m_imageBuffer[whichBuffer]))
				{
					++whichBuffer;
					if (whichBuffer == m_bufferSize)
						whichBuffer = 0;
					data = m_dataBuffer[whichBuffer];
				}
				//}

				break;
			}

		}

	}

	for (int i = 0; i < NUM_TRANSFER_PER_TRANSACTION; ++i)
	{
		CloseHandle(inOverlaps[i].hEvent);
	}

}