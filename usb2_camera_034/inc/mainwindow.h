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
	void updateImage(QPixmap visible, QPixmap infrared);

	void showFrameRate();

	void saveData();

	void countReceiveFrames();
	
	void changeImageToColor(bool flag);

	void chooseSavingPath();
	void takeImage();


	//dual lights fusion
	void changeInfraredColor();

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


	int m_bitsPerPixel;
};

#endif // MAINWINDOW_H
