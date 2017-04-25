#include "mainwindow.h"
#include "qsettings.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_imageModel(this),
	m_frameCount(0),
	m_receiveFramesCount(0),
	m_isClosed(false),
	m_isCapturingSpectrum(false)
{
 	ui.setupUi(this);

	initCameraConfig();

	
	ui.statusBar->showMessage(QStringLiteral("就绪"));
	//m_statusBarLabel = new QLabel(ui.statusBar);
	//ui.statusBar->addWidget(m_statusBarLabel);
	//m_statusBarLabel->setText(QStringLiteral("就绪"));

	//Qt4的信号槽使用方式
	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
	connect(ui.m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseCamera()));

	//Qt5的重载信号与槽连接的使用方式
	
	connect(ui.m_analogGainSet, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::setAnalogGain);
	connect(ui.m_digitalGainSet, static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::setDigitalGain);

	connect(ui.m_autoExposure, &QRadioButton::toggled, this, &MainWindow::setExposureMode);
	connect(ui.m_exposureSlider, &QSlider::valueChanged, this, &MainWindow::setExposureValue);
	connect(ui.m_exposureSlider, &QSlider::valueChanged, ui.m_exposureSpinBox, &QSpinBox::setValue);
	//connect(ui.m_exposureSpinBox, static_cast<void (QSpinBox:: *)(int)>(&QSpinBox::valueChanged), ui.m_exposureSlider, &QSlider::setValue);
	
	connect(ui.m_pathChoosingButton, &QPushButton::clicked, this, &MainWindow::chooseSavingPath);
	connect(ui.m_imageTakingButton, &QPushButton::clicked, this, &MainWindow::takeImage);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(showFrameRate()));
	
	connect(ui.m_wavelengthSlider, &QSlider::valueChanged, this, &MainWindow::changeWavelength);
	connect(ui.m_wavelengthSlider, &QSlider::valueChanged, ui.m_wavelengthSpinBox, &QSpinBox::setValue);
	//connect(ui.m_wavelengthSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), ui.m_wavelengthSlider, &QSlider::setValue);

	connect(ui.m_openSpectrometerButton, &QPushButton::clicked, this, &MainWindow::openSpectrometer);

	connect(ui.m_captureSpectrum, &QPushButton::clicked, this, &MainWindow::captureSpectrumImg);

	connect(ui.m_horizontalMirror, &QPushButton::clicked, this, &MainWindow::setHorizontalMirror);
	connect(ui.m_verticalMirror, &QPushButton::clicked, this, &MainWindow::setVerticalMirror);
	connect(ui.m_lowIlluminationCheck, &QCheckBox::stateChanged, this, &MainWindow::setIlluminationState);
}

MainWindow::~MainWindow()
{
	//m_imageModel.closeUSBCamera();
}

void MainWindow::initCameraConfig()
{
	//TODO 配置信息设置
	//[Spectrometer]
	//width = 1280
	//height = 960
	//initwavelen = 420
	//minwavelen = 420
	//maxwavelen = 720
	//stepofwavelen = 10
	//pixBitswidth = 12
	//iscolor = false

	QSettings settings("camconfig.ini", QSettings::IniFormat);
	m_imageWidth = settings.value("Spectrometer/width").toInt();
	m_imageHeight = settings.value("Spectrometer/height").toInt();
	m_curWavelength = settings.value("Spectrometer/initwavelen").toInt();
	m_sliderMinWavelength = settings.value("Spectrometer/minwavelen").toInt();
	m_sliderMaxWavelength = settings.value("Spectrometer/maxwavelen").toInt();
	unsigned short stepOfWavelenth = settings.value("Spectrometer/stepofwavelen").toInt();
	m_bitsPerPixel = settings.value("Spectrometer/pixbitswidth").toInt();
	m_isColor = settings.value("Spectrometer/iscolor").toBool();
	int bufferNum = settings.value("Transfer/buffernum").toInt();
	int packetNum = settings.value("Transfer/packetnum").toInt();
	int xferQueSize = settings.value("Transfer/xferquesize").toInt();
	int timeOut = settings.value("Transfer/timeout").toInt();

	if (m_imageWidth == 0 || m_imageHeight == 0)
	{
		m_imageWidth = 1280;
		m_imageHeight = 960;
	}

	if (m_curWavelength == 0)
		m_curWavelength = 420;
	if (m_sliderMinWavelength == 0)
		m_sliderMinWavelength = 420;
	if (m_sliderMaxWavelength == 0)
		m_sliderMaxWavelength = 720;
	if (stepOfWavelenth == 0)
		stepOfWavelenth = 10;

	if (m_bitsPerPixel <= 0)
		m_bitsPerPixel = 12;

	if (bufferNum <= 0)
		bufferNum = 2;

	if (packetNum <= 0)
		packetNum = 200;

	if (xferQueSize <= 0)
		xferQueSize = 2;

	if (timeOut <= 0)
		timeOut = 1000;

	m_imageModel.initialize(m_imageWidth, m_imageHeight, m_bitsPerPixel, bufferNum, m_isColor);
	m_imageModel.initializeTransfer(packetNum, xferQueSize, timeOut);

	ui.m_showFrame->setFixedSize(QSize(m_imageWidth / 2, m_imageHeight / 2));
	ui.m_showLabel->setFixedSize(QSize(m_imageWidth / 2, m_imageHeight / 2));

	ui.m_wavelengthSlider->setMinimum(m_sliderMinWavelength);
	ui.m_wavelengthSlider->setMaximum(m_sliderMaxWavelength);
	ui.m_wavelengthSlider->setValue(m_curWavelength);
	ui.m_wavelengthSlider->setSingleStep(stepOfWavelenth);

	ui.m_wavelengthSpinBox->setMinimum(m_sliderMinWavelength);
	ui.m_wavelengthSpinBox->setMaximum(m_sliderMaxWavelength);
	ui.m_wavelengthSpinBox->setValue(m_curWavelength);
	ui.m_wavelengthSpinBox->setSingleStep(stepOfWavelenth);

	ui.m_capMinWavelen->setMinimum(m_sliderMinWavelength);
	ui.m_capMinWavelen->setMaximum(m_sliderMaxWavelength);
	ui.m_capMinWavelen->setValue(m_sliderMinWavelength);
	ui.m_capMaxWavelen->setMinimum(m_sliderMinWavelength);
	ui.m_capMaxWavelen->setMaximum(m_sliderMaxWavelength);
	ui.m_capMaxWavelen->setValue(m_sliderMaxWavelength);
	ui.m_stepOfWavelen->setValue(stepOfWavelenth);

	ui.m_rangeOfWavelen->setText(QString::number(m_sliderMinWavelength) + "-" + QString::number(m_sliderMaxWavelength));

	//ui.m_showLabel->installEventFilter(this);
}

void MainWindow::openCamera()
{
	//qDebug() << "i have in ";
	if (m_imageModel.openUSBCamera())
	{

		//相机配置初始化
		setAnalogGain(ui.m_analogGainSet->currentIndex());
		setDigitalGain(ui.m_digitalGainSet->currentIndex());
		if (ui.m_autoExposure->isChecked())
		{
			setExposureMode(true);
		}
		else
		{
			setExposureMode(false);
			setExposureValue(ui.m_exposureSlider->value());
		}



		ui.m_startButton->setEnabled(false);
		ui.m_pauseButton->setEnabled(true);
		ui.m_stopButton->setEnabled(true);
		
		m_isClosed = false;
		m_imageModel.readData();
		m_frameCount = 0;
		m_timer.start(1000);

		ui.m_imageTakingButton->setEnabled(true);
		ui.m_analogGainSet->setEnabled(true);
		ui.m_digitalGainSet->setEnabled(true);
		ui.m_exposureMode->setEnabled(true);

		//ui.m_spectrometerCtrl->setEnabled(true);
		ui.m_openSpectrometerButton->setEnabled(true);

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

	ui.m_imageTakingButton->setEnabled(false);
	ui.m_analogGainSet->setEnabled(false);
	ui.m_digitalGainSet->setEnabled(false);
	ui.m_exposureMode->setEnabled(false);

	ui.m_captureSpectrumBox->setEnabled(false);
	//ui.m_spectrometerCtrl->setEnabled(false);
	ui.m_wavelengthSlider->setEnabled(false);

	m_imageModel.closeUSBCamera();
	m_timer.stop();

	if (ui.m_pauseButton->text() != "暂停")
	{
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		m_imageModel.whetherPausingUSBCamera(false);
	}

	//m_statusBarLabel->setText(QStringLiteral("就绪"));
	ui.statusBar->showMessage(QStringLiteral("就绪"));
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
	ui.m_showLabel->setPixmap(image);
	++m_frameCount;

	if (m_isCapturingSpectrum)
	{
		if (m_countForCapturingSpectrum == 0)
		{
			if (m_curWavelength <= m_maxWavelength)
			{
				m_imageModel.changeWavelength(m_curWavelength);
				m_curWavelength += m_stepOfWavelength;
				++m_countForProgressBar;
			}
		}
			
		++m_countForCapturingSpectrum;
		if (m_countForCapturingSpectrum == 10)
		{
			m_imageModel.takeSpectrumImage();
		}

		if (m_countForCapturingSpectrum == 20)
		{
			m_countForCapturingSpectrum = 0;
			m_progressDialog->setValue(m_countForProgressBar);
		}

	}
}

void MainWindow::showFrameRate()
{
	//QString receiveFrameRate = QString::number(m_receiveFramesCount);
	//m_statusBarLabel->setText(receiveFrameRate + "fps");
	ui.m_receiveRateLabel->setText(QString::number(m_frameCount));
	m_frameCount = 0;
	//m_receiveFramesCount = 0;
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

		ui.m_captureSpectrumBox->setEnabled(false);
	}
	else
	{
		m_imageModel.whetherPausingUSBCamera(false);
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		ui.m_imageTakingButton->setEnabled(true);


		if (!ui.m_openSpectrometerButton->isEnabled())
			ui.m_captureSpectrumBox->setEnabled(true);
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

void MainWindow::setDigitalGain(int index)
{
	uchar u4;
	++index;
	if (index != 8)
		u4 = index << 5;
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
	// cmos相关
	// A + Q = 1904, pixclk = 29.7 Mhz
	// (A + Q) / pixclk = 64.1 us
	// exposure_time = valueof(0x3012) * 64.1 us
	// max_value_of(0x3012) = 1136

	qDebug() << value;
	uchar u3;
	uchar u4;

	value = value * 1000 / 64;
	u3 = value >> 8;
	u4 = value;

	m_imageModel.sendSettingCommand(0x30, 0x12, u3, u4);
}

void MainWindow::chooseSavingPath()
{
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("存储路径选择"), ".");
	if (path == "")
		return;
	m_imageModel.setSavingPath(path);
}

void MainWindow::takeImage()
{
	m_imageModel.takeImage();
}

void MainWindow::changeWavelength()
{
	unsigned short wavelen = ui.m_wavelengthSlider->value();
	m_imageModel.changeWavelength(wavelen);
}

void MainWindow::openSpectrometer()
{
	if (m_imageModel.openSpectrometer())
	{

		ui.m_openSpectrometerButton->setEnabled(false);
		ui.m_wavelengthSlider->setEnabled(true);

		m_imageModel.changeWavelength(m_curWavelength);		
		ui.m_captureSpectrumBox->setEnabled(true);


	}
	else
	{
		showStateOnStatusBar("Open LCTF failed, please try again");
	}

	
}

void MainWindow::captureSpectrumImg()
{
	m_curWavelength = ui.m_capMinWavelen->value();
	m_minWavelength = ui.m_capMinWavelen->value();
	m_maxWavelength = ui.m_capMaxWavelen->value();
	m_stepOfWavelength = ui.m_stepOfWavelen->value();
	m_countForCapturingSpectrum = 0;
	m_countForProgressBar = 0;

	int num = (m_maxWavelength - m_minWavelength) / m_stepOfWavelength + 1;
	QProgressDialog progress(QStringLiteral("捕获光谱图像"), QStringLiteral("停止捕获"), 0, num, this);
	m_progressDialog = &progress;
	progress.setWindowModality(Qt::WindowModal);

	// 当前目录下建立频谱文件夹
	QString path = m_imageModel.getSavingPath();
	QDir dir(path);
	QTime time = QTime::currentTime();
	QString dirName = time.toString("hhmmsszzz");
	dir.mkdir(dirName);
	m_imageModel.setSavingPath(path + "\\" + dirName);

	m_isCapturingSpectrum = true;
	
	progress.exec();

	m_isCapturingSpectrum = false;

	m_imageModel.setSavingPath(path);

}


// 窗体每1.5ms左右自动进入paintEvent
void MainWindow::paintEvent(QPaintEvent* event)
{
	QMainWindow::paintEvent(event);
	int xPos = ui.m_spectrometerCtrl->x() + ui.m_wavelengthSlider->x() - 5;
	int yPos = ui.m_spectrometerCtrl->y() + ui.m_labelForPos->y() + ui.m_spectrometerCtrl->layout()->spacing() + 2;
	int num = 10;
	int interval = (m_sliderMaxWavelength - m_sliderMinWavelength) / num;
	int posInterval = ui.m_wavelengthSlider->width() / num;
	ui.m_wavelengthSlider->setTickInterval(interval);
	QPainter painter(this);
	for (int i = 0; i <= num; ++i) {
		painter.drawText(xPos + i * posInterval, yPos, QString::number(m_sliderMinWavelength + i * interval));
	}

}

void MainWindow::setHorizontalMirror()
{
	m_imageModel.setHorizontalMirror();
}

void MainWindow::setVerticalMirror()
{
	m_imageModel.setVerticalMirror();
}

void MainWindow::showStateOnStatusBar(QString state, int timeOut)
{
	ui.statusBar->showMessage(state, timeOut);
}

void MainWindow::setIlluminationState(int state)
{
	switch (state)
	{
	case Qt::Checked:
		m_imageModel.setLowIlluminationChecked(true);
		break;
	case Qt::Unchecked:
		m_imageModel.setLowIlluminationChecked(false);
		break;
	default:
		break;
	}
}