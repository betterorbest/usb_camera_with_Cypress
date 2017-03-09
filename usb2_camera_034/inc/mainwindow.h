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

	void setGlobalGain(int gain);

	void setExposureMode(bool isAuto);
	void setExposureValue(int value);

	void chooseSavingPath();
	void takeImage();

	void changeWavelength();
	void openSpectrometer();
	void captureSpectrumImg();
	bool setWavelength(unsigned short wavelen);
private:
	Ui::MainWindowClass ui;

	ImageModel m_imageModel;

	QTimer m_timer;

	QLabel *m_statusBarLabel;

	int m_frameCount;

	int m_receiveFramesCount;

	int m_imageWidth;
	int m_imageHeight;

	bool m_isClosed;

	bool m_isColor;
	int m_bitsPerPixel;

	bool m_isCapturingSpectrum;
	uchar m_countForCapturingSpectrum;
	QProgressDialog *m_progress;
	unsigned short m_wavelength;
};

#endif // MAINWINDOW_H
