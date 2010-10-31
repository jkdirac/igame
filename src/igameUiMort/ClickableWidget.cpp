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
	qDebug() << "clickable widget deleted";
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
	}
	else
	{

		//One Item in operation region can create new scene
		if (!getScene()->itemInCompartment(this))
			return;

		m_ownScene = getScene()->itemApplyNewScene(this);
		//    newScene->loadXml(":demoUiXml.ui.xml");
		qDebug() << "new scene id: " << id();
	}

	if (m_senemgr == NULL)
	{
		qDebug() << "m_senemgr pointer NULL ";
	}
	else
	{
		m_senemgr->addNewScene(m_ownScene);
	}
}

void ClickableWidget::deletOwnerScene()
{
	if (m_ownScene)
		delete m_ownScene;
}

/** 
 * @breif  
 *	Disable the SceneItemView in the System tree view
 * 
 * @Param invalid 
 *	invalid the scene and its sub scene if true
 *	ohterwis enable those scenes
 */
void ClickableWidget::invalidOwnerScene(bool invalid)
{
	if (m_ownScene)
	{
		m_ownScene->invalidTree(invalid);
	}
}
