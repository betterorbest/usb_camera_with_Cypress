#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "imagemodel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void paintEvent(QPaintEvent* event);

	
private:
	void initCameraConfig();

public slots:
	void openCamera();
	void closeCamera();
	void pauseCamera();

	void updateImage(QPixmap image);

	void showFrameRate();

	void saveData();

	void countReceiveFrames();

	void changeWidthTo8bitsPerPixel(bool flag);
	
	void changeImageToColor(bool flag);

	void setAnalogGain(int index);

	void setDigitalGain(int index);

	void setExposureMode(bool isAuto);
	void setExposureValue(int value);

	void chooseSavingPath();
	void takeImage();



	//光谱仪相关
	void changeWavelength();
	void openSpectrometer();
	void captureSpectrumImg();

	void setHorizontalMirror();
	void setVerticalMirror();

	void setIlluminationState(int state);


	void showStateOnStatusBar(QString state, int timeOut = 0);

private:
	Ui::MainWindowClass ui;

	ImageModel m_imageModel;

	QTimer m_timer;

	//QLabel *m_statusBarLabel;

	int m_frameCount;

	int m_receiveFramesCount;

	int m_imageWidth;
	int m_imageHeight;

	bool m_isClosed;

	bool m_isColor;
	int m_bitsPerPixel;


	//光谱仪相关
	bool m_isCapturingSpectrum;
	uchar m_countForCapturingSpectrum;
	unsigned short m_curWavelength;
	unsigned short m_minWavelength;
	unsigned short m_maxWavelength;
	unsigned short m_stepOfWavelength;
	int m_countForProgressBar;
	QProgressDialog* m_progressDialog;

	unsigned short m_sliderMinWavelength;
	unsigned short m_sliderMaxWavelength;

};

#endif // MAINWINDOW_H
