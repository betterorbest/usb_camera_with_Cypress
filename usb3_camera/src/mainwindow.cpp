#include "mainwindow.h"
#include "qsettings.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	m_imageModel(this, 960, 1280),
	m_frameCount(0),
	m_receiveFramesCount(0)
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

	connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(openCamera()));
	connect(ui.m_stopButton, SIGNAL(clicked()), this, SLOT(closeCamera()));
	connect(ui.m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseCamera()));

	connect(ui.m_8bitsChoosed, SIGNAL(toggled(bool)), this, SLOT(changeWidthTo8bitsPerPixel(bool)));
	connect(ui.m_colorImageChoosed, SIGNAL(toggled(bool)), this, SLOT(changeImageToColor(bool)));

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
		m_imageModel.readData();
		m_frameCount = 0;
		m_timer.start(1000);

		ui.m_bitsPerPixelChange->setEnabled(true);
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

	m_imageModel.closeUSBCamera();
	m_timer.stop();

	if (ui.m_pauseButton->text() != "暂停")
	{
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
		m_imageModel.whetherPausingUSBCamera(false);
	}

	m_frameRateLabel->setText(QStringLiteral("就绪"));
	ui.m_startButton->setEnabled(true);
	//m_frameCount = 0;
	//m_receiveFramesCount = 0;
}

void MainWindow::updateImage(QPixmap image)
{
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
	m_frameRateLabel->setText(frameRate + "fps");
	ui.m_receiveRateLabel->setText(receiveFrameRate);
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
		m_imageModel.whetherPausingUSBCamera(true);
		ui.m_pauseButton->setText(QStringLiteral("取消暂停"));
	}
	else
	{
		m_imageModel.whetherPausingUSBCamera(false);
		ui.m_pauseButton->setText(QStringLiteral("暂停"));
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