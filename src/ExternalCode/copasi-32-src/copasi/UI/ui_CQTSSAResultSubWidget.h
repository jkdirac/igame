/*
 All rights reserved. 
*/

/********************************************************************************
** Form generated from reading UI file 'CQTSSAResultSubWidget.ui'
**
** Created: Thu Oct 14 14:44:36 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CQTSSARESULTSUBWIDGET_H
#define UI_CQTSSARESULTSUBWIDGET_H

#include <Qt3Support/Q3Frame>
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "CQArrayAnnotationsWidget.h"
#include "CTimeSeriesTable.h"
#include "copasiWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQTSSAResultSubWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mpLblResult;
    QPushButton *ButtonSaveData;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *spacer;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget2;
    QWidget *tab;
    QVBoxLayout *vboxLayout;
    Q3TextEdit *optimizationResultText;
    QWidget *tab1;
    QVBoxLayout *vboxLayout1;
    CTimeSeriesTable *dataTable;
    QWidget *TabPage_ILDM;
    QGridLayout *gridLayout;
    QSlider *mSlider;
    QSpacerItem *mSpacer;
    QLabel *mLabel7;
    QLabel *pLabel1;
    QLabel *mLabel2;
    QLabel *mLabel3;
    QLabel *mLabel4;
    QLabel *mLabel5;
    QLabel *mLabel6;
    QTabWidget *mTabWidget;
    QWidget *tab2;
    QGridLayout *gridLayout1;
    CQArrayAnnotationsWidget *pArrayWidget;
    QWidget *tab3;
    QGridLayout *gridLayout2;
    CQArrayAnnotationsWidget *pArrayWidget2;
    QWidget *TabPage;
    QGridLayout *gridLayout3;
    CQArrayAnnotationsWidget *pArrayWidget3;
    QWidget *TabPage1;
    QGridLayout *gridLayout4;
    CQArrayAnnotationsWidget *pArrayWidget4;
    QWidget *TabPage2;
    QGridLayout *gridLayout5;
    CQArrayAnnotationsWidget *pArrayWidget_3_2;
    QWidget *TabPage3;
    QGridLayout *gridLayout6;
    CQArrayAnnotationsWidget *pArrayWidgetTMP1;
    QWidget *TabPage4;
    QGridLayout *gridLayout7;
    CQArrayAnnotationsWidget *pArrayWidgetTMP2;
    QWidget *TabPage5;
    QGridLayout *gridLayout8;
    CQArrayAnnotationsWidget *pArrayWidgetTMP3;
    QWidget *TabPage_ILDMM;
    QGridLayout *gridLayout9;
    QLabel *pLabel1_6;
    QLabel *mLabel6_6;
    QLabel *mLabel4_6;
    QLabel *mLabel2_6;
    QLabel *mLabel3_6;
    QSpacerItem *mSpacer_6;
    QLabel *mLabel5_6;
    QSlider *mSlider_4;
    QTabWidget *mTabWidget_4;
    QWidget *tab4;
    QGridLayout *gridLayout10;
    CQArrayAnnotationsWidget *pArrayWidget_5;
    QWidget *tab5;
    QGridLayout *gridLayout11;
    CQArrayAnnotationsWidget *pArrayWidget2_5;
    QWidget *TabPage6;
    QGridLayout *gridLayout12;
    CQArrayAnnotationsWidget *pArrayWidget3_5;
    QWidget *TabPage7;
    QGridLayout *gridLayout13;
    CQArrayAnnotationsWidget *pArrayWidget4_5;
    QWidget *TabPage_CSP;
    QGridLayout *gridLayout14;
    QTabWidget *mTabWidget_3;
    QWidget *tab6;
    QGridLayout *gridLayout15;
    CQArrayAnnotationsWidget *pArrayWidget_3;
    QWidget *tab7;
    QGridLayout *gridLayout16;
    CQArrayAnnotationsWidget *pArrayWidget2_3;
    QWidget *TabPage8;
    QGridLayout *gridLayout17;
    CQArrayAnnotationsWidget *pArrayWidget3_3;
    QWidget *TabPage9;
    QGridLayout *gridLayout18;
    CQArrayAnnotationsWidget *pArrayWidget4_3;
    QWidget *TabPage10;
    QGridLayout *gridLayout19;
    CQArrayAnnotationsWidget *pArrayWidgetNPIr;
    QWidget *TabPage11;
    QGridLayout *gridLayout20;
    CQArrayAnnotationsWidget *pArrayWidgetNPIc;
    QWidget *TabPage12;
    QGridLayout *gridLayout21;
    CQArrayAnnotationsWidget *pArrayWidget4_3_2;
    QWidget *TabPage13;
    QGridLayout *gridLayout22;
    CQArrayAnnotationsWidget *pArrayWidgetNIIr;
    QLabel *pLabel1_3;
    QLabel *mLabel2_3;
    QLabel *mLabel3_3;
    QLabel *mLabel4_3;
    QLabel *mLabel5_3;
    QLabel *mLabel6_3;
    QSpacerItem *mSpacer_3;
    QSlider *mSlider_3;

    void setupUi(CopasiWidget *CQTSSAResultSubWidget)
    {
        if (CQTSSAResultSubWidget->objectName().isEmpty())
            CQTSSAResultSubWidget->setObjectName(QString::fromUtf8("CQTSSAResultSubWidget"));
        CQTSSAResultSubWidget->resize(612, 473);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CQTSSAResultSubWidget->sizePolicy().hasHeightForWidth());
        CQTSSAResultSubWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(CQTSSAResultSubWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mpLblResult = new QLabel(CQTSSAResultSubWidget);
        mpLblResult->setObjectName(QString::fromUtf8("mpLblResult"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mpLblResult->sizePolicy().hasHeightForWidth());
        mpLblResult->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(mpLblResult);

        ButtonSaveData = new QPushButton(CQTSSAResultSubWidget);
        ButtonSaveData->setObjectName(QString::fromUtf8("ButtonSaveData"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ButtonSaveData->sizePolicy().hasHeightForWidth());
        ButtonSaveData->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(ButtonSaveData);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(CQTSSAResultSubWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboBox);

        spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tabWidget2 = new QTabWidget(CQTSSAResultSubWidget);
        tabWidget2->setObjectName(QString::fromUtf8("tabWidget2"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget2->sizePolicy().hasHeightForWidth());
        tabWidget2->setSizePolicy(sizePolicy3);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        vboxLayout = new QVBoxLayout(tab);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        optimizationResultText = new Q3TextEdit(tab);
        optimizationResultText->setObjectName(QString::fromUtf8("optimizationResultText"));
        optimizationResultText->setReadOnly(true);

        vboxLayout->addWidget(optimizationResultText);

        tabWidget2->addTab(tab, QString());
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        vboxLayout1 = new QVBoxLayout(tab1);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(11, 11, 11, 11);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        dataTable = new CTimeSeriesTable(tab1);
        dataTable->setObjectName(QString::fromUtf8("dataTable"));

        vboxLayout1->addWidget(dataTable);

        tabWidget2->addTab(tab1, QString());
        TabPage_ILDM = new QWidget();
        TabPage_ILDM->setObjectName(QString::fromUtf8("TabPage_ILDM"));
        gridLayout = new QGridLayout(TabPage_ILDM);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mSlider = new QSlider(TabPage_ILDM);
        mSlider->setObjectName(QString::fromUtf8("mSlider"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(mSlider->sizePolicy().hasHeightForWidth());
        mSlider->setSizePolicy(sizePolicy4);
        mSlider->setMouseTracking(true);
        mSlider->setAcceptDrops(true);
        mSlider->setMaximum(0);
        mSlider->setPageStep(1);
        mSlider->setTracking(true);
        mSlider->setOrientation(Qt::Horizontal);
        mSlider->setTickPosition(QSlider::NoTicks);
        mSlider->setTickInterval(1);

        gridLayout->addWidget(mSlider, 1, 0, 1, 8);

        mSpacer = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(mSpacer, 0, 7, 1, 1);

        mLabel7 = new QLabel(TabPage_ILDM);
        mLabel7->setObjectName(QString::fromUtf8("mLabel7"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(mLabel7->sizePolicy().hasHeightForWidth());
        mLabel7->setSizePolicy(sizePolicy5);
        mLabel7->setWordWrap(false);

        gridLayout->addWidget(mLabel7, 0, 2, 1, 1);

        pLabel1 = new QLabel(TabPage_ILDM);
        pLabel1->setObjectName(QString::fromUtf8("pLabel1"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pLabel1->sizePolicy().hasHeightForWidth());
        pLabel1->setSizePolicy(sizePolicy6);
        pLabel1->setWordWrap(false);

        gridLayout->addWidget(pLabel1, 0, 0, 1, 1);

        mLabel2 = new QLabel(TabPage_ILDM);
        mLabel2->setObjectName(QString::fromUtf8("mLabel2"));
        sizePolicy5.setHeightForWidth(mLabel2->sizePolicy().hasHeightForWidth());
        mLabel2->setSizePolicy(sizePolicy5);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        mLabel2->setFont(font);
        mLabel2->setWordWrap(false);

        gridLayout->addWidget(mLabel2, 0, 1, 1, 1);

        mLabel3 = new QLabel(TabPage_ILDM);
        mLabel3->setObjectName(QString::fromUtf8("mLabel3"));
        sizePolicy6.setHeightForWidth(mLabel3->sizePolicy().hasHeightForWidth());
        mLabel3->setSizePolicy(sizePolicy6);
        mLabel3->setWordWrap(false);

        gridLayout->addWidget(mLabel3, 0, 3, 1, 1);

        mLabel4 = new QLabel(TabPage_ILDM);
        mLabel4->setObjectName(QString::fromUtf8("mLabel4"));
        sizePolicy5.setHeightForWidth(mLabel4->sizePolicy().hasHeightForWidth());
        mLabel4->setSizePolicy(sizePolicy5);
        mLabel4->setFont(font);
        mLabel4->setWordWrap(false);

        gridLayout->addWidget(mLabel4, 0, 4, 1, 1);

        mLabel5 = new QLabel(TabPage_ILDM);
        mLabel5->setObjectName(QString::fromUtf8("mLabel5"));
        sizePolicy6.setHeightForWidth(mLabel5->sizePolicy().hasHeightForWidth());
        mLabel5->setSizePolicy(sizePolicy6);
        mLabel5->setWordWrap(false);

        gridLayout->addWidget(mLabel5, 0, 5, 1, 1);

        mLabel6 = new QLabel(TabPage_ILDM);
        mLabel6->setObjectName(QString::fromUtf8("mLabel6"));
        sizePolicy5.setHeightForWidth(mLabel6->sizePolicy().hasHeightForWidth());
        mLabel6->setSizePolicy(sizePolicy5);
        mLabel6->setWordWrap(false);

        gridLayout->addWidget(mLabel6, 0, 6, 1, 1);

        mTabWidget = new QTabWidget(TabPage_ILDM);
        mTabWidget->setObjectName(QString::fromUtf8("mTabWidget"));
        sizePolicy3.setHeightForWidth(mTabWidget->sizePolicy().hasHeightForWidth());
        mTabWidget->setSizePolicy(sizePolicy3);
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        gridLayout1 = new QGridLayout(tab2);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        pArrayWidget = new CQArrayAnnotationsWidget(tab2);
        pArrayWidget->setObjectName(QString::fromUtf8("pArrayWidget"));

        gridLayout1->addWidget(pArrayWidget, 0, 0, 1, 1);

        mTabWidget->addTab(tab2, QString());
        tab3 = new QWidget();
        tab3->setObjectName(QString::fromUtf8("tab3"));
        gridLayout2 = new QGridLayout(tab3);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        pArrayWidget2 = new CQArrayAnnotationsWidget(tab3);
        pArrayWidget2->setObjectName(QString::fromUtf8("pArrayWidget2"));

        gridLayout2->addWidget(pArrayWidget2, 0, 0, 1, 1);

        mTabWidget->addTab(tab3, QString());
        TabPage = new QWidget();
        TabPage->setObjectName(QString::fromUtf8("TabPage"));
        gridLayout3 = new QGridLayout(TabPage);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        pArrayWidget3 = new CQArrayAnnotationsWidget(TabPage);
        pArrayWidget3->setObjectName(QString::fromUtf8("pArrayWidget3"));

        gridLayout3->addWidget(pArrayWidget3, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage, QString());
        TabPage1 = new QWidget();
        TabPage1->setObjectName(QString::fromUtf8("TabPage1"));
        gridLayout4 = new QGridLayout(TabPage1);
        gridLayout4->setSpacing(6);
        gridLayout4->setContentsMargins(11, 11, 11, 11);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        pArrayWidget4 = new CQArrayAnnotationsWidget(TabPage1);
        pArrayWidget4->setObjectName(QString::fromUtf8("pArrayWidget4"));

        gridLayout4->addWidget(pArrayWidget4, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage1, QString());
        TabPage2 = new QWidget();
        TabPage2->setObjectName(QString::fromUtf8("TabPage2"));
        gridLayout5 = new QGridLayout(TabPage2);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        pArrayWidget_3_2 = new CQArrayAnnotationsWidget(TabPage2);
        pArrayWidget_3_2->setObjectName(QString::fromUtf8("pArrayWidget_3_2"));

        gridLayout5->addWidget(pArrayWidget_3_2, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage2, QString());
        TabPage3 = new QWidget();
        TabPage3->setObjectName(QString::fromUtf8("TabPage3"));
        gridLayout6 = new QGridLayout(TabPage3);
        gridLayout6->setSpacing(6);
        gridLayout6->setContentsMargins(11, 11, 11, 11);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        pArrayWidgetTMP1 = new CQArrayAnnotationsWidget(TabPage3);
        pArrayWidgetTMP1->setObjectName(QString::fromUtf8("pArrayWidgetTMP1"));

        gridLayout6->addWidget(pArrayWidgetTMP1, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage3, QString());
        TabPage4 = new QWidget();
        TabPage4->setObjectName(QString::fromUtf8("TabPage4"));
        gridLayout7 = new QGridLayout(TabPage4);
        gridLayout7->setSpacing(6);
        gridLayout7->setContentsMargins(11, 11, 11, 11);
        gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
        pArrayWidgetTMP2 = new CQArrayAnnotationsWidget(TabPage4);
        pArrayWidgetTMP2->setObjectName(QString::fromUtf8("pArrayWidgetTMP2"));

        gridLayout7->addWidget(pArrayWidgetTMP2, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage4, QString());
        TabPage5 = new QWidget();
        TabPage5->setObjectName(QString::fromUtf8("TabPage5"));
        gridLayout8 = new QGridLayout(TabPage5);
        gridLayout8->setSpacing(6);
        gridLayout8->setContentsMargins(11, 11, 11, 11);
        gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
        pArrayWidgetTMP3 = new CQArrayAnnotationsWidget(TabPage5);
        pArrayWidgetTMP3->setObjectName(QString::fromUtf8("pArrayWidgetTMP3"));

        gridLayout8->addWidget(pArrayWidgetTMP3, 0, 0, 1, 1);

        mTabWidget->addTab(TabPage5, QString());

        gridLayout->addWidget(mTabWidget, 2, 0, 1, 8);

        tabWidget2->addTab(TabPage_ILDM, QString());
        TabPage_ILDMM = new QWidget();
        TabPage_ILDMM->setObjectName(QString::fromUtf8("TabPage_ILDMM"));
        gridLayout9 = new QGridLayout(TabPage_ILDMM);
        gridLayout9->setSpacing(6);
        gridLayout9->setContentsMargins(11, 11, 11, 11);
        gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
        pLabel1_6 = new QLabel(TabPage_ILDMM);
        pLabel1_6->setObjectName(QString::fromUtf8("pLabel1_6"));
        sizePolicy6.setHeightForWidth(pLabel1_6->sizePolicy().hasHeightForWidth());
        pLabel1_6->setSizePolicy(sizePolicy6);
        pLabel1_6->setWordWrap(false);

        gridLayout9->addWidget(pLabel1_6, 0, 0, 1, 1);

        mLabel6_6 = new QLabel(TabPage_ILDMM);
        mLabel6_6->setObjectName(QString::fromUtf8("mLabel6_6"));
        sizePolicy5.setHeightForWidth(mLabel6_6->sizePolicy().hasHeightForWidth());
        mLabel6_6->setSizePolicy(sizePolicy5);
        mLabel6_6->setWordWrap(false);

        gridLayout9->addWidget(mLabel6_6, 0, 5, 1, 1);

        mLabel4_6 = new QLabel(TabPage_ILDMM);
        mLabel4_6->setObjectName(QString::fromUtf8("mLabel4_6"));
        sizePolicy5.setHeightForWidth(mLabel4_6->sizePolicy().hasHeightForWidth());
        mLabel4_6->setSizePolicy(sizePolicy5);
        mLabel4_6->setFont(font);
        mLabel4_6->setWordWrap(false);

        gridLayout9->addWidget(mLabel4_6, 0, 3, 1, 1);

        mLabel2_6 = new QLabel(TabPage_ILDMM);
        mLabel2_6->setObjectName(QString::fromUtf8("mLabel2_6"));
        sizePolicy5.setHeightForWidth(mLabel2_6->sizePolicy().hasHeightForWidth());
        mLabel2_6->setSizePolicy(sizePolicy5);
        mLabel2_6->setFont(font);
        mLabel2_6->setWordWrap(false);

        gridLayout9->addWidget(mLabel2_6, 0, 1, 1, 1);

        mLabel3_6 = new QLabel(TabPage_ILDMM);
        mLabel3_6->setObjectName(QString::fromUtf8("mLabel3_6"));
        sizePolicy6.setHeightForWidth(mLabel3_6->sizePolicy().hasHeightForWidth());
        mLabel3_6->setSizePolicy(sizePolicy6);
        mLabel3_6->setWordWrap(false);

        gridLayout9->addWidget(mLabel3_6, 0, 2, 1, 1);

        mSpacer_6 = new QSpacerItem(309, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout9->addItem(mSpacer_6, 0, 6, 1, 1);

        mLabel5_6 = new QLabel(TabPage_ILDMM);
        mLabel5_6->setObjectName(QString::fromUtf8("mLabel5_6"));
        sizePolicy6.setHeightForWidth(mLabel5_6->sizePolicy().hasHeightForWidth());
        mLabel5_6->setSizePolicy(sizePolicy6);
        mLabel5_6->setWordWrap(false);

        gridLayout9->addWidget(mLabel5_6, 0, 4, 1, 1);

        mSlider_4 = new QSlider(TabPage_ILDMM);
        mSlider_4->setObjectName(QString::fromUtf8("mSlider_4"));
        sizePolicy4.setHeightForWidth(mSlider_4->sizePolicy().hasHeightForWidth());
        mSlider_4->setSizePolicy(sizePolicy4);
        mSlider_4->setMouseTracking(true);
        mSlider_4->setAcceptDrops(true);
        mSlider_4->setMaximum(0);
        mSlider_4->setPageStep(1);
        mSlider_4->setTracking(true);
        mSlider_4->setOrientation(Qt::Horizontal);
        mSlider_4->setTickPosition(QSlider::NoTicks);
        mSlider_4->setTickInterval(1);

        gridLayout9->addWidget(mSlider_4, 1, 0, 1, 7);

        mTabWidget_4 = new QTabWidget(TabPage_ILDMM);
        mTabWidget_4->setObjectName(QString::fromUtf8("mTabWidget_4"));
        tab4 = new QWidget();
        tab4->setObjectName(QString::fromUtf8("tab4"));
        gridLayout10 = new QGridLayout(tab4);
        gridLayout10->setSpacing(6);
        gridLayout10->setContentsMargins(11, 11, 11, 11);
        gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
        pArrayWidget_5 = new CQArrayAnnotationsWidget(tab4);
        pArrayWidget_5->setObjectName(QString::fromUtf8("pArrayWidget_5"));

        gridLayout10->addWidget(pArrayWidget_5, 0, 0, 1, 1);

        mTabWidget_4->addTab(tab4, QString());
        tab5 = new QWidget();
        tab5->setObjectName(QString::fromUtf8("tab5"));
        gridLayout11 = new QGridLayout(tab5);
        gridLayout11->setSpacing(6);
        gridLayout11->setContentsMargins(11, 11, 11, 11);
        gridLayout11->setObjectName(QString::fromUtf8("gridLayout11"));
        pArrayWidget2_5 = new CQArrayAnnotationsWidget(tab5);
        pArrayWidget2_5->setObjectName(QString::fromUtf8("pArrayWidget2_5"));

        gridLayout11->addWidget(pArrayWidget2_5, 0, 0, 1, 1);

        mTabWidget_4->addTab(tab5, QString());
        TabPage6 = new QWidget();
        TabPage6->setObjectName(QString::fromUtf8("TabPage6"));
        gridLayout12 = new QGridLayout(TabPage6);
        gridLayout12->setSpacing(6);
        gridLayout12->setContentsMargins(11, 11, 11, 11);
        gridLayout12->setObjectName(QString::fromUtf8("gridLayout12"));
        pArrayWidget3_5 = new CQArrayAnnotationsWidget(TabPage6);
        pArrayWidget3_5->setObjectName(QString::fromUtf8("pArrayWidget3_5"));

        gridLayout12->addWidget(pArrayWidget3_5, 0, 0, 1, 1);

        mTabWidget_4->addTab(TabPage6, QString());
        TabPage7 = new QWidget();
        TabPage7->setObjectName(QString::fromUtf8("TabPage7"));
        gridLayout13 = new QGridLayout(TabPage7);
        gridLayout13->setSpacing(6);
        gridLayout13->setContentsMargins(11, 11, 11, 11);
        gridLayout13->setObjectName(QString::fromUtf8("gridLayout13"));
        pArrayWidget4_5 = new CQArrayAnnotationsWidget(TabPage7);
        pArrayWidget4_5->setObjectName(QString::fromUtf8("pArrayWidget4_5"));

        gridLayout13->addWidget(pArrayWidget4_5, 0, 0, 1, 1);

        mTabWidget_4->addTab(TabPage7, QString());

        gridLayout9->addWidget(mTabWidget_4, 2, 0, 1, 7);

        tabWidget2->addTab(TabPage_ILDMM, QString());
        TabPage_CSP = new QWidget();
        TabPage_CSP->setObjectName(QString::fromUtf8("TabPage_CSP"));
        gridLayout14 = new QGridLayout(TabPage_CSP);
        gridLayout14->setSpacing(6);
        gridLayout14->setContentsMargins(11, 11, 11, 11);
        gridLayout14->setObjectName(QString::fromUtf8("gridLayout14"));
        mTabWidget_3 = new QTabWidget(TabPage_CSP);
        mTabWidget_3->setObjectName(QString::fromUtf8("mTabWidget_3"));
        sizePolicy3.setHeightForWidth(mTabWidget_3->sizePolicy().hasHeightForWidth());
        mTabWidget_3->setSizePolicy(sizePolicy3);
        tab6 = new QWidget();
        tab6->setObjectName(QString::fromUtf8("tab6"));
        gridLayout15 = new QGridLayout(tab6);
        gridLayout15->setSpacing(6);
        gridLayout15->setContentsMargins(11, 11, 11, 11);
        gridLayout15->setObjectName(QString::fromUtf8("gridLayout15"));
        pArrayWidget_3 = new CQArrayAnnotationsWidget(tab6);
        pArrayWidget_3->setObjectName(QString::fromUtf8("pArrayWidget_3"));

        gridLayout15->addWidget(pArrayWidget_3, 0, 0, 1, 1);

        mTabWidget_3->addTab(tab6, QString());
        tab7 = new QWidget();
        tab7->setObjectName(QString::fromUtf8("tab7"));
        gridLayout16 = new QGridLayout(tab7);
        gridLayout16->setSpacing(6);
        gridLayout16->setContentsMargins(11, 11, 11, 11);
        gridLayout16->setObjectName(QString::fromUtf8("gridLayout16"));
        pArrayWidget2_3 = new CQArrayAnnotationsWidget(tab7);
        pArrayWidget2_3->setObjectName(QString::fromUtf8("pArrayWidget2_3"));

        gridLayout16->addWidget(pArrayWidget2_3, 0, 0, 1, 1);

        mTabWidget_3->addTab(tab7, QString());
        TabPage8 = new QWidget();
        TabPage8->setObjectName(QString::fromUtf8("TabPage8"));
        gridLayout17 = new QGridLayout(TabPage8);
        gridLayout17->setSpacing(6);
        gridLayout17->setContentsMargins(11, 11, 11, 11);
        gridLayout17->setObjectName(QString::fromUtf8("gridLayout17"));
        pArrayWidget3_3 = new CQArrayAnnotationsWidget(TabPage8);
        pArrayWidget3_3->setObjectName(QString::fromUtf8("pArrayWidget3_3"));

        gridLayout17->addWidget(pArrayWidget3_3, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage8, QString());
        TabPage9 = new QWidget();
        TabPage9->setObjectName(QString::fromUtf8("TabPage9"));
        gridLayout18 = new QGridLayout(TabPage9);
        gridLayout18->setSpacing(6);
        gridLayout18->setContentsMargins(11, 11, 11, 11);
        gridLayout18->setObjectName(QString::fromUtf8("gridLayout18"));
        pArrayWidget4_3 = new CQArrayAnnotationsWidget(TabPage9);
        pArrayWidget4_3->setObjectName(QString::fromUtf8("pArrayWidget4_3"));

        gridLayout18->addWidget(pArrayWidget4_3, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage9, QString());
        TabPage10 = new QWidget();
        TabPage10->setObjectName(QString::fromUtf8("TabPage10"));
        gridLayout19 = new QGridLayout(TabPage10);
        gridLayout19->setSpacing(6);
        gridLayout19->setContentsMargins(11, 11, 11, 11);
        gridLayout19->setObjectName(QString::fromUtf8("gridLayout19"));
        pArrayWidgetNPIr = new CQArrayAnnotationsWidget(TabPage10);
        pArrayWidgetNPIr->setObjectName(QString::fromUtf8("pArrayWidgetNPIr"));

        gridLayout19->addWidget(pArrayWidgetNPIr, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage10, QString());
        TabPage11 = new QWidget();
        TabPage11->setObjectName(QString::fromUtf8("TabPage11"));
        gridLayout20 = new QGridLayout(TabPage11);
        gridLayout20->setSpacing(6);
        gridLayout20->setContentsMargins(11, 11, 11, 11);
        gridLayout20->setObjectName(QString::fromUtf8("gridLayout20"));
        pArrayWidgetNPIc = new CQArrayAnnotationsWidget(TabPage11);
        pArrayWidgetNPIc->setObjectName(QString::fromUtf8("pArrayWidgetNPIc"));

        gridLayout20->addWidget(pArrayWidgetNPIc, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage11, QString());
        TabPage12 = new QWidget();
        TabPage12->setObjectName(QString::fromUtf8("TabPage12"));
        gridLayout21 = new QGridLayout(TabPage12);
        gridLayout21->setSpacing(6);
        gridLayout21->setContentsMargins(11, 11, 11, 11);
        gridLayout21->setObjectName(QString::fromUtf8("gridLayout21"));
        pArrayWidget4_3_2 = new CQArrayAnnotationsWidget(TabPage12);
        pArrayWidget4_3_2->setObjectName(QString::fromUtf8("pArrayWidget4_3_2"));

        gridLayout21->addWidget(pArrayWidget4_3_2, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage12, QString());
        TabPage13 = new QWidget();
        TabPage13->setObjectName(QString::fromUtf8("TabPage13"));
        gridLayout22 = new QGridLayout(TabPage13);
        gridLayout22->setSpacing(6);
        gridLayout22->setContentsMargins(11, 11, 11, 11);
        gridLayout22->setObjectName(QString::fromUtf8("gridLayout22"));
        pArrayWidgetNIIr = new CQArrayAnnotationsWidget(TabPage13);
        pArrayWidgetNIIr->setObjectName(QString::fromUtf8("pArrayWidgetNIIr"));

        gridLayout22->addWidget(pArrayWidgetNIIr, 0, 0, 1, 1);

        mTabWidget_3->addTab(TabPage13, QString());

        gridLayout14->addWidget(mTabWidget_3, 2, 0, 1, 7);

        pLabel1_3 = new QLabel(TabPage_CSP);
        pLabel1_3->setObjectName(QString::fromUtf8("pLabel1_3"));
        sizePolicy6.setHeightForWidth(pLabel1_3->sizePolicy().hasHeightForWidth());
        pLabel1_3->setSizePolicy(sizePolicy6);
        pLabel1_3->setWordWrap(false);

        gridLayout14->addWidget(pLabel1_3, 0, 0, 1, 1);

        mLabel2_3 = new QLabel(TabPage_CSP);
        mLabel2_3->setObjectName(QString::fromUtf8("mLabel2_3"));
        sizePolicy5.setHeightForWidth(mLabel2_3->sizePolicy().hasHeightForWidth());
        mLabel2_3->setSizePolicy(sizePolicy5);
        mLabel2_3->setFont(font);
        mLabel2_3->setWordWrap(false);

        gridLayout14->addWidget(mLabel2_3, 0, 1, 1, 1);

        mLabel3_3 = new QLabel(TabPage_CSP);
        mLabel3_3->setObjectName(QString::fromUtf8("mLabel3_3"));
        sizePolicy6.setHeightForWidth(mLabel3_3->sizePolicy().hasHeightForWidth());
        mLabel3_3->setSizePolicy(sizePolicy6);
        mLabel3_3->setWordWrap(false);

        gridLayout14->addWidget(mLabel3_3, 0, 2, 1, 1);

        mLabel4_3 = new QLabel(TabPage_CSP);
        mLabel4_3->setObjectName(QString::fromUtf8("mLabel4_3"));
        sizePolicy5.setHeightForWidth(mLabel4_3->sizePolicy().hasHeightForWidth());
        mLabel4_3->setSizePolicy(sizePolicy5);
        mLabel4_3->setFont(font);
        mLabel4_3->setWordWrap(false);

        gridLayout14->addWidget(mLabel4_3, 0, 3, 1, 1);

        mLabel5_3 = new QLabel(TabPage_CSP);
        mLabel5_3->setObjectName(QString::fromUtf8("mLabel5_3"));
        sizePolicy6.setHeightForWidth(mLabel5_3->sizePolicy().hasHeightForWidth());
        mLabel5_3->setSizePolicy(sizePolicy6);
        mLabel5_3->setWordWrap(false);

        gridLayout14->addWidget(mLabel5_3, 0, 4, 1, 1);

        mLabel6_3 = new QLabel(TabPage_CSP);
        mLabel6_3->setObjectName(QString::fromUtf8("mLabel6_3"));
        sizePolicy5.setHeightForWidth(mLabel6_3->sizePolicy().hasHeightForWidth());
        mLabel6_3->setSizePolicy(sizePolicy5);
        mLabel6_3->setWordWrap(false);

        gridLayout14->addWidget(mLabel6_3, 0, 5, 1, 1);

        mSpacer_3 = new QSpacerItem(181, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout14->addItem(mSpacer_3, 0, 6, 1, 1);

        mSlider_3 = new QSlider(TabPage_CSP);
        mSlider_3->setObjectName(QString::fromUtf8("mSlider_3"));
        sizePolicy4.setHeightForWidth(mSlider_3->sizePolicy().hasHeightForWidth());
        mSlider_3->setSizePolicy(sizePolicy4);
        mSlider_3->setMouseTracking(true);
        mSlider_3->setAcceptDrops(true);
        mSlider_3->setMaximum(0);
        mSlider_3->setPageStep(1);
        mSlider_3->setTracking(true);
        mSlider_3->setOrientation(Qt::Horizontal);
        mSlider_3->setTickPosition(QSlider::NoTicks);
        mSlider_3->setTickInterval(1);

        gridLayout14->addWidget(mSlider_3, 1, 0, 1, 7);

        tabWidget2->addTab(TabPage_CSP, QString());

        verticalLayout->addWidget(tabWidget2);


        retranslateUi(CQTSSAResultSubWidget);
        QObject::connect(ButtonSaveData, SIGNAL(clicked()), CQTSSAResultSubWidget, SLOT(saveDataToFile()));

        tabWidget2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CQTSSAResultSubWidget);
    } // setupUi

    void retranslateUi(CopasiWidget *CQTSSAResultSubWidget)
    {
        CQTSSAResultSubWidget->setWindowTitle(QApplication::translate("CQTSSAResultSubWidget", "TSSA Result Window", 0, QApplication::UnicodeUTF8));
        mpLblResult->setText(QApplication::translate("CQTSSAResultSubWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">Time Scale Separation Analysis Result</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ButtonSaveData->setText(QApplication::translate("CQTSSAResultSubWidget", "Save to File", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("CQTSSAResultSubWidget", "Concentrations", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CQTSSAResultSubWidget", "Particle Numbers", 0, QApplication::UnicodeUTF8)
        );
        tabWidget2->setTabText(tabWidget2->indexOf(tab), QApplication::translate("CQTSSAResultSubWidget", "OptimizationResult", 0, QApplication::UnicodeUTF8));
        tabWidget2->setTabText(tabWidget2->indexOf(tab1), QApplication::translate("CQTSSAResultSubWidget", "TimeSeries", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSlider->setToolTip(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mSlider->setWhatsThis(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        mLabel7->setText(QString());
        pLabel1->setText(QApplication::translate("CQTSSAResultSubWidget", "ILDM operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
        mLabel2->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel3->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
        mLabel4->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel5->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));
        mLabel6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(tab2), QApplication::translate("CQTSSAResultSubWidget", "Species", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(tab3), QApplication::translate("CQTSSAResultSubWidget", "Modes", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage), QApplication::translate("CQTSSAResultSubWidget", "Slow space", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage1), QApplication::translate("CQTSSAResultSubWidget", "Fast space", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage2), QApplication::translate("CQTSSAResultSubWidget", "Reactions slow space", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage3), QApplication::translate("CQTSSAResultSubWidget", "Reactions contributions to modes", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage4), QApplication::translate("CQTSSAResultSubWidget", "Reactions distribution between modes", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(TabPage5), QApplication::translate("CQTSSAResultSubWidget", "Reactions fast space", 0, QApplication::UnicodeUTF8));
        tabWidget2->setTabText(tabWidget2->indexOf(TabPage_ILDM), QApplication::translate("CQTSSAResultSubWidget", "ILDM", 0, QApplication::UnicodeUTF8));
        pLabel1_6->setText(QApplication::translate("CQTSSAResultSubWidget", "ILDM operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
        mLabel6_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel4_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel2_6->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel3_6->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
        mLabel5_6->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSlider_4->setToolTip(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mSlider_4->setWhatsThis(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        mTabWidget_4->setTabText(mTabWidget_4->indexOf(tab4), QApplication::translate("CQTSSAResultSubWidget", "Metabolites", 0, QApplication::UnicodeUTF8));
        mTabWidget_4->setTabText(mTabWidget_4->indexOf(tab5), QApplication::translate("CQTSSAResultSubWidget", "Modes", 0, QApplication::UnicodeUTF8));
        mTabWidget_4->setTabText(mTabWidget_4->indexOf(TabPage6), QApplication::translate("CQTSSAResultSubWidget", "Slow space", 0, QApplication::UnicodeUTF8));
        mTabWidget_4->setTabText(mTabWidget_4->indexOf(TabPage7), QApplication::translate("CQTSSAResultSubWidget", "Fast space", 0, QApplication::UnicodeUTF8));
        tabWidget2->setTabText(tabWidget2->indexOf(TabPage_ILDMM), QApplication::translate("CQTSSAResultSubWidget", "ILDM Modified", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(tab6), QApplication::translate("CQTSSAResultSubWidget", "Amplitude", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(tab7), QApplication::translate("CQTSSAResultSubWidget", "Radical Pointer", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage8), QApplication::translate("CQTSSAResultSubWidget", "Normed Fast Reaction Pointer", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage9), QApplication::translate("CQTSSAResultSubWidget", "Participation Index", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage10), QApplication::translate("CQTSSAResultSubWidget", "Normed Participation Index (by row)", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage11), QApplication::translate("CQTSSAResultSubWidget", "Normed Participation Index (by column)", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage12), QApplication::translate("CQTSSAResultSubWidget", "Importance Index", 0, QApplication::UnicodeUTF8));
        mTabWidget_3->setTabText(mTabWidget_3->indexOf(TabPage13), QApplication::translate("CQTSSAResultSubWidget", "Normed Importance Index (by row)", 0, QApplication::UnicodeUTF8));
        pLabel1_3->setText(QApplication::translate("CQTSSAResultSubWidget", "CSP operation behavior at timepoint:", 0, QApplication::UnicodeUTF8));
        mLabel2_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel3_3->setText(QApplication::translate("CQTSSAResultSubWidget", "or step:", 0, QApplication::UnicodeUTF8));
        mLabel4_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
        mLabel5_3->setText(QApplication::translate("CQTSSAResultSubWidget", "of", 0, QApplication::UnicodeUTF8));
        mLabel6_3->setText(QApplication::translate("CQTSSAResultSubWidget", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mSlider_3->setToolTip(QApplication::translate("CQTSSAResultSubWidget", "move mouse-cursor over slider and use scrollwheel to adjust required step accurately", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        mSlider_3->setWhatsThis(QApplication::translate("CQTSSAResultSubWidget", "use slider to adjust required step", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        tabWidget2->setTabText(tabWidget2->indexOf(TabPage_CSP), QApplication::translate("CQTSSAResultSubWidget", "CSP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CQTSSAResultSubWidget: public Ui_CQTSSAResultSubWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CQTSSARESULTSUBWIDGET_H
