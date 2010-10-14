#ifndef CQEXPERIMENTDATA_H
#define CQEXPERIMENTDATA_H

#include <qvariant.h>

class CExperimentSet;
class CExperimentFileInfo;
class CExperiment;
class CQExperimentDataValidator;
class QSignalMapper;
class CCrossValidationSet;
class CCopasiDataModel;

#include <Qt3Support/Q3ButtonGroup>
#include <Qt3Support/Q3Header>
#include <Qt3Support/Q3ListBox>
#include <Qt3Support/Q3Table>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <map>
#include <string>

QT_BEGIN_NAMESPACE

class Ui_CQExperimentData
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *mpLblWeight;
    QLineEdit *mpEditWeight;
    QLabel *mpLblThreshold;
    QLineEdit *mpEditThreshold;
    QFrame *mpLineCrossValidation;
    QGridLayout *gridLayout;
    QToolButton *mpBtnFileAdd;
    QLabel *mpLblFile;
    Q3ListBox *mpBoxFile;
    QToolButton *mpBtnExperimentDelete;
    QToolButton *mpBtnFileDelete;
    QToolButton *mpBtnExperimentAdd;
    Q3ListBox *mpBoxExperiment;
    QLabel *mpLblExperiment;
    QGridLayout *gridLayout1;
    QLabel *mpLblHeader;
    QLineEdit *mpEditName;
    QFrame *mpLine;
    QLabel *mpLblName;
    QLineEdit *mpEditSeparator;
    QLineEdit *mpEditLast;
    QComboBox *mpBoxWeightMethod;
    QLabel *mpLblExperimentType;
    QLineEdit *mpEditHeader;
    QLabel *mpLblFirst;
    QCheckBox *mpCheckTab;
    Q3ButtonGroup *mpBtnGroup;
    QHBoxLayout *hboxLayout1;
    QRadioButton *mpBtnSteadystate;
    QRadioButton *mpBtnTimeCourse;
    QHBoxLayout *hboxLayout2;
    QCheckBox *mpCheckFrom;
    QCheckBox *mpCheckTo;
    QCheckBox *mpCheckHeader;
    QLabel *mpLblSeperator;
    QLabel *mpLblCopy;
    QLabel *mpLblWeightMethod;
    QLineEdit *mpEditFirst;
    QLabel *mpLblLast;
    Q3Table *mpTable;
    QHBoxLayout *hboxLayout3;
    QPushButton *mpBtnOK;
    QPushButton *mpBtnRevert;
    QPushButton *mpBtnCancel;

    void setupUi(QDialog *CQExperimentData)
    {
        if (CQExperimentData->objectName().isEmpty())
            CQExperimentData->setObjectName(QString::fromUtf8("CQExperimentData"));
        CQExperimentData->resize(522, 421);
        CQExperimentData->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(CQExperimentData);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        mpLblWeight = new QLabel(CQExperimentData);
        mpLblWeight->setObjectName(QString::fromUtf8("mpLblWeight"));
        mpLblWeight->setWordWrap(false);

        hboxLayout->addWidget(mpLblWeight);

        mpEditWeight = new QLineEdit(CQExperimentData);
        mpEditWeight->setObjectName(QString::fromUtf8("mpEditWeight"));

        hboxLayout->addWidget(mpEditWeight);

        mpLblThreshold = new QLabel(CQExperimentData);
        mpLblThreshold->setObjectName(QString::fromUtf8("mpLblThreshold"));
        mpLblThreshold->setWordWrap(false);

        hboxLayout->addWidget(mpLblThreshold);

        mpEditThreshold = new QLineEdit(CQExperimentData);
        mpEditThreshold->setObjectName(QString::fromUtf8("mpEditThreshold"));

        hboxLayout->addWidget(mpEditThreshold);


        vboxLayout->addLayout(hboxLayout);

        mpLineCrossValidation = new QFrame(CQExperimentData);
        mpLineCrossValidation->setObjectName(QString::fromUtf8("mpLineCrossValidation"));
        mpLineCrossValidation->setFrameShape(QFrame::HLine);
        mpLineCrossValidation->setFrameShadow(QFrame::Sunken);

        vboxLayout->addWidget(mpLineCrossValidation);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mpBtnFileAdd = new QToolButton(CQExperimentData);
        mpBtnFileAdd->setObjectName(QString::fromUtf8("mpBtnFileAdd"));
        mpBtnFileAdd->setMaximumSize(QSize(20, 20));
        const QIcon icon = qt_get_icon(image0_ID);
        mpBtnFileAdd->setIcon(icon);

        gridLayout->addWidget(mpBtnFileAdd, 0, 1, 1, 1);

        mpLblFile = new QLabel(CQExperimentData);
        mpLblFile->setObjectName(QString::fromUtf8("mpLblFile"));
        mpLblFile->setWordWrap(false);

        gridLayout->addWidget(mpLblFile, 0, 0, 1, 1);

        mpBoxFile = new Q3ListBox(CQExperimentData);
        mpBoxFile->setObjectName(QString::fromUtf8("mpBoxFile"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mpBoxFile->sizePolicy().hasHeightForWidth());
        mpBoxFile->setSizePolicy(sizePolicy);
        mpBoxFile->setMinimumSize(QSize(0, 80));
        mpBoxFile->setMaximumSize(QSize(32767, 80));

        gridLayout->addWidget(mpBoxFile, 1, 0, 1, 3);

        mpBtnExperimentDelete = new QToolButton(CQExperimentData);
        mpBtnExperimentDelete->setObjectName(QString::fromUtf8("mpBtnExperimentDelete"));
        mpBtnExperimentDelete->setMaximumSize(QSize(20, 20));
        const QIcon icon1 = qt_get_icon(image1_ID);
        mpBtnExperimentDelete->setIcon(icon1);

        gridLayout->addWidget(mpBtnExperimentDelete, 0, 5, 1, 1);

        mpBtnFileDelete = new QToolButton(CQExperimentData);
        mpBtnFileDelete->setObjectName(QString::fromUtf8("mpBtnFileDelete"));
        mpBtnFileDelete->setMaximumSize(QSize(20, 20));
        mpBtnFileDelete->setIcon(icon1);

        gridLayout->addWidget(mpBtnFileDelete, 0, 2, 1, 1);

        mpBtnExperimentAdd = new QToolButton(CQExperimentData);
        mpBtnExperimentAdd->setObjectName(QString::fromUtf8("mpBtnExperimentAdd"));
        mpBtnExperimentAdd->setMaximumSize(QSize(20, 20));
        mpBtnExperimentAdd->setIcon(icon);

        gridLayout->addWidget(mpBtnExperimentAdd, 0, 4, 1, 1);

        mpBoxExperiment = new Q3ListBox(CQExperimentData);
        mpBoxExperiment->setObjectName(QString::fromUtf8("mpBoxExperiment"));
        sizePolicy.setHeightForWidth(mpBoxExperiment->sizePolicy().hasHeightForWidth());
        mpBoxExperiment->setSizePolicy(sizePolicy);
        mpBoxExperiment->setMinimumSize(QSize(0, 80));
        mpBoxExperiment->setMaximumSize(QSize(32767, 80));

        gridLayout->addWidget(mpBoxExperiment, 1, 3, 1, 3);

        mpLblExperiment = new QLabel(CQExperimentData);
        mpLblExperiment->setObjectName(QString::fromUtf8("mpLblExperiment"));
        mpLblExperiment->setWordWrap(false);

        gridLayout->addWidget(mpLblExperiment, 0, 3, 1, 1);


        vboxLayout->addLayout(gridLayout);

        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        mpLblHeader = new QLabel(CQExperimentData);
        mpLblHeader->setObjectName(QString::fromUtf8("mpLblHeader"));
        mpLblHeader->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblHeader->setWordWrap(false);

        gridLayout1->addWidget(mpLblHeader, 3, 3, 1, 2);

        mpEditName = new QLineEdit(CQExperimentData);
        mpEditName->setObjectName(QString::fromUtf8("mpEditName"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(3), static_cast<QSizePolicy::Policy>(5));
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mpEditName->sizePolicy().hasHeightForWidth());
        mpEditName->setSizePolicy(sizePolicy1);

        gridLayout1->addWidget(mpEditName, 0, 1, 1, 2);

        mpLine = new QFrame(CQExperimentData);
        mpLine->setObjectName(QString::fromUtf8("mpLine"));
        mpLine->setFrameShape(QFrame::HLine);
        mpLine->setFrameShadow(QFrame::Sunken);

        gridLayout1->addWidget(mpLine, 2, 0, 1, 9);

        mpLblName = new QLabel(CQExperimentData);
        mpLblName->setObjectName(QString::fromUtf8("mpLblName"));
        mpLblName->setAlignment(Qt::AlignVCenter);
        mpLblName->setWordWrap(false);

        gridLayout1->addWidget(mpLblName, 0, 0, 1, 1);

        mpEditSeparator = new QLineEdit(CQExperimentData);
        mpEditSeparator->setObjectName(QString::fromUtf8("mpEditSeparator"));
        mpEditSeparator->setEnabled(false);
        QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(0));
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mpEditSeparator->sizePolicy().hasHeightForWidth());
        mpEditSeparator->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(mpEditSeparator, 4, 5, 1, 3);

        mpEditLast = new QLineEdit(CQExperimentData);
        mpEditLast->setObjectName(QString::fromUtf8("mpEditLast"));
        QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(5));
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mpEditLast->sizePolicy().hasHeightForWidth());
        mpEditLast->setSizePolicy(sizePolicy3);
        mpEditLast->setMinimumSize(QSize(50, 0));

        gridLayout1->addWidget(mpEditLast, 0, 7, 1, 2);

        mpBoxWeightMethod = new QComboBox(CQExperimentData);
        mpBoxWeightMethod->setObjectName(QString::fromUtf8("mpBoxWeightMethod"));

        gridLayout1->addWidget(mpBoxWeightMethod, 4, 2, 1, 1);

        mpLblExperimentType = new QLabel(CQExperimentData);
        mpLblExperimentType->setObjectName(QString::fromUtf8("mpLblExperimentType"));
        mpLblExperimentType->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblExperimentType->setWordWrap(false);

        gridLayout1->addWidget(mpLblExperimentType, 3, 0, 1, 2);

        mpEditHeader = new QLineEdit(CQExperimentData);
        mpEditHeader->setObjectName(QString::fromUtf8("mpEditHeader"));
        mpEditHeader->setEnabled(false);

        gridLayout1->addWidget(mpEditHeader, 3, 5, 1, 3);

        mpLblFirst = new QLabel(CQExperimentData);
        mpLblFirst->setObjectName(QString::fromUtf8("mpLblFirst"));
        mpLblFirst->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblFirst->setWordWrap(false);

        gridLayout1->addWidget(mpLblFirst, 0, 3, 1, 1);

        mpCheckTab = new QCheckBox(CQExperimentData);
        mpCheckTab->setObjectName(QString::fromUtf8("mpCheckTab"));
        mpCheckTab->setChecked(true);

        gridLayout1->addWidget(mpCheckTab, 4, 8, 1, 1);

        mpBtnGroup = new Q3ButtonGroup(CQExperimentData);
        mpBtnGroup->setObjectName(QString::fromUtf8("mpBtnGroup"));
        QSizePolicy sizePolicy4(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(4));
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(mpBtnGroup->sizePolicy().hasHeightForWidth());
        mpBtnGroup->setSizePolicy(sizePolicy4);
        mpBtnGroup->setFrameShape(Q3GroupBox::NoFrame);
        mpBtnGroup->setAlignment(Qt::AlignJustify|Qt::AlignCenter|Qt::AlignBottom|Qt::AlignTop|Qt::AlignRight|Qt::AlignLeft);
        mpBtnGroup->setColumnLayout(0, Qt::Vertical);
        mpBtnGroup->layout()->setSpacing(6);
        mpBtnGroup->layout()->setContentsMargins(0, 0, 0, 0);
        hboxLayout1 = new QHBoxLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(mpBtnGroup->layout());
        if (boxlayout)
            boxlayout->addLayout(hboxLayout1);
        hboxLayout1->setAlignment(Qt::AlignTop);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        mpBtnSteadystate = new QRadioButton(mpBtnGroup);
        mpBtnSteadystate->setObjectName(QString::fromUtf8("mpBtnSteadystate"));
        mpBtnSteadystate->setChecked(true);

        hboxLayout1->addWidget(mpBtnSteadystate);

        mpBtnTimeCourse = new QRadioButton(mpBtnGroup);
        mpBtnTimeCourse->setObjectName(QString::fromUtf8("mpBtnTimeCourse"));

        hboxLayout1->addWidget(mpBtnTimeCourse);


        gridLayout1->addWidget(mpBtnGroup, 3, 2, 1, 1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        mpCheckFrom = new QCheckBox(CQExperimentData);
        mpCheckFrom->setObjectName(QString::fromUtf8("mpCheckFrom"));

        hboxLayout2->addWidget(mpCheckFrom);

        mpCheckTo = new QCheckBox(CQExperimentData);
        mpCheckTo->setObjectName(QString::fromUtf8("mpCheckTo"));

        hboxLayout2->addWidget(mpCheckTo);


        gridLayout1->addLayout(hboxLayout2, 1, 2, 1, 1);

        mpCheckHeader = new QCheckBox(CQExperimentData);
        mpCheckHeader->setObjectName(QString::fromUtf8("mpCheckHeader"));

        gridLayout1->addWidget(mpCheckHeader, 3, 8, 1, 1);

        mpLblSeperator = new QLabel(CQExperimentData);
        mpLblSeperator->setObjectName(QString::fromUtf8("mpLblSeperator"));
        mpLblSeperator->setMinimumSize(QSize(0, 0));
        mpLblSeperator->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblSeperator->setWordWrap(false);

        gridLayout1->addWidget(mpLblSeperator, 4, 3, 1, 2);

        mpLblCopy = new QLabel(CQExperimentData);
        mpLblCopy->setObjectName(QString::fromUtf8("mpLblCopy"));
        mpLblCopy->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblCopy->setWordWrap(false);

        gridLayout1->addWidget(mpLblCopy, 1, 0, 1, 2);

        mpLblWeightMethod = new QLabel(CQExperimentData);
        mpLblWeightMethod->setObjectName(QString::fromUtf8("mpLblWeightMethod"));
        mpLblWeightMethod->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblWeightMethod->setWordWrap(false);

        gridLayout1->addWidget(mpLblWeightMethod, 4, 0, 1, 2);

        mpEditFirst = new QLineEdit(CQExperimentData);
        mpEditFirst->setObjectName(QString::fromUtf8("mpEditFirst"));
        sizePolicy3.setHeightForWidth(mpEditFirst->sizePolicy().hasHeightForWidth());
        mpEditFirst->setSizePolicy(sizePolicy3);
        mpEditFirst->setMinimumSize(QSize(50, 0));

        gridLayout1->addWidget(mpEditFirst, 0, 4, 1, 2);

        mpLblLast = new QLabel(CQExperimentData);
        mpLblLast->setObjectName(QString::fromUtf8("mpLblLast"));
        mpLblLast->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        mpLblLast->setWordWrap(false);

        gridLayout1->addWidget(mpLblLast, 0, 6, 1, 1);


        vboxLayout->addLayout(gridLayout1);

        mpTable = new Q3Table(CQExperimentData);
        mpTable->setObjectName(QString::fromUtf8("mpTable"));
        mpTable->setNumRows(3);
        mpTable->setNumCols(7);
        mpTable->setSelectionMode(Q3Table::NoSelection);

        vboxLayout->addWidget(mpTable);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(6);
        hboxLayout3->setContentsMargins(0, 0, 0, 0);
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        mpBtnOK = new QPushButton(CQExperimentData);
        mpBtnOK->setObjectName(QString::fromUtf8("mpBtnOK"));

        hboxLayout3->addWidget(mpBtnOK);

        mpBtnRevert = new QPushButton(CQExperimentData);
        mpBtnRevert->setObjectName(QString::fromUtf8("mpBtnRevert"));

        hboxLayout3->addWidget(mpBtnRevert);

        mpBtnCancel = new QPushButton(CQExperimentData);
        mpBtnCancel->setObjectName(QString::fromUtf8("mpBtnCancel"));

        hboxLayout3->addWidget(mpBtnCancel);


        vboxLayout->addLayout(hboxLayout3);

        QWidget::setTabOrder(mpBoxFile, mpBoxExperiment);
        QWidget::setTabOrder(mpBoxExperiment, mpEditName);
        QWidget::setTabOrder(mpEditName, mpEditFirst);
        QWidget::setTabOrder(mpEditFirst, mpEditLast);
        QWidget::setTabOrder(mpEditLast, mpCheckFrom);
        QWidget::setTabOrder(mpCheckFrom, mpCheckTo);
        QWidget::setTabOrder(mpCheckTo, mpBtnSteadystate);
        QWidget::setTabOrder(mpBtnSteadystate, mpEditHeader);
        QWidget::setTabOrder(mpEditHeader, mpCheckHeader);
        QWidget::setTabOrder(mpCheckHeader, mpEditSeparator);
        QWidget::setTabOrder(mpEditSeparator, mpCheckTab);
        QWidget::setTabOrder(mpCheckTab, mpTable);
        QWidget::setTabOrder(mpTable, mpBtnOK);
        QWidget::setTabOrder(mpBtnOK, mpBtnRevert);
        QWidget::setTabOrder(mpBtnRevert, mpBtnCancel);

        retranslateUi(CQExperimentData);
        QObject::connect(mpCheckHeader, SIGNAL(toggled(bool)), CQExperimentData, SLOT(slotCheckHeader(bool)));
        QObject::connect(mpCheckTab, SIGNAL(toggled(bool)), CQExperimentData, SLOT(slotCheckTab(bool)));
        QObject::connect(mpBtnSteadystate, SIGNAL(toggled(bool)), CQExperimentData, SLOT(slotExprimentType(bool)));
        QObject::connect(mpBtnOK, SIGNAL(clicked()), CQExperimentData, SLOT(slotOK()));
        QObject::connect(mpBtnRevert, SIGNAL(clicked()), CQExperimentData, SLOT(slotRevert()));
        QObject::connect(mpBtnCancel, SIGNAL(clicked()), CQExperimentData, SLOT(slotCancel()));
        QObject::connect(mpBtnFileAdd, SIGNAL(clicked()), CQExperimentData, SLOT(slotFileAdd()));
        QObject::connect(mpBtnFileDelete, SIGNAL(clicked()), CQExperimentData, SLOT(slotFileDelete()));
        QObject::connect(mpBtnExperimentAdd, SIGNAL(clicked()), CQExperimentData, SLOT(slotExperimentAdd()));
        QObject::connect(mpBtnExperimentDelete, SIGNAL(clicked()), CQExperimentData, SLOT(slotExperimentDelete()));
        QObject::connect(mpBoxFile, SIGNAL(currentChanged(Q3ListBoxItem*)), CQExperimentData, SLOT(slotFileChanged(Q3ListBoxItem*)));
        QObject::connect(mpBoxExperiment, SIGNAL(currentChanged(Q3ListBoxItem*)), CQExperimentData, SLOT(slotExperimentChanged(Q3ListBoxItem*)));
        QObject::connect(mpEditHeader, SIGNAL(lostFocus()), CQExperimentData, SLOT(slotUpdateTable()));
        QObject::connect(mpEditSeparator, SIGNAL(textChanged(QString)), CQExperimentData, SLOT(slotSeparator()));
        QObject::connect(mpCheckFrom, SIGNAL(toggled(bool)), CQExperimentData, SLOT(slotCheckFrom(bool)));
        QObject::connect(mpCheckTo, SIGNAL(toggled(bool)), CQExperimentData, SLOT(slotCheckTo(bool)));
        QObject::connect(mpBoxWeightMethod, SIGNAL(activated(int)), CQExperimentData, SLOT(slotWeightMethod(int)));

        QMetaObject::connectSlotsByName(CQExperimentData);
    } // setupUi

    void retranslateUi(QDialog *CQExperimentData)
    {
        CQExperimentData->setWindowTitle(QApplication::translate("CQExperimentData", "Experimental Data", 0, QApplication::UnicodeUTF8));
        mpLblWeight->setText(QApplication::translate("CQExperimentData", "Weight", 0, QApplication::UnicodeUTF8));
        mpLblThreshold->setText(QApplication::translate("CQExperimentData", "Threshold", 0, QApplication::UnicodeUTF8));
        mpBtnFileAdd->setText(QString());
        mpLblFile->setText(QApplication::translate("CQExperimentData", "File", 0, QApplication::UnicodeUTF8));
        mpBoxFile->clear();
        mpBoxFile->insertItem(QString());
        mpBtnExperimentDelete->setText(QString());
        mpBtnFileDelete->setText(QString());
        mpBtnExperimentAdd->setText(QString());
        mpBoxExperiment->clear();
        mpBoxExperiment->insertItem(QString());
        mpLblExperiment->setText(QApplication::translate("CQExperimentData", "Experiment", 0, QApplication::UnicodeUTF8));
        mpLblHeader->setText(QApplication::translate("CQExperimentData", "Header", 0, QApplication::UnicodeUTF8));
        mpLblName->setText(QApplication::translate("CQExperimentData", "Name", 0, QApplication::UnicodeUTF8));
        mpLblExperimentType->setText(QApplication::translate("CQExperimentData", "Experiment Type", 0, QApplication::UnicodeUTF8));
        mpLblFirst->setText(QApplication::translate("CQExperimentData", "First Row", 0, QApplication::UnicodeUTF8));
        mpCheckTab->setText(QApplication::translate("CQExperimentData", "<tab>", 0, QApplication::UnicodeUTF8));
        mpBtnGroup->setTitle(QString());
        mpBtnSteadystate->setText(QApplication::translate("CQExperimentData", "Steady State", 0, QApplication::UnicodeUTF8));
        mpBtnTimeCourse->setText(QApplication::translate("CQExperimentData", "Time Course", 0, QApplication::UnicodeUTF8));
        mpCheckFrom->setText(QApplication::translate("CQExperimentData", "from previous", 0, QApplication::UnicodeUTF8));
        mpCheckTo->setText(QApplication::translate("CQExperimentData", "to next", 0, QApplication::UnicodeUTF8));
        mpCheckHeader->setText(QString());
        mpLblSeperator->setText(QApplication::translate("CQExperimentData", "Separator", 0, QApplication::UnicodeUTF8));
        mpLblCopy->setText(QApplication::translate("CQExperimentData", "Copy settings below", 0, QApplication::UnicodeUTF8));
        mpLblWeightMethod->setText(QApplication::translate("CQExperimentData", "Weight Method", 0, QApplication::UnicodeUTF8));
        mpLblLast->setText(QApplication::translate("CQExperimentData", "Last Row", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(0, QApplication::translate("CQExperimentData", "Column Name", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(1, QApplication::translate("CQExperimentData", "Type", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(2, QApplication::translate("CQExperimentData", "Hidden", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(3, QApplication::translate("CQExperimentData", "<>", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(4, QApplication::translate("CQExperimentData", "Model Object", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(5, QApplication::translate("CQExperimentData", "Hidden", 0, QApplication::UnicodeUTF8));
        mpTable->horizontalHeader()->setLabel(6, QApplication::translate("CQExperimentData", "Weight", 0, QApplication::UnicodeUTF8));
        mpBtnOK->setText(QApplication::translate("CQExperimentData", "&OK", 0, QApplication::UnicodeUTF8));
        mpBtnOK->setShortcut(QApplication::translate("CQExperimentData", "Alt+O", 0, QApplication::UnicodeUTF8));
        mpBtnRevert->setText(QApplication::translate("CQExperimentData", "&Revert", 0, QApplication::UnicodeUTF8));
        mpBtnRevert->setShortcut(QApplication::translate("CQExperimentData", "Alt+R", 0, QApplication::UnicodeUTF8));
        mpBtnCancel->setText(QApplication::translate("CQExperimentData", "&Cancel", 0, QApplication::UnicodeUTF8));
        mpBtnCancel->setShortcut(QApplication::translate("CQExperimentData", "Alt+C", 0, QApplication::UnicodeUTF8));
    } // retranslateUi


protected:
    enum IconID
    {
        image0_ID,
        image1_ID,
        unknown_ID
    };
    static QPixmap qt_get_icon(IconID id)
    {
    static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x01,
    0xdd, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x8d, 0x93, 0xbd, 0x6a, 0x55,
    0x41, 0x10, 0xc7, 0x7f, 0xb3, 0x67, 0xf7, 0x28, 0x18, 0x44, 0x24, 0x82,
    0x56, 0x56, 0xa2, 0x4d, 0x7c, 0x01, 0x9b, 0x54, 0xe2, 0x03, 0xd8, 0x5a,
    0xf9, 0x04, 0x3e, 0x80, 0x8d, 0x45, 0xc0, 0x5a, 0xb0, 0xb1, 0xb4, 0x11,
    0x04, 0x5b, 0xb5, 0xb0, 0x92, 0x40, 0x08, 0x1a, 0x3f, 0x90, 0x34, 0x26,
    0x51, 0x50, 0x50, 0xf1, 0x92, 0xfb, 0xed, 0xfd, 0xd8, 0xdd, 0x19, 0x8b,
    0x73, 0x4e, 0x3c, 0x68, 0x72, 0x71, 0x60, 0x61, 0x77, 0x76, 0xf7, 0xb7,
    0x33, 0xfb, 0x9f, 0x91, 0xf5, 0xcd, 0xed, 0xce, 0xa9, 0x93, 0x4b, 0xc7,
    0xd4, 0x8c, 0xc6, 0xd4, 0x60, 0x3a, 0x9d, 0x11, 0xe7, 0x91, 0xce, 0x7e,
    0xdf, 0xa5, 0xa8, 0xdd, 0x5e, 0x7f, 0x7c, 0xed, 0xe6, 0x8d, 0xab, 0x1f,
    0xf8, 0xdb, 0x5e, 0xbd, 0xdd, 0x99, 0xa8, 0xaa, 0xb5, 0x47, 0xce, 0xd9,
    0xc6, 0x93, 0x68, 0x83, 0x61, 0xb4, 0x37, 0xef, 0xf7, 0xec, 0xe3, 0xee,
    0x37, 0x7b, 0xf6, 0x62, 0xeb, 0xe7, 0x83, 0x87, 0x4f, 0x57, 0xcd, 0x8c,
    0xf6, 0x70, 0xff, 0x10, 0x01, 0x11, 0xc1, 0x39, 0x10, 0xa7, 0xb8, 0xc2,
    0x71, 0xf6, 0xdc, 0x32, 0xab, 0x57, 0x56, 0x96, 0x2f, 0x5d, 0x38, 0xff,
    0xfc, 0xd1, 0x93, 0x97, 0xd7, 0xdb, 0x67, 0x0f, 0x05, 0x18, 0x20, 0x40,
    0x59, 0x7a, 0x3e, 0x7d, 0xfe, 0xc2, 0xc6, 0xc6, 0x16, 0xaf, 0xdf, 0x6d,
    0x93, 0xe2, 0xb4, 0x1c, 0x0e, 0x7a, 0x8f, 0x6f, 0xdf, 0xb9, 0x7f, 0x6b,
    0x21, 0x00, 0x40, 0x9c, 0xe0, 0x04, 0xce, 0x2c, 0x9f, 0x66, 0x1e, 0x8d,
    0x1f, 0xdf, 0xbb, 0xec, 0xec, 0x7e, 0xa5, 0x3c, 0x5e, 0x32, 0x1c, 0xf5,
    0xd6, 0x9a, 0x73, 0xfe, 0xd0, 0xcb, 0x80, 0x13, 0x21, 0x45, 0xe5, 0xf2,
    0xca, 0x45, 0x66, 0xd3, 0xc8, 0x7e, 0xb7, 0x4f, 0x67, 0xbf, 0x47, 0x08,
    0x25, 0x9b, 0x1b, 0xeb, 0x2c, 0x04, 0x98, 0x19, 0x39, 0x2b, 0x89, 0x4c,
    0xaf, 0xf7, 0x8b, 0xd1, 0x68, 0xca, 0x6c, 0x36, 0xa7, 0x0c, 0x81, 0x10,
    0x3c, 0x45, 0x51, 0x2c, 0x06, 0x24, 0x35, 0x86, 0xa3, 0x39, 0x29, 0x25,
    0x34, 0x1b, 0x65, 0x19, 0x10, 0x07, 0xaa, 0x4a, 0xf0, 0x01, 0x11, 0x8e,
    0x06, 0xc4, 0xac, 0x4c, 0x26, 0x91, 0xac, 0x55, 0x32, 0xae, 0x10, 0x3c,
    0x0e, 0x91, 0x92, 0x9c, 0x13, 0x21, 0x84, 0x3a, 0xc9, 0x06, 0x50, 0xcf,
    0xa7, 0x31, 0x23, 0x40, 0x4c, 0xb9, 0x56, 0xc0, 0xa1, 0x19, 0xc4, 0x41,
    0x12, 0x45, 0xb2, 0x02, 0x9e, 0xc2, 0x7b, 0xa4, 0x15, 0x82, 0x6f, 0x64,
    0x48, 0x49, 0x0f, 0x42, 0x93, 0x42, 0x20, 0x19, 0x82, 0x54, 0x35, 0x21,
    0x82, 0x15, 0xe0, 0x14, 0x0a, 0x81, 0x4a, 0xe8, 0xca, 0x9c, 0xb6, 0x7f,
    0x1e, 0x2a, 0x48, 0xe3, 0xac, 0xe9, 0xae, 0x70, 0x08, 0x0e, 0x11, 0xa9,
    0x5f, 0xff, 0x13, 0xc1, 0x91, 0x75, 0xf0, 0xbf, 0xe6, 0x1a, 0x82, 0x69,
    0xd5, 0x44, 0x58, 0x15, 0x60, 0xab, 0xb7, 0x30, 0xad, 0x17, 0x56, 0x49,
    0xdc, 0x4e, 0xc1, 0x37, 0x7b, 0x4b, 0x27, 0xc2, 0x81, 0x53, 0xa1, 0x52,
    0xc1, 0x20, 0x25, 0x23, 0xab, 0x91, 0x72, 0x46, 0x63, 0xc6, 0x87, 0x92,
    0xb6, 0x8e, 0xbe, 0x3f, 0x18, 0x8c, 0xd7, 0xee, 0xde, 0x4b, 0xce, 0xf9,
    0xfa, 0x11, 0x45, 0x70, 0x98, 0x29, 0x66, 0x60, 0x75, 0x67, 0x98, 0x19,
    0x98, 0x21, 0xe2, 0x18, 0x0f, 0x86, 0xb3, 0x06, 0xf0, 0x1b, 0xda, 0xc4,
    0xfd, 0x8b, 0x61, 0x0d, 0x6a, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,
    0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

    static const unsigned char image1_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
    0x08, 0x06, 0x00, 0x00, 0x00, 0x1f, 0xf3, 0xff, 0x61, 0x00, 0x00, 0x02,
    0x7c, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x7d, 0x93, 0x5d, 0x68, 0x8e,
    0x61, 0x18, 0xc7, 0x7f, 0xf7, 0xfd, 0x3c, 0xf7, 0xf3, 0xce, 0x5e, 0x66,
    0x63, 0xbe, 0x45, 0xbe, 0xb2, 0x48, 0xc9, 0x81, 0x14, 0x49, 0x42, 0x0e,
    0x70, 0xb4, 0x13, 0x07, 0x8e, 0x28, 0x25, 0xca, 0x28, 0x49, 0x51, 0x1c,
    0xcc, 0x47, 0x39, 0x21, 0x1f, 0x71, 0x20, 0x39, 0x51, 0x6a, 0x25, 0xc5,
    0x94, 0x1d, 0x88, 0xb1, 0x96, 0xcd, 0x47, 0xbe, 0xc6, 0x36, 0x9f, 0xb3,
    0x79, 0x37, 0xdb, 0xfb, 0xb1, 0x87, 0x77, 0xef, 0xf3, 0x3c, 0xf7, 0xe5,
    0xc0, 0xfb, 0xda, 0x8b, 0xe5, 0xaa, 0xab, 0xae, 0x83, 0xeb, 0xfa, 0xdf,
    0xff, 0x8f, 0x6e, 0xd5, 0xd8, 0xfc, 0xb2, 0xaf, 0xbc, 0x6c, 0x74, 0xcc,
    0x8a, 0x50, 0x28, 0x2b, 0x90, 0xcd, 0x0e, 0x11, 0xe4, 0x02, 0xfa, 0xfa,
    0x53, 0x3a, 0x0c, 0xec, 0x40, 0x32, 0xe5, 0xaf, 0xdf, 0xba, 0x65, 0xdd,
    0x73, 0xfe, 0xae, 0x47, 0x4f, 0xda, 0x7f, 0x58, 0x6b, 0xa5, 0xb8, 0xa3,
    0x28, 0x12, 0xff, 0x47, 0x20, 0xe9, 0x4c, 0x20, 0x8f, 0x9f, 0x75, 0xca,
    0xdb, 0x8e, 0x6e, 0xa9, 0x6f, 0x68, 0xed, 0xbd, 0x78, 0xe5, 0xd6, 0x2a,
    0x11, 0xa1, 0xb8, 0xf5, 0x3f, 0x88, 0x80, 0x52, 0x0a, 0xad, 0x41, 0x69,
    0x8b, 0x76, 0x34, 0x93, 0xa7, 0x54, 0xb2, 0x6a, 0xf9, 0xa2, 0xca, 0xaa,
    0x79, 0x33, 0x6f, 0x5f, 0xad, 0xbb, 0x57, 0x5d, 0xbc, 0x3b, 0x22, 0x80,
    0x00, 0x0a, 0xf0, 0x3c, 0x97, 0x77, 0xef, 0x3f, 0xd1, 0xd4, 0xd4, 0x4a,
    0xcb, 0xd3, 0x97, 0x84, 0x41, 0xd6, 0xcb, 0xa4, 0x93, 0xd7, 0x0e, 0x1e,
    0x39, 0x5b, 0xf3, 0x5f, 0x00, 0x00, 0xa5, 0x15, 0x5a, 0xc1, 0x84, 0xca,
    0x71, 0xe4, 0xac, 0xe2, 0x6b, 0x4f, 0x8a, 0xf6, 0x8e, 0x4f, 0x78, 0x25,
    0x1e, 0x99, 0xc1, 0x64, 0x6d, 0x61, 0xcf, 0x1d, 0xf1, 0x18, 0xd0, 0x4a,
    0x11, 0x06, 0x21, 0x8b, 0x16, 0x57, 0x91, 0xcb, 0x06, 0xf4, 0x65, 0x86,
    0xe8, 0xef, 0xee, 0xc6, 0x18, 0x8f, 0xe6, 0xa6, 0xc6, 0x11, 0x24, 0xd8,
    0x08, 0x5e, 0x35, 0x43, 0x5b, 0x0b, 0x16, 0x08, 0x05, 0x42, 0x63, 0x18,
    0xec, 0xec, 0x44, 0x9f, 0xd8, 0x83, 0x69, 0xa8, 0xc3, 0x94, 0xc6, 0xf1,
    0x3c, 0x83, 0xe3, 0x38, 0xbf, 0xcf, 0x86, 0x19, 0x7c, 0x7e, 0x03, 0x0f,
    0xeb, 0xc1, 0x4f, 0x22, 0x1f, 0x3b, 0xf1, 0x57, 0x54, 0x23, 0x1f, 0xda,
    0xa8, 0x38, 0x75, 0x80, 0x58, 0x43, 0x3d, 0xa3, 0x66, 0x3c, 0x20, 0x58,
    0xb8, 0x14, 0x3d, 0x71, 0x1a, 0x4a, 0x31, 0x02, 0xc0, 0x94, 0x39, 0x30,
    0x73, 0x3e, 0xdc, 0xa9, 0xc3, 0x69, 0xbb, 0x44, 0xfc, 0x51, 0x23, 0xba,
    0xbd, 0x1d, 0x73, 0xef, 0x2e, 0xc1, 0xd4, 0xd9, 0x0c, 0xec, 0x3c, 0x8c,
    0x53, 0x39, 0x09, 0xa3, 0x6c, 0x5e, 0x64, 0x01, 0x20, 0x3f, 0x67, 0xb5,
    0x8b, 0x5a, 0x59, 0x8d, 0xfa, 0x3e, 0x84, 0xb9, 0x7a, 0x9e, 0xd8, 0x8b,
    0x1b, 0x90, 0x18, 0x20, 0x58, 0xb0, 0x98, 0xfe, 0x43, 0x67, 0x08, 0x66,
    0x55, 0xe1, 0x0c, 0x0e, 0xe2, 0xb8, 0x2e, 0xaa, 0x88, 0x82, 0x5b, 0x30,
    0x21, 0x8c, 0x40, 0x19, 0x07, 0x57, 0x97, 0xa0, 0xba, 0x12, 0xf0, 0xa5,
    0x17, 0x32, 0x59, 0xe8, 0xfa, 0x86, 0xb2, 0x0a, 0xe5, 0x19, 0x1c, 0x05,
    0x8e, 0x2a, 0x04, 0x9d, 0x37, 0xd1, 0x16, 0x9c, 0x0f, 0x72, 0x78, 0x57,
    0x4e, 0x13, 0x3b, 0xbe, 0x1f, 0x7a, 0x53, 0x44, 0x4b, 0x96, 0x61, 0xe3,
    0xe3, 0x31, 0x2d, 0xaf, 0x19, 0xbf, 0x61, 0x2d, 0xb1, 0x9b, 0x37, 0x60,
    0x54, 0x69, 0xfe, 0xf5, 0x61, 0x06, 0xbf, 0x53, 0x70, 0xef, 0xd7, 0x63,
    0xce, 0x1c, 0x83, 0x9e, 0x3e, 0x72, 0x9b, 0xb7, 0x92, 0xb9, 0x7c, 0x1b,
    0xff, 0xe4, 0x05, 0xa4, 0x6c, 0x2c, 0x4e, 0x22, 0x41, 0xf9, 0xde, 0x5d,
    0xe8, 0x44, 0x0f, 0x62, 0xbc, 0x3f, 0x22, 0x1f, 0x96, 0xb0, 0x74, 0x35,
    0x6a, 0xf5, 0x26, 0x64, 0xfa, 0x5c, 0x72, 0xdb, 0x6a, 0x10, 0x11, 0x82,
    0x8d, 0x1b, 0x49, 0x5e, 0xbb, 0x4e, 0xe9, 0xbe, 0xdd, 0xf8, 0xdb, 0x77,
    0x60, 0xc7, 0x8c, 0xc5, 0x09, 0xc2, 0x3f, 0x24, 0xb8, 0x36, 0x3f, 0xc7,
    0x2b, 0xca, 0xe0, 0xe8, 0x39, 0x04, 0x30, 0x40, 0x14, 0x81, 0x08, 0x44,
    0x6b, 0x56, 0x92, 0x7b, 0xdc, 0x8a, 0x0a, 0x84, 0xb8, 0x9f, 0xc3, 0x75,
    0x0d, 0xc5, 0x39, 0xba, 0xa9, 0x74, 0xda, 0xaf, 0x3d, 0x7e, 0x3a, 0xd4,
    0xfa, 0x57, 0xa2, 0x82, 0x45, 0xa1, 0x11, 0xb1, 0x88, 0x80, 0xe4, 0x7f,
    0x86, 0x88, 0x80, 0x08, 0x4a, 0x69, 0xfc, 0x74, 0x66, 0xa8, 0x00, 0xf0,
    0x13, 0xf0, 0x32, 0x22, 0x79, 0x63, 0x5a, 0xb7, 0x6f, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

    switch (id) {
        case image0_ID:  { QImage img; img.loadFromData(image0_data, sizeof(image0_data), "PNG"); return QPixmap::fromImage(img); }
        case image1_ID:  { QImage img; img.loadFromData(image1_data, sizeof(image1_data), "PNG"); return QPixmap::fromImage(img); }
        default: return QPixmap();
    } // switch
    } // icon

};

namespace Ui {
    class CQExperimentData: public Ui_CQExperimentData {};
} // namespace Ui

QT_END_NAMESPACE

class CQExperimentData : public QDialog, public Ui::CQExperimentData
{
    Q_OBJECT

public:
    CQExperimentData(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~CQExperimentData();

    friend class CQExperimentDataValidator;

    virtual bool load( CExperimentSet * pExperimentSet , CCopasiDataModel * pDataModel );

public slots:
    virtual void loadTable( CExperiment * pExperiment, const bool & guess );

signals:
    void experimentChanged();

protected:
    unsigned int mOldWeightMethod;
    QPixmap mCopasi;
    QSignalMapper * mpBtnMap;
    CQExperimentDataValidator * mpValidatorHeader;
    CQExperimentDataValidator * mpValidatorLast;
    CExperiment * mpExperiment;
    CExperimentFileInfo * mpFileInfo;
    CExperimentSet * mpExperimentSet;
    CExperimentSet * mpExperimentSetCopy;
    std::map<std::string, std::string> mKeyMap;
    std::map<std::string, std::string> mFileMap;
    CQExperimentDataValidator * mpValidatorFirst;
    unsigned int mShown;
    CQExperimentDataValidator * mpValidatorName;
    QSignalMapper * mpComboMap;
    bool mCrossValidation;
    bool mShowError;
    CCopasiDataModel * mpDataModel;

    virtual bool loadExperiment( CExperiment * pExperiment );
    bool saveExperiment( CExperiment * pExperiment, const bool & full );
    void syncExperiments();
    bool saveTable( CExperiment * pExperiment );
    bool isLikePreviousExperiment( CExperiment * pExperiment );
    void enableEdit( const bool & enable );

protected slots:
    virtual void languageChange();

    void slotRevert();
    void slotFirst();
    void slotLast();
    void slotHeader();
    void slotExprimentType( bool isSteadyState );
    void slotCheckTab( bool checked );
    void slotCheckHeader( bool checked );
    void slotExperimentAdd();
    void slotExperimentChanged( Q3ListBoxItem * pItem );
    void slotExperimentDelete();
    void slotFileAdd();
    void slotFileChanged( Q3ListBoxItem * pItem );
    void slotFileDelete();
    void slotCancel();
    void slotOK();
    void slotUpdateTable();
    void slotModelObject( int row );
    void slotTypeChanged( int row );
    void slotSeparator();
    void slotCheckFrom( bool checked );
    void slotCheckTo( bool checked );


private:
    void init();
    void destroy();

private slots:
    void slotWeightMethod( int weightMethod );

};

#endif // CQEXPERIMENTDATA_H
