#ifndef _SET_COPASI_WIDGET_H_
#define _SET_COPASI_WIDGET_H_

#include <QWidget>
#include "ui_SetCopasiPath.h"

class SetCopasiWidget: public QDialog
{
	Q_OBJECT
	public:
		SetCopasiWidget(QDialog *parent = NULL);
		const QString getCopasiPath();
		bool isCanceled();

	private:
		QString m_path;
		bool b_cancel;
		Ui::SetCopasiPath ui;

		private slots:
			void finish();
		void search();
		void cancel();
};

#endif
