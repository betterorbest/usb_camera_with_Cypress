#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QtCore>
//#include "qimage.h"
#include "qpixmap.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

class ImageProcess : public QObject
{
	Q_OBJECT

public:
	typedef enum{
		GRAY,
		GRAY_INVERSE,
		METAL,
		RAINBOW
	} InfraredColor;


	ImageProcess();
	~ImageProcess();
	void initialize(int width, int height, bool isColor);
	void initialize(int visibleWidth, int visibleHeight, int infraWidth, int infraHeight, bool isColor, InfraredColor infraColor);
	void setWidth(int width);
	void setHeight(int height);
	void imageToPixmap(QImage &image);
	void saveOriginalData(unsigned short *data);
	void enableSaveData();
	void setImageColorOrBlack(bool isColor);
	
	void disableImageProcess();
	void enableImageProcess();

	void setPauseFlag(bool flag);

	void autoWhiteBalance(cv::Mat &src, cv::Mat &dst);

	void dataToImage(unsigned char *data, int bitsPerPixel, int width, int height);

	void setSavingPath(QString path);
	void takeOriginalImage(const cv::Mat& image,  const QPixmap& pixmap);
	void takeShowingImage(const QPixmap& visible, const QPixmap& infrared);
	void setTakingImageFlag(bool flag);

	
	void initLookupTable();
	void visibleDataToImage(cv::Mat& src, cv::Mat& dst, bool isColor);
	void infrared14bitsTo8bits(cv::Mat& src, cv::Mat& dst);
	void infraredDataToImage(cv::Mat& src, cv::Mat& dst, InfraredColor infraColor);
	void setInfraColor(InfraredColor color);

signals:
	void showImage(QPixmap visible, QPixmap infra);
	void showImage(QPixmap visible);

public slots:
	void dataToImage();

private:
	unsigned char *m_imageData;
	
	int m_imageHeight;
	int m_imageWidth;

	QPixmap m_imageShow;
	QImage m_image;
	QString m_path;

	bool m_saveOriginalDataFlag;
	bool m_isColor;

	bool m_imageProcessingFlag;
	bool m_pauseFlag;
	bool m_isTakingImage;

	//dual lights fusion
	cv::Mat m_metalLUT;
	cv::Mat m_grayInverseLUT;
	cv::Mat m_rainbowLUT;

	InfraredColor m_infraredColor;
	int m_visibleWidth;
	int m_visibleHeight;
	int m_infraredWidth;
	int m_infraredHeight;
	
};

inline void ImageProcess::setWidth(int width)
{
	m_imageWidth = width;
}

inline void ImageProcess::setHeight(int height)
{
	m_imageHeight = height;
}

#endif