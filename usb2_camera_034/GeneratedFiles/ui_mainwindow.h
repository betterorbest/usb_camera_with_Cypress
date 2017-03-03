/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_pauseButton;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_6;
    QPushButton *m_pathChoosingButton;
    QPushButton *m_imageTakingButton;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *m_resolutionSwitching;
    QGroupBox *m_bitsPerPixelChange;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *m_8bitsChoosed;
    QRadioButton *m_12bitsChoosed;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *m_colorImageChoosed;
    QRadioButton *m_grayImageChoosed;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *m_analogGainSet;
    QGroupBox *m_digitalGainSet;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QSlider *m_rGainSet;
    QLabel *m_rGain;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QSlider *m_gGainSet;
    QLabel *m_gGain;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QSlider *m_bGainSet;
    QLabel *m_bGain;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QSlider *m_globalGainSet;
    QLabel *m_globalGain;
    QLabel *label;
    QGroupBox *m_exposureMode;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *m_autoExposure;
    QRadioButton *m_manualExposure;
    QHBoxLayout *horizontalLayout_12;
    QSlider *m_exposureSlider;
    QSpinBox *m_exposureSpinBox;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_receiveRateLabel;
    QLabel *label_4;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QFrame *m_showFrame;
    QGridLayout *gridLayout;
    QLabel *m_showLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(937, 892);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MainWindow/camera.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        MainWindowClass->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid gray;\n"
"    border-radius: 3px;\n"
"	margin-top: 1ex;\n"
"	padding-bottom: 4px;\n"
"	padding-top: 7px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    /*subcontrol-position: top center; /* position at the top center */\n"
"    padding: 0 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #f4f4f4, stop: 1 #f4f4f4);\n"
"}\n"
"\n"
"QGroupBox#groupBox_6 {   /*\345\270\247\347\216\207\344\270\216\346\270\251\345\272\246\347\273\204\350\256\276\347\275\256\346\227\240\350\276\271\346\241\206*/\n"
"	border: none;\n"
"	margin-top: 0;\n"
"	padding-top:0px;\n"
"}\n"
"\n"
"QGroupBox#groupBox_6 {\n"
"	padding: 0 0;\n"
"\n"
"}"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 5, -1, 5);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(250, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(7);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 5, 0);
        m_startButton = new QPushButton(frame);
        m_startButton->setObjectName(QStringLiteral("m_startButton"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        m_startButton->setFont(font);
        m_startButton->setFlat(false);

        verticalLayout->addWidget(m_startButton);

        m_stopButton = new QPushButton(frame);
        m_stopButton->setObjectName(QStringLiteral("m_stopButton"));
        m_stopButton->setEnabled(false);
        m_stopButton->setFont(font);

        verticalLayout->addWidget(m_stopButton);

        m_pauseButton = new QPushButton(frame);
        m_pauseButton->setObjectName(QStringLiteral("m_pauseButton"));
        m_pauseButton->setEnabled(false);
        m_pauseButton->setFont(font);

        verticalLayout->addWidget(m_pauseButton);

        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        QFont font1;
        font1.setFamily(QStringLiteral("Aharoni"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        groupBox_5->setFont(font1);
        verticalLayout_6 = new QVBoxLayout(groupBox_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        m_pathChoosingButton = new QPushButton(groupBox_5);
        m_pathChoosingButton->setObjectName(QStringLiteral("m_pathChoosingButton"));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        m_pathChoosingButton->setFont(font2);

        verticalLayout_6->addWidget(m_pathChoosingButton);

        m_imageTakingButton = new QPushButton(groupBox_5);
        m_imageTakingButton->setObjectName(QStringLiteral("m_imageTakingButton"));
        m_imageTakingButton->setEnabled(false);
        m_imageTakingButton->setFont(font2);

        verticalLayout_6->addWidget(m_imageTakingButton);


        verticalLayout->addWidget(groupBox_5);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_resolutionSwitching = new QComboBox(groupBox);
        m_resolutionSwitching->setObjectName(QStringLiteral("m_resolutionSwitching"));
        m_resolutionSwitching->setEnabled(false);
        m_resolutionSwitching->setFont(font2);
        m_resolutionSwitching->setAutoFillBackground(false);
        m_resolutionSwitching->setEditable(false);

        horizontalLayout_7->addWidget(m_resolutionSwitching);


        verticalLayout->addWidget(groupBox);

        m_bitsPerPixelChange = new QGroupBox(frame);
        m_bitsPerPixelChange->setObjectName(QStringLiteral("m_bitsPerPixelChange"));
        m_bitsPerPixelChange->setEnabled(false);
        m_bitsPerPixelChange->setFont(font);
        m_bitsPerPixelChange->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        m_bitsPerPixelChange->setFlat(false);
        horizontalLayout_4 = new QHBoxLayout(m_bitsPerPixelChange);
        horizontalLayout_4->setSpacing(7);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_8bitsChoosed = new QRadioButton(m_bitsPerPixelChange);
        m_8bitsChoosed->setObjectName(QStringLiteral("m_8bitsChoosed"));
        m_8bitsChoosed->setFont(font2);
        m_8bitsChoosed->setLayoutDirection(Qt::LeftToRight);
        m_8bitsChoosed->setChecked(true);

        horizontalLayout_4->addWidget(m_8bitsChoosed);

        m_12bitsChoosed = new QRadioButton(m_bitsPerPixelChange);
        m_12bitsChoosed->setObjectName(QStringLiteral("m_12bitsChoosed"));
        m_12bitsChoosed->setFont(font2);

        horizontalLayout_4->addWidget(m_12bitsChoosed);


        verticalLayout->addWidget(m_bitsPerPixelChange);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFont(font);
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_colorImageChoosed = new QRadioButton(groupBox_4);
        m_colorImageChoosed->setObjectName(QStringLiteral("m_colorImageChoosed"));
        m_colorImageChoosed->setFont(font2);
        m_colorImageChoosed->setChecked(true);

        horizontalLayout_5->addWidget(m_colorImageChoosed);

        m_grayImageChoosed = new QRadioButton(groupBox_4);
        m_grayImageChoosed->setObjectName(QStringLiteral("m_grayImageChoosed"));
        m_grayImageChoosed->setFont(font2);
        m_grayImageChoosed->setChecked(false);

        horizontalLayout_5->addWidget(m_grayImageChoosed);


        verticalLayout->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setEnabled(true);
        groupBox_3->setFont(font);
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_analogGainSet = new QComboBox(groupBox_3);
        m_analogGainSet->setObjectName(QStringLiteral("m_analogGainSet"));
        m_analogGainSet->setEnabled(false);
        m_analogGainSet->setFont(font2);

        horizontalLayout_6->addWidget(m_analogGainSet);


        verticalLayout->addWidget(groupBox_3);

        m_digitalGainSet = new QGroupBox(frame);
        m_digitalGainSet->setObjectName(QStringLiteral("m_digitalGainSet"));
        m_digitalGainSet->setEnabled(false);
        m_digitalGainSet->setFont(font);
        verticalLayout_3 = new QVBoxLayout(m_digitalGainSet);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_11 = new QLabel(m_digitalGainSet);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font2);

        horizontalLayout_11->addWidget(label_11);

        m_rGainSet = new QSlider(m_digitalGainSet);
        m_rGainSet->setObjectName(QStringLiteral("m_rGainSet"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_rGainSet->sizePolicy().hasHeightForWidth());
        m_rGainSet->setSizePolicy(sizePolicy);
        m_rGainSet->setMaximumSize(QSize(16777215, 16777215));
        m_rGainSet->setMinimum(1);
        m_rGainSet->setMaximum(8);
        m_rGainSet->setPageStep(1);
        m_rGainSet->setOrientation(Qt::Horizontal);
        m_rGainSet->setInvertedAppearance(false);
        m_rGainSet->setInvertedControls(false);
        m_rGainSet->setTickPosition(QSlider::NoTicks);
        m_rGainSet->setTickInterval(1);

        horizontalLayout_11->addWidget(m_rGainSet);

        m_rGain = new QLabel(m_digitalGainSet);
        m_rGain->setObjectName(QStringLiteral("m_rGain"));
        m_rGain->setFont(font2);

        horizontalLayout_11->addWidget(m_rGain);

        label_13 = new QLabel(m_digitalGainSet);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font2);

        horizontalLayout_11->addWidget(label_13);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_8 = new QLabel(m_digitalGainSet);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font2);

        horizontalLayout_10->addWidget(label_8);

        m_gGainSet = new QSlider(m_digitalGainSet);
        m_gGainSet->setObjectName(QStringLiteral("m_gGainSet"));
        sizePolicy.setHeightForWidth(m_gGainSet->sizePolicy().hasHeightForWidth());
        m_gGainSet->setSizePolicy(sizePolicy);
        m_gGainSet->setMaximumSize(QSize(16777215, 16777215));
        m_gGainSet->setMinimum(1);
        m_gGainSet->setMaximum(8);
        m_gGainSet->setPageStep(1);
        m_gGainSet->setOrientation(Qt::Horizontal);
        m_gGainSet->setInvertedAppearance(false);
        m_gGainSet->setInvertedControls(false);
        m_gGainSet->setTickPosition(QSlider::NoTicks);
        m_gGainSet->setTickInterval(1);

        horizontalLayout_10->addWidget(m_gGainSet);

        m_gGain = new QLabel(m_digitalGainSet);
        m_gGain->setObjectName(QStringLiteral("m_gGain"));
        m_gGain->setFont(font2);

        horizontalLayout_10->addWidget(m_gGain);

        label_10 = new QLabel(m_digitalGainSet);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font2);

        horizontalLayout_10->addWidget(label_10);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_5 = new QLabel(m_digitalGainSet);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);

        horizontalLayout_9->addWidget(label_5);

        m_bGainSet = new QSlider(m_digitalGainSet);
        m_bGainSet->setObjectName(QStringLiteral("m_bGainSet"));
        sizePolicy.setHeightForWidth(m_bGainSet->sizePolicy().hasHeightForWidth());
        m_bGainSet->setSizePolicy(sizePolicy);
        m_bGainSet->setMaximumSize(QSize(16777215, 16777215));
        m_bGainSet->setMinimum(1);
        m_bGainSet->setMaximum(8);
        m_bGainSet->setPageStep(1);
        m_bGainSet->setOrientation(Qt::Horizontal);
        m_bGainSet->setInvertedAppearance(false);
        m_bGainSet->setInvertedControls(false);
        m_bGainSet->setTickPosition(QSlider::NoTicks);
        m_bGainSet->setTickInterval(1);

        horizontalLayout_9->addWidget(m_bGainSet);

        m_bGain = new QLabel(m_digitalGainSet);
        m_bGain->setObjectName(QStringLiteral("m_bGain"));
        m_bGain->setFont(font2);

        horizontalLayout_9->addWidget(m_bGain);

        label_7 = new QLabel(m_digitalGainSet);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font2);

        horizontalLayout_9->addWidget(label_7);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(m_digitalGainSet);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font2);

        horizontalLayout_8->addWidget(label_2);

        m_globalGainSet = new QSlider(m_digitalGainSet);
        m_globalGainSet->setObjectName(QStringLiteral("m_globalGainSet"));
        sizePolicy.setHeightForWidth(m_globalGainSet->sizePolicy().hasHeightForWidth());
        m_globalGainSet->setSizePolicy(sizePolicy);
        m_globalGainSet->setMaximumSize(QSize(16777215, 16777215));
        m_globalGainSet->setMinimum(1);
        m_globalGainSet->setMaximum(8);
        m_globalGainSet->setPageStep(1);
        m_globalGainSet->setOrientation(Qt::Horizontal);
        m_globalGainSet->setInvertedAppearance(false);
        m_globalGainSet->setInvertedControls(false);
        m_globalGainSet->setTickPosition(QSlider::NoTicks);
        m_globalGainSet->setTickInterval(1);

        horizontalLayout_8->addWidget(m_globalGainSet);

        m_globalGain = new QLabel(m_digitalGainSet);
        m_globalGain->setObjectName(QStringLiteral("m_globalGain"));
        m_globalGain->setFont(font2);

        horizontalLayout_8->addWidget(m_globalGain);

        label = new QLabel(m_digitalGainSet);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font2);

        horizontalLayout_8->addWidget(label);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout->addWidget(m_digitalGainSet);

        m_exposureMode = new QGroupBox(frame);
        m_exposureMode->setObjectName(QStringLiteral("m_exposureMode"));
        m_exposureMode->setEnabled(false);
        m_exposureMode->setFont(font);
        verticalLayout_4 = new QVBoxLayout(m_exposureMode);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        m_autoExposure = new QRadioButton(m_exposureMode);
        m_autoExposure->setObjectName(QStringLiteral("m_autoExposure"));
        m_autoExposure->setFont(font2);
        m_autoExposure->setChecked(true);

        verticalLayout_4->addWidget(m_autoExposure);

        m_manualExposure = new QRadioButton(m_exposureMode);
        m_manualExposure->setObjectName(QStringLiteral("m_manualExposure"));
        m_manualExposure->setFont(font2);

        verticalLayout_4->addWidget(m_manualExposure);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        m_exposureSlider = new QSlider(m_exposureMode);
        m_exposureSlider->setObjectName(QStringLiteral("m_exposureSlider"));
        m_exposureSlider->setEnabled(false);
        sizePolicy.setHeightForWidth(m_exposureSlider->sizePolicy().hasHeightForWidth());
        m_exposureSlider->setSizePolicy(sizePolicy);
        m_exposureSlider->setMaximumSize(QSize(16777215, 16777215));
        m_exposureSlider->setMinimum(1);
        m_exposureSlider->setMaximum(92);
        m_exposureSlider->setSingleStep(1);
        m_exposureSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_12->addWidget(m_exposureSlider);

        m_exposureSpinBox = new QSpinBox(m_exposureMode);
        m_exposureSpinBox->setObjectName(QStringLiteral("m_exposureSpinBox"));
        m_exposureSpinBox->setEnabled(false);
        m_exposureSpinBox->setFont(font2);
        m_exposureSpinBox->setMinimum(1);
        m_exposureSpinBox->setMaximum(92);

        horizontalLayout_12->addWidget(m_exposureSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_12);


        verticalLayout->addWidget(m_exposureMode);

        groupBox_6 = new QGroupBox(frame);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_6);
        horizontalLayout_13->setSpacing(3);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(groupBox_6);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_receiveRateLabel = new QLabel(groupBox_2);
        m_receiveRateLabel->setObjectName(QStringLiteral("m_receiveRateLabel"));
        m_receiveRateLabel->setLayoutDirection(Qt::LeftToRight);
        m_receiveRateLabel->setTextFormat(Qt::AutoText);
        m_receiveRateLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(m_receiveRateLabel);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);


        horizontalLayout_13->addWidget(groupBox_2);

        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setFont(font);
        horizontalLayout_14 = new QHBoxLayout(groupBox_7);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_6);

        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_14->addWidget(label_3);


        horizontalLayout_13->addWidget(groupBox_7);


        verticalLayout->addWidget(groupBox_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(frame);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(4);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_showFrame = new QFrame(frame_2);
        m_showFrame->setObjectName(QStringLiteral("m_showFrame"));
        m_showFrame->setStyleSheet(QStringLiteral("background-color: rgb(130, 130, 130)"));
        m_showFrame->setFrameShape(QFrame::StyledPanel);
        m_showFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(m_showFrame);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        m_showLabel = new QLabel(m_showFrame);
        m_showLabel->setObjectName(QStringLiteral("m_showLabel"));
        m_showLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_showLabel, 0, 0, 1, 1);


        horizontalLayout->addWidget(m_showFrame);

        horizontalSpacer_2 = new QSpacerItem(38, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 824, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_3->addWidget(frame_2);

        MainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        m_resolutionSwitching->setCurrentIndex(2);
        m_analogGainSet->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "CMOS\346\225\260\345\255\227\347\233\270\346\234\272\346\265\213\350\257\225\350\275\257\344\273\266", 0));
        m_startButton->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\347\233\270\346\234\272", 0));
        m_stopButton->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255\347\233\270\346\234\272", 0));
        m_pauseButton->setText(QApplication::translate("MainWindowClass", "\346\232\202\345\201\234", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230", 0));
        m_pathChoosingButton->setText(QApplication::translate("MainWindowClass", "\351\200\211\346\213\251\345\255\230\345\202\250\350\267\257\345\276\204", 0));
        m_imageTakingButton->setText(QApplication::translate("MainWindowClass", "\346\213\215\347\205\247", 0));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "\345\210\206\350\276\250\347\216\207", 0));
        m_resolutionSwitching->clear();
        m_resolutionSwitching->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "320 * 240", 0)
         << QApplication::translate("MainWindowClass", "640 * 480", 0)
         << QApplication::translate("MainWindowClass", "1280 * 960", 0)
        );
        m_bitsPerPixelChange->setTitle(QApplication::translate("MainWindowClass", "\345\233\276\345\203\217\344\275\215\345\256\275", 0));
        m_8bitsChoosed->setText(QApplication::translate("MainWindowClass", "8\344\275\215", 0));
        m_12bitsChoosed->setText(QApplication::translate("MainWindowClass", "12\344\275\215", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindowClass", "\346\210\220\345\203\217\347\261\273\345\236\213", 0));
        m_colorImageChoosed->setText(QApplication::translate("MainWindowClass", "\345\275\251\350\211\262", 0));
        m_grayImageChoosed->setText(QApplication::translate("MainWindowClass", "\351\273\221\347\231\275", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindowClass", "\346\250\241\346\213\237\345\242\236\347\233\212", 0));
        m_analogGainSet->clear();
        m_analogGainSet->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "1\345\200\215", 0)
         << QApplication::translate("MainWindowClass", "2\345\200\215", 0)
         << QApplication::translate("MainWindowClass", "4\345\200\215", 0)
         << QApplication::translate("MainWindowClass", "8\345\200\215", 0)
         << QApplication::translate("MainWindowClass", "10\345\200\215", 0)
        );
        m_digitalGainSet->setTitle(QApplication::translate("MainWindowClass", "\346\225\260\345\255\227\345\242\236\347\233\212", 0));
        label_11->setText(QApplication::translate("MainWindowClass", "\347\272\242\350\211\262", 0));
        m_rGain->setText(QApplication::translate("MainWindowClass", "1", 0));
        label_13->setText(QApplication::translate("MainWindowClass", "x", 0));
        label_8->setText(QApplication::translate("MainWindowClass", "\347\273\277\350\211\262", 0));
        m_gGain->setText(QApplication::translate("MainWindowClass", "1", 0));
        label_10->setText(QApplication::translate("MainWindowClass", "x", 0));
        label_5->setText(QApplication::translate("MainWindowClass", "\350\223\235\350\211\262", 0));
        m_bGain->setText(QApplication::translate("MainWindowClass", "1", 0));
        label_7->setText(QApplication::translate("MainWindowClass", "x", 0));
        label_2->setText(QApplication::translate("MainWindowClass", "\345\205\250\345\261\200", 0));
        m_globalGain->setText(QApplication::translate("MainWindowClass", "1", 0));
        label->setText(QApplication::translate("MainWindowClass", "x", 0));
        m_exposureMode->setTitle(QApplication::translate("MainWindowClass", "\346\233\235\345\205\211\350\256\276\347\275\256", 0));
        m_autoExposure->setText(QApplication::translate("MainWindowClass", "\350\207\252\345\212\250", 0));
        m_manualExposure->setText(QApplication::translate("MainWindowClass", "\346\211\213\345\212\250(\346\233\235\345\205\211\345\200\274)", 0));
        groupBox_6->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindowClass", "\345\270\247\347\216\207", 0));
        m_receiveRateLabel->setText(QApplication::translate("MainWindowClass", "0", 0));
        label_4->setText(QApplication::translate("MainWindowClass", "fps", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindowClass", "\346\270\251\345\272\246", 0));
        label_6->setText(QApplication::translate("MainWindowClass", "0", 0));
        label_3->setText(QApplication::translate("MainWindowClass", "\342\204\203", 0));
        m_showLabel->setText(QApplication::translate("MainWindowClass", "\346\230\276\347\244\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
