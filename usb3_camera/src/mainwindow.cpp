#include "mainwindow.h"
#include "qsettings.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_imageModel(this, 960, 1280),
	m_frameCount(0),
	m_receiveFramesCount(0),
	m_isClosed(false)
{
	if (!initCameraConfig())
	{
		m_imageHeight = 960;
		m_imageWidth = 1280;
	}

	m_imageModel.setResolution(m_imageHeight, m_imageWidth);

 	ui.setupUi(this);
	ui.m_showLabel->setFixedSize(QSize(m_imageWidth, m_imageHeight));
		
	m_frameRateLabel = new QLabel(ui.statusBar);
	ui.statusBar->addWidget(m_frameRateLabel);
	m_frameRateLabel->setText(QStringLiteral("就绪"));

	//Qt4的信号槽使用方式
	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
	connect(ui.m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseCamera()));

	connect(ui.m_8bitsChoosed, SIGNAL(toggled(bool)), this, SLOT(changeWidthTo8bitsPerPixel(bool)));
	connect(ui.m_colorImageChoosed, SIGNAL(toggled(bool)), this, SLOT(changeImageToColor(bool)));
	

	//Qt5的重载信号与槽连接的使用方式
	connect(ui.m_resolutionSwitching, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::switchResolution);
	
	connect(ui.m_analogGainSet, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::setAnalogGain);
	
	connect(ui.m_rGainSet, &QSlider::valueChanged, this, &MainWindow::setRedGain);
	connect(ui.m_gGainSet, &QSlider::valueChanged, this, &MainWindow::setGreenGain);
	connect(ui.m_bGainSet, &QSlider::valueChanged, this, &MainWindow::setBlueGain);
	connect(ui.m_globalGainSet, &QSlider::valueChanged, this, &MainWindow::setGlobalGain);

	connect(ui.m_autoExposure, &QRadioButton::toggled, this, &MainWindow::setExposureMode);
	connect(ui.m_exposureSlider, &QSlider::valueChanged, this, &MainWindow::setExposureValue);
	connect(ui.m_exposureSlider, &QSlider::valueChanged, ui.m_exposureSpinBox, &QSpinBox::setValue);
	connect(ui.m_exposureSpinBox, static_cast<void (QSpinBox:: *)(int)>(&QSpinBox::valueChanged), ui.m_exposureSlider, &QSlider::setValue);
	
	connect(ui.m_pathChoosingButton, &QPushButton::clicked, this, &MainWindow::chooseSavingPath);
	connect(ui.m_imageTakingButton, &QPushButton::clicked, this, &MainWindow::takeImage);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(showFrameRate()));
	
}

MainWindow::~MainWindow()
{
	//m_imageModel.closeUSBCamera();
}

void MainWindow::openCamera()
{
	//qDebug() << "i have in ";
	if (m_imageModel.openUSBCamera())
	{
		ui.m_startButton->setEnabled(false);
		ui.m_pauseButton->setEnabled(true);
		ui.m_stopButton->setEnabled(true);
		
		m_isClosed = false;
		m_imageModel.readData();
		m_frameCount = 0;
		m_timer.start(1000);

		ui.m_bitsPerPixelChange->setEnabled(true);
		ui.m_resolutionSwitching->setEnabled(true);
		ui.m_imageTakingButton->setEnabled(true);
		ui.m_analogGainSet->setEnabled(true);
		ui.m_digitalGainSet->setEnabled(true);
		ui.m_exposureMode->setEnabled(true);
	}
	else
	{
		QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("设备打开失败，请重新连接"));
	}
}

void MainWindow::closeCamera()
{
	//qDebug() << "i out";

	ui.m_stopButton->setEnabled(false);
	ui.m_pauseButton->setEnabled(false);
	ui.m_bitsPerPixelChange->setEnabled(false);
	ui.m_resolutionSwitching->setEnabled(false);
	ui.m_imageTakingButton->setEnabled(false);
	ui.m_analogGainSet->setEnabled(false);
	ui.m_digitalGainSet->setEnabled(false);
	ui.m_exposureMode->setEnabled(false);

	m_imageModel.closeUSBCamera();
	m_timer.stop();

	if (ui.m_pauseButton->text() != "暂停")
	{
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		m_imageModel.whetherPausingUSBCamera(false);
	}

	m_frameRateLabel->setText(QStringLiteral("就绪"));
	ui.m_startButton->setEnabled(true);
	m_frameCount = 0;
	m_receiveFramesCount = 0;
	m_isClosed = true;
	ui.m_showLabel->clear();
	ui.m_receiveRateLabel->setText(QString::number(0));
}

void MainWindow::updateImage(QPixmap image)
{
	if (m_isClosed)
		return;
	//qDebug() << "updateImage";
	//ui.m_showLabel->resize(image.size());
	
	//ui.m_showLabel->clear();
	ui.m_showLabel->setPixmap(image);
	//DWORD start1 = GetTickCount();
	++m_frameCount;

	/*DWORD end1 = GetTickCount();
	qDebug() << end1 - start1;*/
}

void MainWindow::showFrameRate()
{
	QString frameRate = QString::number(m_frameCount);
	QString receiveFrameRate = QString::number(m_receiveFramesCount);
	m_frameRateLabel->setText(receiveFrameRate + "fps");
	ui.m_receiveRateLabel->setText(frameRate);
	m_frameCount = 0;
	m_receiveFramesCount = 0;
}


void MainWindow::saveData()
{
	m_imageModel.saveData();
}

void MainWindow::countReceiveFrames()
{
	++m_receiveFramesCount;
}

void MainWindow::pauseCamera()
{
	if (ui.m_pauseButton->text() == QStringLiteral("暂停"))
	{
		ui.m_imageTakingButton->setEnabled(false);
		m_imageModel.whetherPausingUSBCamera(true);
		ui.m_pauseButton->setText(QStringLiteral("取消暂停"));
	}
	else
	{
		m_imageModel.whetherPausingUSBCamera(false);
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		ui.m_imageTakingButton->setEnabled(true);
	}
}

void MainWindow::changeWidthTo8bitsPerPixel(bool flag)
{
	m_imageModel.changeWidthTo8bitsPerPixel(flag);
	//qDebug() << "in change";
}

void MainWindow::changeImageToColor(bool flag)
{
	m_imageModel.changeImageToColor(flag);
}

void MainWindow::switchResolution(int index)
{
	ui.m_resolutionSwitching->setEnabled(false);
	switch (index)
	{
	case 0:// 320 * 240
		m_imageModel.changeResolution(320, 240, 0xb1, 320 * 240, 1, 200);
		ui.m_showLabel->setFixedSize(320, 240);
		break;
	case 1:// 640 * 480
		m_imageModel.changeResolution(640, 480, 0xa2, 320 * 240, 4, 200);
		ui.m_showLabel->setFixedSize(640, 480);
		break;
	case 2:// 1280 * 960
		m_imageModel.changeResolution(1280, 960, 0xa1, 120 * 1024, 10, 50);
		ui.m_showLabel->setFixedSize(1280, 960);
		break;
	default:
		break;
	}
	ui.m_resolutionSwitching->setEnabled(true);
}

bool MainWindow::initCameraConfig()
{
	QSettings settings("camconfig.ini", QSettings::IniFormat);

	m_imageWidth = settings.value("Camera034/width").toInt();
	m_imageHeight = settings.value("Camera034/height").toInt();

	if (m_imageHeight == 0 || m_imageWidth == 0)
		return false;
	else
		return true;
}

void MainWindow::setAnalogGain(int index)
{
	switch (index)
	{
	case 0://1倍增益
		m_imageModel.sendSettingCommand(0x3E, 0xE4, 0xD2, 0x08);
		m_imageModel.sendSettingCommand(0x30, 0xB0, 0x00, 0x00);
		break;
	case 1://2倍增益
		m_imageModel.sendSettingCommand(0x3E, 0xE4, 0xD2, 0x08);
		m_imageModel.sendSettingCommand(0x30, 0xB0, 0x00, 0x10);
		break;
	case 2://4倍增益
		m_imageModel.sendSettingCommand(0x3E, 0xE4, 0xD2, 0x08);
		m_imageModel.sendSettingCommand(0x30, 0xB0, 0x00, 0x20);
		break;
	case 3://8倍增益
		m_imageModel.sendSettingCommand(0x3E, 0xE4, 0xD2, 0x08);
		m_imageModel.sendSettingCommand(0x30, 0xB0, 0x00, 0x30);
		break;
	case 4://10倍增益
		m_imageModel.sendSettingCommand(0x3E, 0xE4, 0xD3, 0x08);
		m_imageModel.sendSettingCommand(0x30, 0xB0, 0x00, 0x30);
		break;
	default:
		break;
	}
}

void MainWindow::setRedGain(int gain)
{
	ui.m_rGain->setText(QString::number(gain));
	uchar u4;
	if (gain != 8)
		u4 = gain << 5;
	else
		u4 = 255;

	m_imageModel.sendSettingCommand(0x30, 0x5C, 0x00, u4);
}

void MainWindow::setGreenGain(int gain)
{
	ui.m_gGain->setText(QString::number(gain));
	uchar u4;
	if (gain != 8)
		u4 = gain << 5;
	else
		u4 = 255;

	m_imageModel.sendSettingCommand(0x30, 0x58, 0x00, u4);
	m_imageModel.sendSettingCommand(0x30, 0x5A, 0x00, u4);
}

void MainWindow::setBlueGain(int gain)
{
	ui.m_bGain->setText(QString::number(gain));
	uchar u4;
	if (gain != 8)
		u4 = gain << 5;
	else
		u4 = 255;

	m_imageModel.sendSettingCommand(0x30, 0x56, 0x00, u4);
}

void MainWindow::setGlobalGain(int gain)
{
	ui.m_globalGain->setText(QString::number(gain));
	uchar u4;
	if (gain != 8)
		u4 = gain << 5;
	else
		u4 = 255;

	m_imageModel.sendSettingCommand(0x30, 0x5E, 0x00, u4);
}

void MainWindow::setExposureMode(bool isAuto)
{
	if (isAuto)
	{
		ui.m_exposureSlider->setEnabled(false);
		ui.m_exposureSpinBox->setEnabled(false);
		m_imageModel.sendSettingCommand(0x31, 0x00, 0x00, 0x1B);
	}
	else
	{
		m_imageModel.sendSettingCommand(0x31, 0x00, 0x00, 0x1A);
		ui.m_exposureSlider->setEnabled(true);
		ui.m_exposureSpinBox->setEnabled(true);
	}
}

void MainWindow::setExposureValue(int value)
{
	qDebug() << value;
	uchar u3;
	uchar u4;

	u3 = (value * 80 / 11) >> 8;
	u4 = (value * 80 / 11);

	m_imageModel.sendSettingCommand(0x30, 0x12, u3, u4);
}

void MainWindow::chooseSavingPath()
{
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("存储路径选择"), ".");
	if (path == "")
		path = ".";
	m_imageModel.setSavingPath(path);
}

void MainWindow::takeImage()
{
	m_imageModel.takeImage();
}
