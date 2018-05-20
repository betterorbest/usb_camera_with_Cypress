#include "spectrumanalysis.h"

SpectrumAnalysisDialog::SpectrumAnalysisDialog(QWidget* parent)
	:QDialog(parent)
{
	ui.setupUi(this);

	ui.m_showLabel->setFixedSize(QSize(640, 480));
	connect(ui.m_loadImagesButton, &QPushButton::clicked, this, &SpectrumAnalysisDialog::loadImamges);
	connect(ui.m_showLabel, &MyLabel::currentPos, this, &SpectrumAnalysisDialog::calculateReflectivity);
	connect(ui.m_listImg, &QListWidget::itemClicked, this, &SpectrumAnalysisDialog::showSelectedImg);
	connect(ui.m_clearCurvesButton, &QPushButton::clicked, this, &SpectrumAnalysisDialog::clearGraph);
	

	ui.m_plot->xAxis->setRange(410, 730);
	ui.m_plot->xAxis->setLabel(QStringLiteral("波长/nm"));
	ui.m_plot->yAxis->setRange(0, 1);
	ui.m_plot->yAxis->setLabel(QStringLiteral("反射率"));

	ui.m_listImg->hide();
}

void SpectrumAnalysisDialog::calculateReflectivity(int x, int y)
{
	m_yPlot.clear();
	x = x << 1;
	y = y << 1;

	for (int i = 0; i < m_sceneMat.size(); ++i)
	{
		double val = m_sceneMat[i].at<unsigned short>(y, x) * 1.0 / m_referenceMat[i].at<unsigned short>(y, x);
		m_yPlot.push_back(val);
	}

	QCPGraph *graph = ui.m_plot->addGraph();
	static int color = 0;
	QPen pen;
	switch (color++ % 8)
	{
		
	case 0:
		graph->setPen(QPen(Qt::red));
		break;
	case 1:
		graph->setPen(QPen(Qt::black));
		break;
	case 2:
		graph->setPen(QPen(Qt::green));
		break;
	case 3:
		graph->setPen(QPen(Qt::blue));
		break;
	case 4:
		graph->setPen(QPen(Qt::cyan));
		break;
	case 5:
		graph->setPen(QPen(Qt::magenta));
		break;
	case 6:
		graph->setPen(QPen(Qt::darkCyan));
		break;
	case 7:
		graph->setPen(QPen(Qt::gray));
		break;
	case 8:
		graph->setPen(QPen(Qt::darkRed));
		break;
	case 9:
		graph->setPen(QPen(Qt::darkGreen));
		break;
	case 10:
		graph->setPen(QPen(Qt::darkBlue));
		break;
	case 11:
		graph->setPen(QPen(Qt::yellow)); 
		break;
	case 12:
		graph->setPen(QPen(Qt::darkMagenta));
		break;
	case 13:
		graph->setPen(QPen(Qt::darkYellow));
		break;
	case 14:
		graph->setPen(QPen(Qt::darkGray));
		break;
	case 15:
		graph->setPen(QPen(Qt::lightGray));
		break;
	default:
		graph->setPen(QPen(Qt::black));
		break;
	}

	graph->setData(m_xPlot, m_yPlot);
	graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
	ui.m_plot->replot();

}

void SpectrumAnalysisDialog::showSelectedImg(QListWidgetItem* item)
{
	QString wavelength = item->text();
	QPixmap pixmap(m_scenePath + "/" + wavelength + ".bmp", ".bmp");
	if (pixmap.isNull())
		ui.m_showLabel->setText(QStringLiteral("该波长预览图片缺失"));
	else
		ui.m_showLabel->setPixmap(pixmap);
}


void SpectrumAnalysisDialog::loadImamges()
{
	ui.m_plot->clearGraphs();
	ui.m_plot->replot();

	//实物图片
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("光谱图片选择"), ".");
	if (path == "")
		return;

	QString pathBackup(m_scenePath);
	m_scenePath = path;

	QDir sceneDir(m_scenePath);
	m_scenePath += '/';
	sceneDir.setNameFilters(QStringList() << "*.png");
	QStringList sceneList = sceneDir.entryList();

	//参考光谱
	QString refPath = QCoreApplication::applicationDirPath();
	refPath += "/reference";
	QDir refDir(refPath);
	refPath += "/";
	refDir.setNameFilters(QStringList() << "*.png");
	QStringList refList = refDir.entryList();

	QStringList showList;
	for (auto ele : sceneList)
	{
		if (refList.contains(ele))
		{
			if (showList.size() == 0)
			{
				m_wavelength.clear();
				m_referenceMat.clear();
				m_sceneMat.clear();
			}
			
			QString wavelen(ele);
			wavelen.remove(".png");
			m_wavelength.push_back(wavelen.toInt());
			showList.push_back(wavelen);
			cv::Mat scene = cv::imread((m_scenePath + ele).toLocal8Bit().toStdString(), cv::IMREAD_ANYDEPTH);
			cv::Mat ref = cv::imread((refPath + ele).toLocal8Bit().toStdString(), cv::IMREAD_ANYDEPTH);
			m_referenceMat.push_back(ref);
			m_sceneMat.push_back(scene);
		}
	}

	if (showList.size() == 0)
	{
		QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("图片集选择不合理，请重新选择"));
		m_scenePath = pathBackup;
		return;
	}
		
	//预览选项
	ui.m_listImg->clear();
	ui.m_listImg->addItems(showList);

	QImage showImg(m_scenePath + "550.bmp", ".bmp");
	if (showImg.isNull())
		ui.m_showLabel->setText(QStringLiteral("该波长预览图片缺失"));
	else
		ui.m_showLabel->setPixmap(QPixmap::fromImage(showImg));

	m_xPlot.clear();
	for (auto ele : showList)
	{
		m_xPlot.push_back(ele.toInt());
	}

	ui.m_listImg->show();

}

void SpectrumAnalysisDialog::clearGraph()
{
	ui.m_plot->clearGraphs();
	ui.m_plot->replot();
}












//void SpectrumAnalysisDialog::loadImamges()
//{
//	ui.m_plot->clearGraphs();
//	ui.m_plot->replot();
//
//	//实物图片
//	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("光谱图片选择"), ".");
//	if (path == "")
//		return;
//	m_scenePath = path;
//	
//	QDir sceneDir(m_scenePath);
//	m_scenePath += '/';
//	sceneDir.setNameFilters(QStringList() << "*.png");
//	QStringList sceneList = sceneDir.entryList();
//
//	m_sceneMat.clear();
//	for (QString ele : sceneList)
//	{
//		m_sceneMat.push_back(cv::imread((m_scenePath + ele).toLocal8Bit().toStdString(), cv::IMREAD_ANYDEPTH));
//	}
//
//	//预览选项
//	QStringList showList = sceneList.replaceInStrings(".png", "");
//	ui.m_listImg->addItems(showList);
//
//	//参考光谱
//	QString refPath = QCoreApplication::applicationDirPath();
//	refPath += "/reference";
//	QDir refDir(refPath);
//	refPath += "/";
//	refDir.setNameFilters(QStringList() << "*.png");
//	QStringList refList = refDir.entryList();
//	
//	for (QString ele : refList)
//	{
//		m_referenceMat.push_back(cv::imread((refPath + ele).toStdString(), cv::IMREAD_ANYDEPTH));
//	}
//
//	
//	QImage showImg(m_scenePath + "550.bmp", ".bmp");
//	ui.m_showLabel->setPixmap(QPixmap::fromImage(showImg));
//}


//void SpectrumAnalysisDialog::calculateReflectivity(int x, int y)
//{
//	m_yPlot.clear();
//	x = x << 1;
//	y = y << 1;
//
//	for (int i = 0; i < m_sceneMat.size(); ++i)
//	{
//		double val = m_sceneMat[i].at<unsigned short>(y, x) * 1.0 / m_referenceMat[i].at<unsigned short>(y, x);
//		m_yPlot.push_back(val);
//	}
//
//	ui.m_plot->addGraph()->setData(m_xPlot, m_yPlot);
//	ui.m_plot->replot();
//	
//}
