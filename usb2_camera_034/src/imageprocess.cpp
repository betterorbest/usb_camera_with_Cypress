#include "imageprocess.h"

#include "qdebug.h"
#include <Windows.h> 
#include <QtConcurrent>
#include "imagefifo.h"
//#include "qtextstream.h"

ImageProcess::ImageProcess()
	:m_imageProcessingFlag(true),
	m_pauseFlag(false),
	m_path("."),
	m_isTakingImage(false),
	m_imageData(nullptr)
{
	initLookupTable();
}

ImageProcess::~ImageProcess()
{
	if (m_imageData != nullptr)
	{
		delete[] m_imageData;
		m_imageData = nullptr;
	}
}

void ImageProcess::initialize(int width, int height, bool isColor)
{
	m_imageData = new uchar[width * height];
	m_isColor = isColor;
}

void ImageProcess::initialize(int visibleWidth, int visibleHeight, int infraWidth, int infraHeight, bool isColor, InfraredColor infraColor)
{
	m_visibleWidth = visibleWidth;
	m_visibleHeight = visibleHeight;
	m_infraredWidth = infraWidth;
	m_infraredHeight = infraHeight;
	m_isColor = isColor;
	m_infraredColor = infraColor;
}

void ImageProcess::dataToImage(unsigned char *data, int bitsPerPixel, int width, int height)
{
	//bitsPerPixel为12bits

	cv::Mat image = cv::Mat(height, width, CV_16UC1, data);
	cv::Mat visibleData = image(cv::Rect(0, 0, m_visibleWidth, m_visibleHeight));
	cv::Mat infraredData = image(cv::Rect(m_visibleWidth, 0, m_infraredWidth, m_infraredHeight));


	cv::Mat visibleDisplay;
	cv::Mat infraredDisplay;
	visibleDataToImage(visibleData, visibleDisplay, m_isColor);
	infraredDataToImage(infraredData, infraredDisplay, m_infraredColor);

	QImage visibleImage(visibleDisplay.data, visibleDisplay.cols, visibleDisplay.rows, visibleDisplay.step, QImage::Format_RGB888);
	QImage infraImage(infraredDisplay.data, infraredDisplay.cols, infraredDisplay.rows, infraredDisplay.step, QImage::Format_RGB888);
		
	QPixmap visiblePixmap(QPixmap::fromImage(visibleImage));
	QPixmap infraPixmap(QPixmap::fromImage(infraImage));
	emit showImage(visiblePixmap, infraPixmap);
	if (m_isTakingImage)
	{
		DWORD start = GetTickCount();
		//takeOriginalImage(cv::Mat(height, width, CV_16UC1, data16bits), m_imageShow);
		takeShowingImage(visiblePixmap, infraPixmap);
		DWORD end = GetTickCount();
		qDebug() << end - start << "this is the time";
	}
	/*********数据接收较慢时使用*******************/
	/*m_image = QImage(m_imageData, m_imageWidth, m_imageHeight, QImage::Format_Grayscale8);
	QtConcurrent::run(this, &ImageProcess::imageToPixmap, m_image);*/

}


void ImageProcess::imageToPixmap(QImage &image)
{
	//DWORD start = GetTickCount();
	QPixmap pixmap = QPixmap::fromImage(image);
	//DWORD end = GetTickCount();
	//qDebug() << end - start << "this is thread " << QThread::currentThreadId();
	emit showImage(pixmap);
}

void ImageProcess::saveOriginalData(unsigned short *data)
{
	int size = m_imageHeight * m_imageWidth;
	unsigned short *tempData = new unsigned short[size];
	for (int i = 0; i < size; ++i)
	{
		tempData[i] = data[i];
	}


	QTime time = QTime::currentTime();
	QString str = time.toString("hhmmsszzz");
	QString path = "./" + str + ".txt";
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly))
		return;
	
	QTextStream out(&file);
	for (int i = 0; i < m_imageHeight; ++i)
	{
		int k = i * m_imageWidth;
		for (int j = 0; j < m_imageWidth; ++j)
		{
			out << tempData[k + j] << " ";
		}
		out << "\r\n";
	}
	delete tempData;
	tempData = nullptr;

}

void ImageProcess::enableSaveData()
{
	m_saveOriginalDataFlag = true;
}

void ImageProcess::setImageColorOrBlack(bool isColor)
{
	m_isColor = isColor;
}

void ImageProcess::dataToImage()
{
	ImageData* imageData;
	while (m_imageProcessingFlag)
	{
		imageData = ImageFifo::getFifoHead();
		if (imageData == nullptr) continue;
		if (!m_pauseFlag)
		{
			dataToImage((*imageData).m_data, (*imageData).m_bitsPerPixel, (*imageData).m_imageWidth, (*imageData).m_imageHeight);
		}
		ImageFifo::outFifo();
	}

	ImageFifo::emptyFifo();
}

void ImageProcess::disableImageProcess()
{
	m_imageProcessingFlag = false;
}

void ImageProcess::enableImageProcess()
{
	m_imageProcessingFlag = true;
}

void ImageProcess::setPauseFlag(bool flag)
{
	m_pauseFlag = flag;
}

void ImageProcess::setSavingPath(QString path)
{
	m_path = path;
}

void ImageProcess::takeOriginalImage(const cv::Mat& image, const QPixmap& pixmap)
{
	QTime time = QTime::currentTime();
	QString str = time.toString("hhmmsszzz");
	QString path = m_path + "\\" + str;
	cv::imwrite((path + ".png").toLocal8Bit().toStdString(), image);
	pixmap.save(path + ".bmp");
	m_isTakingImage = false;
}

void ImageProcess::takeShowingImage(const QPixmap& visible, const QPixmap& infrared)
{
	QTime time = QTime::currentTime();
	QString str = time.toString("hhmmsszzz");
	QString visiblePath = m_path + "\\" + "vis_" + str + ".bmp";
	QString infraredPath = m_path + "\\" + "infra_" + str + ".bmp";
	visible.save(visiblePath);
	infrared.save(infraredPath);
	m_isTakingImage = false;
}

void ImageProcess::setTakingImageFlag(bool flag)
{
	if (m_isTakingImage)
		return;
	m_isTakingImage = flag;
}



void ImageProcess::autoWhiteBalance(cv::Mat &src, cv::Mat &dst)
{
	/*********原始的灰度世界算法**************/
	cv::Scalar averagePerChannel = cv::mean(src);
	double ratio = (averagePerChannel[0] + averagePerChannel[1] + averagePerChannel[2]) / 3;
	averagePerChannel[0] = ratio / averagePerChannel[0];
	averagePerChannel[1] = ratio / averagePerChannel[1];
	averagePerChannel[2] = ratio / averagePerChannel[2];
	cv::multiply(src, averagePerChannel, dst);

	/**********完美反射算法*****************/
	//int histRGBSum[766] = { 0 };
	//short *RGBSum = new short[src.rows * src.cols];
	//ZeroMemory(RGBSum, src.rows * src.cols * sizeof(short));
	//
	////遍历像素的准备
	//int nr = src.rows;
	//int nc = src.cols;
	//if (src.isContinuous())    //提高遍历的效率
	//{
	//	nc = nc * nr;
	//	nr = 1;
	//}

	////统计各个像素R+G+B的值
	//short sum;
	//short *ptrRGBSum = RGBSum;
	//for (int i = 0; i < nr; ++i)
	//{
	//	uchar *data = src.ptr<uchar>(i);
	//	for (int j = 0; j < nc; ++j)
	//	{
	//		sum = (short)(*data + *(data + 1) + *(data + 2));
	//		++histRGBSum[sum];
	//		*ptrRGBSum = sum;
	//		data += 3;
	//		++ptrRGBSum;
	//	}
	//}

	////确定像素阈值
	//float thresholdRatio = 0.02;
	//int threshold;
	//int thresholdSum = 0;
	//for (int i = 765; i > 0; --i)
	//{
	//	thresholdSum += histRGBSum[i];
	//	if (thresholdSum >= thresholdRatio * src.total())
	//	{
	//		threshold = i;
	//		break;
	//	}
	//}

	////遍历图像，计算大于阈值的像素点的R\G\B分量的累积和的平均值
	//cv::Scalar averageRGB(0);
	//int amount = 0;
	//ptrRGBSum = RGBSum;
	//for (int i = 0; i < nr; ++i)
	//{
	//	uchar *data = src.ptr<uchar>(i);
	//	for (int j = 0; j < nc; ++j)
	//	{
	//		if (*ptrRGBSum > threshold)
	//		{
	//			averageRGB[0] += *data;
	//			averageRGB[1] += *(data + 1);
	//			averageRGB[2] += *(data + 2);
	//			++amount;
	//		}
	//		data += 3;
	//		++ptrRGBSum;
 //		}
	//}
	//averageRGB /= amount;
	//
	////对原图像应用该平均值进行比例调整
	//averageRGB[0] = 255 / averageRGB[0];
	//averageRGB[1] = 255 / averageRGB[1];
	//averageRGB[2] = 255 / averageRGB[2];
	//cv::multiply(src, averageRGB, dst);

	//delete[] RGBSum;


	//cv::Vec3d m_last_avg_bgr = cv::Vec3d(-1, -1, -1);
	//double m_smooth_ratio = 0.8;
	//std::vector<int> m_white_hist;
	//m_white_hist.resize(766, 0);
	//std::fill(m_white_hist.begin(), m_white_hist.end(), 0);
	//std::vector<cv::Mat> bgr;
	//split(src, bgr);
	//cv::Mat sum = cv::Mat::zeros(src.size(), CV_32FC1);
	//sum = cv::Mat::zeros(src.size(), CV_32FC1);
	//cv::accumulate(bgr[0], sum);
	//cv::accumulate(bgr[1], sum);
	//cv::accumulate(bgr[2], sum);
	//double min_value, max_value;
	//cv::minMaxLoc(sum, &min_value, &max_value);
	//int t = int(max_value*(1 - 0.1));

	//float* ptr_sum = sum.ptr<float>();
	//ptr_sum = sum.ptr<float>();
	//for (int i = 0; i < sum.total(); ++i)
	//{
	//	m_white_hist[ptr_sum[i]]++;
	//}

	////t = 255;
	//int hist_sum = 0;
	//for (int i = 765; i >= 0; --i)
	//{
	//	hist_sum += m_white_hist[i];
	//	if (hist_sum > sum.total() * 0.05)
	//	{
	//		t = i;
	//		break;
	//	}
	//}

	//ptr_sum = sum.ptr<float>();
	//cv::Vec3b* ptr_img = src.ptr<cv::Vec3b>();
	//ptr_img = src.ptr<cv::Vec3b>();
	//int count = 0;
	//cv::Vec3d avg_bgr(0, 0, 0);
	//for (int i = 0; i < sum.total(); ++i)
	//{
	//	if (ptr_sum[i] > t)
	//	{
	//		count++;
	//		avg_bgr += ptr_img[i];
	//	}
	//}
	//avg_bgr /= count;
	//if (count > 0)
	//{
	//	if (m_last_avg_bgr[0] < 0)
	//	{
	//		m_last_avg_bgr = avg_bgr;
	//	}
	//	avg_bgr = m_smooth_ratio * m_last_avg_bgr + (1 - m_smooth_ratio) * avg_bgr;
	//	m_last_avg_bgr = avg_bgr;

	//	cv::Scalar gain(255 / avg_bgr[0], 255 / avg_bgr[1], 255 / avg_bgr[2]);
	//	cv::multiply(src, gain, dst);
	//}
}



void ImageProcess::visibleDataToImage(cv::Mat&src, cv::Mat &dst, bool isColor)
{
	//raw data转图片显示
	DWORD start = GetTickCount();
	src.convertTo(dst, CV_8UC1, 0.0625);
	DWORD end = GetTickCount();
	qDebug() << end - start;

	if (isColor)
		cv::cvtColor(dst, dst, CV_BayerGB2RGB);
	else
		cv::cvtColor(dst, dst, CV_GRAY2RGB);
}


void ImageProcess::infraredDataToImage(cv::Mat& src, cv::Mat& dst, InfraredColor infraColor)
{
	cv::medianBlur(src, dst, 3);
	

	////得到一帧最大值、最小值、平均值
	//minMaxLoc(m_image_16bit, &m_min_pixel, &m_max_pixel, 0, &m_max_pixel_position);
	//m_avg_pixel = mean(m_image_16bit);

	//Mat image_16bit_tmp;
	//image_16bit_tmp = m_image_16bit.clone();

	//16bit转8bit图像处理
	infrared14bitsTo8bits(dst, dst);

	//单通道变为3通道
	cv::cvtColor(dst, dst, CV_GRAY2RGB);

	switch (infraColor)
	{
	case METAL:
	{
		//查找表法，效率高
		cv::LUT(dst, m_metalLUT, dst);
	}
	break;
	case RAINBOW:
	{
		cv::LUT(dst, m_rainbowLUT, dst);
	}
	break;
	case GRAY_INVERSE:
	{
		//使用查找表法反转
		cv::LUT(dst, m_grayInverseLUT, dst);
	}
	break;
	default:
		break;
	}

	/*Point point1(m_max_pixel_position.x - 5, m_max_pixel_position.y);
	Point point2(m_max_pixel_position.x + 5, m_max_pixel_position.y);
	Point point3(m_max_pixel_position.x, m_max_pixel_position.y - 5);
	Point point4(m_max_pixel_position.x, m_max_pixel_position.y + 5);
	line(image_tmp, point1, point2, Scalar(255, 0, 0));
	line(image_tmp, point3, point4, Scalar(255, 0, 0));*/

}

void ImageProcess::infrared14bitsTo8bits(cv::Mat &src, cv::Mat &dst)
{
	/*************自适应直方图******************/
	//计算直方图
	int histSize[1] = { 0xffff + 1 };
	float hrangs[2] = { 0, 0xffff + 1 };
	const float* ranges[1] = { hrangs };
	int channels[1] = { 0 };
	cv::Mat hist;
	cv::calcHist(&src, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
	int imin = 0;
	for (; imin < histSize[0]; ++imin)
		if (hist.at<float>(imin) > 1)     //改为可调界限
			break;
	int imax = histSize[0] - 1;
	for (; imax >= 0; --imax)
		if (imin >= imax || hist.at<float>(imax) > 0)
			break;

	if (imin >= imax)
	{
		imax = imin;
		imin = imin - 2;
	}

	cv::Mat tempDst(src.rows, src.cols, CV_8UC1);
	for (int i = 0; i < src.rows; i++)
	{
		unsigned short *dataSrc = src.ptr<unsigned short>(i);
		unsigned char *dataDst = tempDst.ptr<unsigned char>(i);
		for (int j = 0; j < src.cols; j++)
		{
			if (dataSrc[j] <= imin)
			{
				dataDst[j] = 0;
			}
			else if (dataSrc[j] >= imax)
			{
				dataDst[j] = 255;
			}
			else
			{
				dataDst[j] = (dataSrc[j] - imin + 0.0) / (imax - imin) * 255;
			}
		}
	}

	dst = tempDst;
}

void ImageProcess::initLookupTable()
{
	//伪彩查找表 RGB排列方式
	m_metalLUT = cv::Mat(1, 256, CV_8UC3);
	uchar *p1 = m_metalLUT.data;
	for (int i = 0; i < 256; i++)
	{
		if (i >= 0 && i < 22)
		{
			p1[3 * i] = 0;
			p1[3 * i + 1] = 0;
			p1[3 * i + 2] = (i / 22.0) * 115;
		}
		else if (i >= 22 && i < 95)
		{
			float seg_ratio = (i - 22) / 73.0f;
			p1[3 * i] = seg_ratio * 190;
			p1[3 * i + 1] = 0;
			p1[3 * i + 2] = seg_ratio * 35 + 115;
		}
		else if (i >= 95 && i < 140)
		{
			float seg_ratio = (i - 95) / 45.0f;
			p1[3 * i] = seg_ratio * 50 + 190;
			p1[3 * i + 1] = seg_ratio * 80;
			p1[3 * i + 2] = 150 - seg_ratio * 150;
		}
		else if (i >= 140 && i < 150)
		{
			float seg_ratio = (i - 140) / 10.0f;
			p1[3 * i] = seg_ratio * 15 + 240;
			p1[3 * i + 1] = seg_ratio * 20 + 80;
			p1[3 * i + 2] = 0;
		}
		else if (i >= 150 && i < 220)
		{
			float seg_ratio = (i - 150) / 70.0f;
			p1[3 * i] = 255;
			p1[3 * i + 1] = seg_ratio * 120 + 100;
			p1[3 * i + 2] = 0;
		}
		else if (i >= 220 && i < 240)
		{
			float seg_ratio = (i - 220) / 20.0f;
			p1[3 * i] = 255;
			p1[3 * i + 1] = seg_ratio * 35 + 220;
			p1[3 * i + 2] = seg_ratio * 150;
		}
		else
		{
			float seg_ratio = (i - 240) / 15.0f;
			p1[3 * i] = 255;
			p1[3 * i + 1] = 255;
			p1[3 * i + 2] = seg_ratio * 105 + 150;
		}

	}

	//网上通用的伪彩
	/*m_look_up_table_color = Mat(1, 256, CV_8UC3);
	uchar *p1 = m_look_up_table_color.data;
	for (int i = 0; i < 256; i++)
	{
	p1[3 * i] = abs(0 - i);
	p1[3 * i + 1] = abs(127 - i);
	p1[3 * i + 2] = abs(255 - i);
	}*/

	//彩虹图查找表
	m_rainbowLUT = cv::Mat(1, 256, CV_8UC3);
	uchar *p2 = m_rainbowLUT.data;
	for (int i = 0; i < 256; i++)
	{
		int tmp = i;
		if (i <= 51)
		{
			p2[3 * i] = 0;
			p2[3 * i + 1] = tmp * 5;
			p2[3 * i + 2] = 255;
		}
		else if (i <= 102)
		{
			tmp -= 51;
			p2[3 * i] = 0;
			p2[3 * i + 1] = 255;
			p2[3 * i + 2] = 255 - tmp * 5;
		}
		else if (i <= 153)
		{
			tmp -= 102;
			p2[3 * i] = tmp * 5;
			p2[3 * i + 1] = 255;
			p2[3 * i + 2] = 0;
		}
		else if (i <= 204)
		{
			tmp -= 153;
			p2[3 * i] = 255;
			p2[3 * i + 1] = 255 - (uchar)(128.0 * tmp / 51.0 + 0.5);
			p2[3 * i + 2] = 0;
		}
		else
		{
			tmp -= 204;
			p2[3 * i] = 255;
			p2[3 * i + 1] = 127 - (uchar)(127.0 * tmp / 51.0 + 0.5);
			p2[3 * i + 2] = 0;
		}
	}

	//灰度反转查找表
	m_grayInverseLUT = cv::Mat(1, 256, CV_8UC1);
	uchar *p3 = m_grayInverseLUT.data;
	for (int i = 0; i < 256; i++)
	{
		p3[i] = 255 - i;
	}
}

void ImageProcess::setInfraColor(InfraredColor color)
{
	m_infraredColor = color;
}