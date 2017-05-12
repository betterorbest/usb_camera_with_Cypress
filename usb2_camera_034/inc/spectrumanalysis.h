#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <QtWidgets/QDialog>
#include "ui_spectrumanalysisdialog.h"

#include <vector>
#include <map>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

class SpectrumAnalysisDialog : public QDialog
{
	Q_OBJECT
public:
	SpectrumAnalysisDialog(QWidget* parent = 0);

public slots:
	void loadImamges();
	void calculateReflectivity(int x, int y);
	void showSelectedImg(QListWidgetItem* item);
	void clearGraph();

private:
	Ui::m_spectrumAnalysisDialogClass ui;
	
	std::vector<cv::Mat> m_referenceMat;
	std::vector<cv::Mat> m_sceneMat;

	QVector<double> m_xPlot;
	QVector<double> m_yPlot;

	QString m_scenePath;

	std::vector<int> m_wavelength;
};


#endif