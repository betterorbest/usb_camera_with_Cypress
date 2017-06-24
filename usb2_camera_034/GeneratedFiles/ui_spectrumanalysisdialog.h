/********************************************************************************
** Form generated from reading UI file 'spectrumanalysisdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECTRUMANALYSISDIALOG_H
#define UI_SPECTRUMANALYSISDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include "mylabel.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_m_spectrumAnalysisDialogClass
{
public:
    MyLabel *m_showLabel;
    QCustomPlot *m_plot;
    QPushButton *m_loadImagesButton;
    QListWidget *m_listImg;
    QPushButton *m_clearCurvesButton;

    void setupUi(QDialog *m_spectrumAnalysisDialogClass)
    {
        if (m_spectrumAnalysisDialogClass->objectName().isEmpty())
            m_spectrumAnalysisDialogClass->setObjectName(QStringLiteral("m_spectrumAnalysisDialogClass"));
        m_spectrumAnalysisDialogClass->resize(1381, 690);
        m_showLabel = new MyLabel(m_spectrumAnalysisDialogClass);
        m_showLabel->setObjectName(QStringLiteral("m_showLabel"));
        m_showLabel->setEnabled(true);
        m_showLabel->setGeometry(QRect(30, 80, 640, 480));
        m_showLabel->setFrameShape(QFrame::Box);
        m_showLabel->setFrameShadow(QFrame::Plain);
        m_showLabel->setLineWidth(1);
        m_showLabel->setTextFormat(Qt::AutoText);
        m_showLabel->setAlignment(Qt::AlignCenter);
        m_plot = new QCustomPlot(m_spectrumAnalysisDialogClass);
        m_plot->setObjectName(QStringLiteral("m_plot"));
        m_plot->setGeometry(QRect(700, 80, 640, 480));
        m_plot->setAutoFillBackground(false);
        m_loadImagesButton = new QPushButton(m_spectrumAnalysisDialogClass);
        m_loadImagesButton->setObjectName(QStringLiteral("m_loadImagesButton"));
        m_loadImagesButton->setGeometry(QRect(30, 30, 93, 28));
        m_listImg = new QListWidget(m_spectrumAnalysisDialogClass);
        m_listImg->setObjectName(QStringLiteral("m_listImg"));
        m_listImg->setEnabled(true);
        m_listImg->setGeometry(QRect(30, 580, 641, 61));
        m_listImg->setFlow(QListView::LeftToRight);
        m_listImg->setResizeMode(QListView::Adjust);
        m_listImg->setViewMode(QListView::ListMode);
        m_listImg->setSelectionRectVisible(false);
        m_clearCurvesButton = new QPushButton(m_spectrumAnalysisDialogClass);
        m_clearCurvesButton->setObjectName(QStringLiteral("m_clearCurvesButton"));
        m_clearCurvesButton->setGeometry(QRect(700, 30, 93, 28));

        retranslateUi(m_spectrumAnalysisDialogClass);

        QMetaObject::connectSlotsByName(m_spectrumAnalysisDialogClass);
    } // setupUi

    void retranslateUi(QDialog *m_spectrumAnalysisDialogClass)
    {
        m_spectrumAnalysisDialogClass->setWindowTitle(QApplication::translate("m_spectrumAnalysisDialogClass", "\345\205\211\350\260\261\345\210\206\346\236\220", 0));
        m_showLabel->setText(QApplication::translate("m_spectrumAnalysisDialogClass", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">\346\230\276\347\244\272\345\214\272\345\237\237</span></p></body></html>", 0));
        m_loadImagesButton->setText(QApplication::translate("m_spectrumAnalysisDialogClass", "\350\275\275\345\205\245\345\233\276\347\211\207\351\233\206", 0));
        m_clearCurvesButton->setText(QApplication::translate("m_spectrumAnalysisDialogClass", "\346\270\205\347\251\272\346\233\262\347\272\277", 0));
    } // retranslateUi

};

namespace Ui {
    class m_spectrumAnalysisDialogClass: public Ui_m_spectrumAnalysisDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECTRUMANALYSISDIALOG_H
