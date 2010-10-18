#ifndef CQMOIETIESTASKWIDGET_H
#define CQMOIETIESTASKWIDGET_H

#include <qvariant.h>


#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "TaskWidget.h"

QT_BEGIN_NAMESPACE

class Ui_CQMoietiesTaskWidget
{
public:
    QVBoxLayout *vboxLayout;
    QSpacerItem *mpSpacer;

    void setupUi(TaskWidget *CQMoietiesTaskWidget)
    {
        if (CQMoietiesTaskWidget->objectName().isEmpty())
            CQMoietiesTaskWidget->setObjectName(QString::fromUtf8("CQMoietiesTaskWidget"));
        CQMoietiesTaskWidget->resize(260, 23);
        vboxLayout = new QVBoxLayout(CQMoietiesTaskWidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(11, 11, 11, 11);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        mpSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(mpSpacer);


        retranslateUi(CQMoietiesTaskWidget);

        QMetaObject::connectSlotsByName(CQMoietiesTaskWidget);
    } // setupUi

    void retranslateUi(TaskWidget *CQMoietiesTaskWidget)
    {
        CQMoietiesTaskWidget->setCaption(QApplication::translate("CQMoietiesTaskWidget", "Mass Conservation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CQMoietiesTaskWidget: public Ui_CQMoietiesTaskWidget {};
} // namespace Ui

QT_END_NAMESPACE

class CQMoietiesTaskWidget : public TaskWidget, public Ui::CQMoietiesTaskWidget
{
    Q_OBJECT

public:
    CQMoietiesTaskWidget(QWidget* parent = 0, const char* name = 0);
    ~CQMoietiesTaskWidget();

    virtual bool runTask();
    virtual bool saveTask();
    virtual bool loadTask();
    virtual CCopasiMethod * createMethod( const CCopasiMethod::SubType & type );

protected slots:
    virtual void languageChange();

private:
    void init();
    void destroy();

};

#endif // CQMOIETIESTASKWIDGET_H
