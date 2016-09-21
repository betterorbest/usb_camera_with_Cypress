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

	bool initCameraConfig();

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

	void switchResolution(int index);
	void setAnalogGain(int index);

	void setRedGain(int gain);
	void setGreenGain(int gain);
	void setBlueGain(int gain);
	void setGlobalGain(int gain);

	void setExposureMode(bool isAuto);
	void setExposureValue(int value);

	void chooseSavingPath();
	void takeImage();
private:
	Ui::MainWindowClass ui;

	ImageModel m_imageModel;

	QTimer m_timer;

	QLabel *m_frameRateLabel;

	int m_frameCount;

	int m_receiveFramesCount;

	int m_imageWidth;
	int m_imageHeight;

	bool m_isClosed;
};

#endif // MAINWINDOW_H
