#include "ClickableWidget.h"
#include <QDebug>

ClickableWidget::ClickableWidget(SPECIESTYPE type) : MItem(NULL, type)
	  ,m_senemgr(NULL)
					  , m_ownScene(NULL)
{
	m_senemgr = SceneManager::getSceneManger();
	renew();
}

ClickableWidget::~ClickableWidget()
{
}

ClickableWidget::ClickableWidget(const QString& fileName, SPECIESTYPE type) : MItem(fileName, type)
	  ,m_senemgr(NULL)
					  , m_ownScene(NULL)
{
	m_senemgr = SceneManager::getSceneManger();
	renew();
    return;
}

void ClickableWidget::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "haha mouseDouble click of clickable item";
	QGraphicsItem::mouseDoubleClickEvent(event);

	//One Item only can has a Scene
	if (m_ownScene != NULL)
	{
		qDebug() << "-- item had a scene";
		return;
	}

	//One Item in operation region can create new scene
	if (!getScene()->itemInCompartment(this))
		return;

	m_ownScene = new MScene(NULL, id(), type());
//    newScene->loadXml(":demoUiXml.ui.xml");
	qDebug() << "new scene id: " << id();

	if (m_senemgr == NULL)
	{
		qDebug() << "m_senemgr pointer NULL ";
	}
	else
	{
		m_senemgr->addNewScene(m_ownScene);
	}
}
