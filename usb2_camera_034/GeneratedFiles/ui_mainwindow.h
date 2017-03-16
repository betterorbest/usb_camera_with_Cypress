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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *m_visibleDisplay;
    QSpacerItem *verticalSpacer_2;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QLabel *m_infraDisplay;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *m_colorImageChoosed;
    QRadioButton *m_grayImageChoosed;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *m_receiveRateLabel;
    QLabel *label_4;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_6;
    QLabel *label_3;
    QPushButton *m_pauseButton;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_6;
    QPushButton *m_pathChoosingButton;
    QPushButton *m_imageTakingButton;
    QPushButton *m_stopButton;
    QPushButton *m_startButton;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QRadioButton *m_infraGray;
    QRadioButton *m_infraGrayInverse;
    QRadioButton *m_infraMetal;
    QRadioButton *m_infraRainbow;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(1366, 703);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MainWindow/camera.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(16777215, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        m_visibleDisplay = new QLabel(frame);
        m_visibleDisplay->setObjectName(QStringLiteral("m_visibleDisplay"));
        m_visibleDisplay->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(m_visibleDisplay, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Sunken);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        m_infraDisplay = new QLabel(frame_3);
        m_infraDisplay->setObjectName(QStringLiteral("m_infraDisplay"));
        m_infraDisplay->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(m_infraDisplay, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


        verticalLayout->addWidget(frame_3);

        verticalSpacer = new QSpacerItem(20, 414, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_4 = new QGroupBox(frame_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        horizontalLayout_5 = new QHBoxLayout(groupBox_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_colorImageChoosed = new QRadioButton(groupBox_4);
        m_colorImageChoosed->setObjectName(QStringLiteral("m_colorImageChoosed"));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        m_colorImageChoosed->setFont(font);
        m_colorImageChoosed->setChecked(true);

        horizontalLayout_5->addWidget(m_colorImageChoosed);

        m_grayImageChoosed = new QRadioButton(groupBox_4);
        m_grayImageChoosed->setObjectName(QStringLiteral("m_grayImageChoosed"));
        m_grayImageChoosed->setFont(font);
        m_grayImageChoosed->setChecked(false);

        horizontalLayout_5->addWidget(m_grayImageChoosed);


        gridLayout_3->addWidget(groupBox_4, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
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


        gridLayout_3->addWidget(groupBox_2, 3, 2, 1, 1);

        groupBox_7 = new QGroupBox(frame_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
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


        gridLayout_3->addWidget(groupBox_7, 3, 3, 1, 1);

        m_pauseButton = new QPushButton(frame_2);
        m_pauseButton->setObjectName(QStringLiteral("m_pauseButton"));
        m_pauseButton->setEnabled(false);

        gridLayout_3->addWidget(m_pauseButton, 1, 1, 1, 1);

        groupBox_5 = new QGroupBox(frame_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_6 = new QVBoxLayout(groupBox_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        m_pathChoosingButton = new QPushButton(groupBox_5);
        m_pathChoosingButton->setObjectName(QStringLiteral("m_pathChoosingButton"));
        m_pathChoosingButton->setFont(font);

        verticalLayout_6->addWidget(m_pathChoosingButton);

        m_imageTakingButton = new QPushButton(groupBox_5);
        m_imageTakingButton->setObjectName(QStringLiteral("m_imageTakingButton"));
        m_imageTakingButton->setEnabled(false);
        m_imageTakingButton->setFont(font);

        verticalLayout_6->addWidget(m_imageTakingButton);


        gridLayout_3->addWidget(groupBox_5, 3, 0, 1, 1);

        m_stopButton = new QPushButton(frame_2);
        m_stopButton->setObjectName(QStringLiteral("m_stopButton"));
        m_stopButton->setEnabled(false);

        gridLayout_3->addWidget(m_stopButton, 1, 2, 1, 1);

        m_startButton = new QPushButton(frame_2);
        m_startButton->setObjectName(QStringLiteral("m_startButton"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        m_startButton->setFont(font1);
        m_startButton->setFlat(false);

        gridLayout_3->addWidget(m_startButton, 1, 0, 1, 1);

        groupBox = new QGroupBox(frame_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        m_infraGray = new QRadioButton(groupBox);
        m_infraGray->setObjectName(QStringLiteral("m_infraGray"));

        gridLayout_4->addWidget(m_infraGray, 0, 0, 1, 1);

        m_infraGrayInverse = new QRadioButton(groupBox);
        m_infraGrayInverse->setObjectName(QStringLiteral("m_infraGrayInverse"));

        gridLayout_4->addWidget(m_infraGrayInverse, 0, 1, 1, 1);

        m_infraMetal = new QRadioButton(groupBox);
        m_infraMetal->setObjectName(QStringLiteral("m_infraMetal"));
        m_infraMetal->setChecked(true);

        gridLayout_4->addWidget(m_infraMetal, 0, 2, 1, 1);

        m_infraRainbow = new QRadioButton(groupBox);
        m_infraRainbow->setObjectName(QStringLiteral("m_infraRainbow"));

        gridLayout_4->addWidget(m_infraRainbow, 0, 3, 1, 1);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 4);


        verticalLayout->addLayout(gridLayout_3);


        horizontalLayout->addWidget(frame_2);

        MainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "CMOS\346\225\260\345\255\227\347\233\270\346\234\272\346\265\213\350\257\225\350\275\257\344\273\266", 0));
        m_visibleDisplay->setText(QApplication::translate("MainWindowClass", "\345\217\257\350\247\201\345\205\211", 0));
        m_infraDisplay->setText(QApplication::translate("MainWindowClass", "\347\272\242\345\244\226", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindowClass", "\345\217\257\350\247\201\345\205\211\351\242\234\350\211\262", 0));
        m_colorImageChoosed->setText(QApplication::translate("MainWindowClass", "\345\275\251\350\211\262", 0));
        m_grayImageChoosed->setText(QApplication::translate("MainWindowClass", "\351\273\221\347\231\275", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindowClass", "\345\270\247\347\216\207", 0));
        m_receiveRateLabel->setText(QApplication::translate("MainWindowClass", "0", 0));
        label_4->setText(QApplication::translate("MainWindowClass", "fps", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindowClass", "\346\270\251\345\272\246", 0));
        label_6->setText(QApplication::translate("MainWindowClass", "0", 0));
        label_3->setText(QApplication::translate("MainWindowClass", "\342\204\203", 0));
        m_pauseButton->setText(QApplication::translate("MainWindowClass", "\346\232\202\345\201\234", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindowClass", "\344\277\235\345\255\230", 0));
        m_pathChoosingButton->setText(QApplication::translate("MainWindowClass", "\351\200\211\346\213\251\345\255\230\345\202\250\350\267\257\345\276\204", 0));
        m_imageTakingButton->setText(QApplication::translate("MainWindowClass", "\346\213\215\347\205\247", 0));
        m_stopButton->setText(QApplication::translate("MainWindowClass", "\345\205\263\351\227\255\347\233\270\346\234\272", 0));
        m_startButton->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\347\233\270\346\234\272", 0));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "\347\272\242\345\244\226\346\230\276\347\244\272", 0));
        m_infraGray->setText(QApplication::translate("MainWindowClass", "\347\201\260\345\272\246", 0));
        m_infraGrayInverse->setText(QApplication::translate("MainWindowClass", "\347\201\260\345\272\246\345\217\215\350\275\254", 0));
        m_infraMetal->setText(QApplication::translate("MainWindowClass", "\347\203\255\351\207\221\345\261\236", 0));
        m_infraRainbow->setText(QApplication::translate("MainWindowClass", "\345\275\251\350\231\271", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
