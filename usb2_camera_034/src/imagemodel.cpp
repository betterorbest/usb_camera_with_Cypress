#include "imagemodel.h"
#include "imagefifo.h"

ImageModel::ImageModel(QWidget *mainWindow)
	:m_mainWindow(mainWindow)
{
	m_camera.moveToThread(&m_receiveThread);

	m_imageProcess.moveToThread(&m_imageProcessThread);

	connect(&m_receiveThread, SIGNAL(started()), &m_camera, SLOT(receiveData()));
	connect(&m_imageProcessThread, SIGNAL(started()), &m_imageProcess, SLOT(dataToImage()));

	connect(&m_imageProcess, SIGNAL(showImage(QPixmap)), m_mainWindow, SLOT(updateImage(QPixmap)));
	//connect(&m_imageProcess, SIGNAL(showImage(QImage)), m_mainWindow, SLOT(updateImage(QImage)));
	connect(&m_camera, SIGNAL(completeFrameTransmission()), m_mainWindow, SLOT(countReceiveFrames()));
	connect(&m_camera, SIGNAL(deviceStateToBeShown(QString, int)), m_mainWindow, SLOT(showStateOnStatusBar(QString, int)));

	connect(this, &ImageModel::wavelengthChanged, &m_camera, static_cast<void (CyDevice::*)(unsigned short)>(&CyDevice::changeWavelength));
	//connect(&m_camera, SIGNAL(completeFrameTransmission(unsigned char *, bool)), &m_imageProcess, SLOT(dataToImage(unsigned char *, bool)), Qt::DirectConnection);
	//connect(&m_camera, SIGNAL(completeFrameTransmission(unsigned char *, bool)), &m_imageProcess, SLOT(dataToImage(unsigned char *, bool)));

	connect(&m_imageProcess, SIGNAL(referenceWavelengthInfo(unsigned short, int)), m_mainWindow, SLOT(changeReferenceParameter(unsigned short, int)));
	
}

ImageModel::~ImageModel()
{
	if (m_receiveThread.isRunning())
	{

		m_camera.disableReceving();
		m_receiveThread.quit();
		m_receiveThread.wait();

		//m_camera.closeDevice();    device类析构时会判断并delete CyDevice
	}
	if (m_imageProcessThread.isRunning())
	{
		m_imageProcess.disableImageProcess();

		m_imageProcessThread.quit();
		m_imageProcessThread.wait();
	}

	QThreadPool::globalInstance()->waitForDone();
}

void ImageModel::initialize(int width, int height, int pixelWidth, int bufferNum, bool isColor)
{
	m_camera.initialize(width, height, pixelWidth, bufferNum);
	m_imageProcess.initialize(width, height, isColor);
}

void ImageModel::initializeTransfer(int packetNum, int xferQueSize, int timeOut)
{
	m_camera.initializeTransfer(packetNum, xferQueSize, timeOut);
}

bool ImageModel::openUSBCamera()
{
	if (m_camera.openDevice((HANDLE)(m_mainWindow->winId())))
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

void ImageModel::closeUSBCamera()
{
	if (m_receiveThread.isRunning()){
		m_camera.disableReceving();
		m_imageProcess.disableImageProcess();

		m_receiveThread.quit();
		m_receiveThread.wait();
		m_camera.closeDevice();

		m_imageProcessThread.quit();
		m_imageProcessThread.wait();
	}
}

void ImageModel::readData()
{
	if (!m_imageProcessThread.isRunning())
	{
		m_imageProcess.enableImageProcess();
		m_imageProcessThread.start();
	}
	m_camera.enableReceving();
	m_receiveThread.start();
}

void ImageModel::setResolution(int height, int width)
{
	m_camera.setHeight(height);
	m_camera.setWidth(width);
	m_imageProcess.setHeight(height);
	m_imageProcess.setWidth(width);
}

void ImageModel::saveData()
{
	m_imageProcess.enableSaveData();
}

void ImageModel::whetherPausingUSBCamera(bool trueOrFalse)
{
	//m_camera.setPauseFlag(trueOrFalse);
	m_imageProcess.setPauseFlag(trueOrFalse);
}

void ImageModel::changeWidthTo8bitsPerPixel(bool flag)
{
	if (flag)
	{
		m_camera.changeWidthTo8bitsPerPixel();
	}
	else
	{
		m_camera.changeWidthTo16bitsPerPixel();
	}
}

void ImageModel::changeImageToColor(bool flag)
{
	m_imageProcess.setImageColorOrBlack(flag);
}

void ImageModel::changeWavelength(unsigned short wavelen)
{
	//m_camera.changeResolution(width, height, req);
	//可以对切换无法进行的在界面处进行处理
	if (m_camera.isReceving())
	{
		m_camera.disableReceving();
		emit wavelengthChanged(wavelen);
	}
	else
	{
		emit m_camera.deviceStateToBeShown(QStringLiteral("波长切换失败，请等待一段时间重新设置"));
	}
}

void ImageModel::sendSettingCommand(uchar u1, uchar u2, uchar u3, uchar u4)
{
	uchar buf[4] = { u1, u2, u3, u4 };

	m_camera.configRegister(buf, 4);

}

void ImageModel::setSavingPath(QString path)
{
	m_imageProcess.setSavingPath(path);
}

void ImageModel::takeImage()
{
	m_imageProcess.setTakingImageFlag(true);
}

void ImageModel::takeSpectrumImage()
{
	m_imageProcess.setCapturingSpectrumFlag(true);
}

void ImageModel::captureReference(bool flag)
{
	m_imageProcess.setCapturingReferenceFlag(flag);
}

bool ImageModel::openSpectrometer()
{
	return m_camera.openLCTF();
}

bool ImageModel::setWavelength(unsigned short wavelen)
{
	return m_camera.setWavelength(wavelen);
}

void ImageModel::setHorizontalMirror()
{
	m_imageProcess.setHorizontal();
}

void ImageModel::setVerticalMirror()
{
	m_imageProcess.setVertical();
}

QString ImageModel::getSavingPath()
{
	return m_imageProcess.getSavingPath();
}

void ImageModel::setLowIlluminationChecked(bool flag)
{
	m_imageProcess.setLowIlluminationChecked(flag);
}

void ImageModel::setRefBoundary(int low, int high)
{
	m_imageProcess.setRefBoundary(low, high);
}