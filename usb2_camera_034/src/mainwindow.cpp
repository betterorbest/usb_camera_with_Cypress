#include "mainwindow.h"
#include "qsettings.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_imageModel(this),
	m_frameCount(0),
	m_receiveFramesCount(0),
	m_isClosed(false)
{
 	ui.setupUi(this);

	initCameraConfig();
		
	m_statusBarLabel = new QLabel(ui.statusBar);
	ui.statusBar->addWidget(m_statusBarLabel);
	m_statusBarLabel->setText(QStringLiteral("就绪"));

	//Qt4的信号槽使用方式
	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
	connect(ui.m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseCamera()));

	connect(ui.m_colorImageChoosed, SIGNAL(toggled(bool)), this, SLOT(changeImageToColor(bool)));

	//Qt5的重载信号与槽连接的使用方式
	connect(ui.m_pathChoosingButton, &QPushButton::clicked, this, &MainWindow::chooseSavingPath);
	connect(ui.m_imageTakingButton, &QPushButton::clicked, this, &MainWindow::takeImage);
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(showFrameRate()));
	

	connect(ui.m_infraGray, &QRadioButton::clicked, this, &MainWindow::changeInfraredColor);
	connect(ui.m_infraGrayInverse, &QRadioButton::clicked, this, &MainWindow::changeInfraredColor);
	connect(ui.m_infraMetal, &QRadioButton::clicked, this, &MainWindow::changeInfraredColor);
	connect(ui.m_infraRainbow, &QRadioButton::clicked, this, &MainWindow::changeInfraredColor);

}

MainWindow::~MainWindow()
{
	//m_imageModel.closeUSBCamera();
}

void MainWindow::initCameraConfig()
{
	//TODO 配置信息设置
	QSettings settings("camconfig.ini", QSettings::IniFormat);
	m_imageWidth = settings.value("Dual/width").toInt();
	m_imageHeight = settings.value("Dual/height").toInt();
	m_bitsPerPixel = settings.value("Dual/pixbitswidth").toInt();
	bool isColor = settings.value("Dual/iscolor").toBool();
	int bufferNum = settings.value("Transfer/buffernum").toInt();
	int packetNum = settings.value("Transfer/packetnum").toInt();
	int xferQueSize = settings.value("Transfer/xferquesize").toInt();
	int timeOut = settings.value("Transfer/timeout").toInt();

	if (m_imageWidth == 0 || m_imageHeight == 0)
	{
		m_imageWidth = 1920;
		m_imageHeight = 960;
	}

	if (m_bitsPerPixel <= 0)
		m_bitsPerPixel = 12;

	if (bufferNum <= 0)
		bufferNum = 2;

	if (packetNum <= 0)
		packetNum = 45;

	if (xferQueSize <= 0)
		xferQueSize = 5;

	if (timeOut <= 0)
		timeOut = 1000;

	m_imageModel.initialize(m_imageWidth, m_imageHeight, m_bitsPerPixel, bufferNum, isColor);
	m_imageModel.initializeTransfer(packetNum, xferQueSize, timeOut);
	m_imageModel.initializeDual(1280, 960, 640, 512, isColor, ImageProcess::METAL);

	ui.m_visibleDisplay->setFixedSize(QSize(1280, 960));
	ui.m_infraDisplay->setFixedSize(QSize(640, 512));


	//初始化组件部分配置
	if (!isColor)
		ui.m_grayImageChoosed->setChecked(true);

	ui.m_infraMetal->setChecked(true);

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

		ui.m_imageTakingButton->setEnabled(true);
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

	m_imageModel.closeUSBCamera();
	m_timer.stop();

	if (ui.m_pauseButton->text() != "暂停")
	{
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		m_imageModel.whetherPausingUSBCamera(false);
	}

	m_statusBarLabel->setText(QStringLiteral("就绪"));
	ui.m_startButton->setEnabled(true);
	m_frameCount = 0;
	m_receiveFramesCount = 0;
	m_isClosed = true;
	ui.m_visibleDisplay->clear();
	ui.m_infraDisplay->clear();
	ui.m_receiveRateLabel->setText(QString::number(0));
}

void MainWindow::updateImage(QPixmap image)
{
	if (m_isClosed)
		return;
	//qDebug() << "updateImage";
	//ui.m_showLabel->resize(image.size());
	
	//ui.m_showLabel->clear();
	ui.m_visibleDisplay->setPixmap(image);
	//DWORD start1 = GetTickCount();
	++m_frameCount;

	/*DWORD end1 = GetTickCount();
	qDebug() << end1 - start1;*/
}

void MainWindow::updateImage(QPixmap visible, QPixmap infrared)
{
	if (m_isClosed)
		return;

	ui.m_visibleDisplay->setPixmap(visible);
	ui.m_infraDisplay->setPixmap(infrared);
	++m_frameCount;
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
	}
	else
	{
		m_imageModel.whetherPausingUSBCamera(false);
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		ui.m_imageTakingButton->setEnabled(true);
	}
}


void MainWindow::changeImageToColor(bool flag)
{
	m_imageModel.changeImageToColor(flag);
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


//dual lights fusion
void MainWindow::changeInfraredColor()
{
	//click radiobutton 信号就会触发该槽
	//已选中的选项，再次点击，依然会进入该槽
	if (ui.m_infraGray->isChecked())
	{
		m_imageModel.setInfraredColor(ImageProcess::GRAY);
		qDebug() << "gray" << sender()->objectName();
	}
	else if (ui.m_infraGrayInverse->isChecked())
	{
		m_imageModel.setInfraredColor(ImageProcess::GRAY_INVERSE);
		qDebug() << "inverse" << sender()->objectName();
	}
	else if (ui.m_infraMetal->isChecked())
	{
		m_imageModel.setInfraredColor(ImageProcess::METAL);
		qDebug() << "metal" << sender()->objectName();
	}
	else
	{
		m_imageModel.setInfraredColor(ImageProcess::RAINBOW);
		qDebug() << "rainbow" << sender()->objectName();
	}
}