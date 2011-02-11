#include "SetCopasiWidget.h"
#include <QFileDialog>

SetCopasiWidget::SetCopasiWidget(QDialog* parent)
	:QDialog(parent)
{
	m_path = "";

	b_cancel = false;

	ui.setupUi(this);
	connect(ui.button_cancel, SIGNAL(pressed()), 
			                     this, SLOT(cancel()));
	connect(ui.button_ok, SIGNAL(pressed()), 
			                     this, SLOT(finish()));
	connect(ui.button_search, SIGNAL(pressed()), 
			                     this, SLOT(search()));
}

const QString SetCopasiWidget::getCopasiPath()
{
	exec();

	return ui.textEdit_path->text();
}

void SetCopasiWidget::finish()
{
	close();
}

void SetCopasiWidget::cancel()
{
	b_cancel = true;
	close();
}

bool SetCopasiWidget::isCanceled()
{
	return b_cancel;
}

void SetCopasiWidget::search()
{
	QString path_name = QFileDialog::getOpenFileName(this);
	ui.textEdit_path->setText(path_name);
}
