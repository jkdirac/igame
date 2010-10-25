/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#include "MItem.h"
#include "MItemPainter.hxx"

#include <QFont>
#include <QRectF>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPen>
#include <QPixmap>
#include <QGraphicsItem>
#include <QImage>
#include <QStyle>
#include <QGraphicsSceneMouseEvent>
#include <QXmlStreamReader>

#include <iostream>
#include <QDebug>

// Class MItem constructor
MItem::MItem()
    : m_id("")
    , m_name("")
    , m_category("")

    , m_color(Qt::black)
    , m_width(100)
    , m_height(100)
    , m_padding(0)
    , m_margin(0)

    , m_isSelectable(false)
    , m_isMouseOverSelectable(false)
    , m_isMovable(false)

    , m_outlineColor(Qt::blue)
    , m_outlineWidth(5)
    , m_outlineStyle(Qt::SolidLine)
    , m_isOutlineAvailable(false)

    , m_text("")
    , m_textFont(QFont::QFont("Arial", 10, QFont::Normal))
    , m_textColor(Qt::red)
    , m_isTextVisible(true)

    , m_alternativeText("")
    , m_alternativeTextFont(QFont::QFont("Arial", 10, QFont::Bold))
    , m_alternativeTextColor(Qt::red)
    , m_isAlternativeTextAvailable(false)

    , m_figure("RECTANGLE")
    , m_figureColor(Qt::black)
    , m_isFigureVisible(false)

    , m_alternativeFigure("")
    , m_alternativeFigureColor(Qt::black)
    , m_isAlternativeFigureAvailable(false)

    , m_pixmap("")
    , m_isPixmapVisible(false)

    , m_alternativePixmap("")
    , m_isAlternativePixmapAvailable(false)

    , m_image("")
    , m_isImageVisible(false)

    , m_alternativeImage("")
    , m_isAlternativeImageAvailable(false)
{
    this->renew();
}

MItem::MItem(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "xml file open failed: " << fileName << " " << file.error();
        return;
	}

    QXmlStreamReader reader(&file);

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            QString name = reader.name().toString();

            if (reader.attributes().hasAttribute("id"))
                setId(reader.attributes().value("id").toString());

            if (reader.attributes().hasAttribute("name"))
                setName(reader.attributes().value("name").toString());
            else
                setText(name);

            if (reader.attributes().hasAttribute("category"))
                setCategory(reader.attributes().value("category").toString());

            if (reader.attributes().hasAttribute("x"))
                setX(reader.attributes().value("x").toString().toDouble());
            else
                setX(200);

            if (reader.attributes().hasAttribute("y"))
                setY(reader.attributes().value("y").toString().toDouble());
            else
                setY(50);

            if (reader.attributes().hasAttribute("zValue"))
                setZValue(reader.attributes().value("zValue").toString().toDouble());

            if (reader.attributes().hasAttribute("toolTip"))
                setToolTip(reader.attributes().value("toolTip").toString());

            if (reader.attributes().hasAttribute("isVisible"))
                setVisible(reader.attributes().value("isVisible").toString().toInt());

            if (reader.attributes().hasAttribute("color"))
                setColor(QColor(reader.attributes().value("color").toString()));

            if (reader.attributes().hasAttribute("width"))
                setWidth(reader.attributes().value("width").toString().toDouble());
            else
                setWidth(100);

            if (reader.attributes().hasAttribute("height"))
                setHeight(reader.attributes().value("height").toString().toDouble());
            else
                setHeight(50);

            if (reader.attributes().hasAttribute("isSelectable"))
                setSelectable(reader.attributes().value("isSelectable").toString().toInt());
            else
                setSelectable(true);

            if (reader.attributes().hasAttribute("isMouseOverSelectable"))
                setMouseOverSelectable(reader.attributes().value("isMouseOverSelectable").toString().toInt());
            else
                setMouseOverSelectable(false);

            if (reader.attributes().hasAttribute("isMovable"))
                setMovable(reader.attributes().value("isMovable").toString().toInt());
            else
                setMovable(true);

            if (reader.attributes().hasAttribute("isOutlineAvailable"))
                setOutlineAvailable(reader.attributes().value("isOutlineAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("outlineColor"))
                setOutlineColor(QColor(reader.attributes().value("outlineColor").toString()));

            if (reader.attributes().hasAttribute("outlineWidth"))
                setOutlineWidth(reader.attributes().value("outlineWidth").toString().toDouble());

            if (reader.attributes().hasAttribute("isFigureVisible"))
                setFigureVisible(reader.attributes().value("isFigureVisible").toString().toInt());

            if (reader.attributes().hasAttribute("figure"))
                setFigure(reader.attributes().value("figure").toString());

            if (reader.attributes().hasAttribute("figureColor"))
                setFigureColor(QColor(reader.attributes().value("figureColor").toString()));

            if (reader.attributes().hasAttribute("isAlternativeFigureAvailable"))
                setAlternativeFigureAvailable(reader.attributes().value("isAlternativeFigureAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeFigure"))
                setAlternativeFigure(reader.attributes().value("alternativeFigure").toString());

            if (reader.attributes().hasAttribute("alternativeFigureColor"))
                setAlternativeFigureColor(QColor(reader.attributes().value("alternativeFigureColor").toString()));

            if (reader.attributes().hasAttribute("isTextVisible"))
                setTextVisible(reader.attributes().value("isTextVisible").toString().toInt());

            if (reader.attributes().hasAttribute("text"))
                setText(reader.attributes().value("text").toString());
            else
                setText(name);

            if (reader.attributes().hasAttribute("textColor"))
                setTextColor(QColor(reader.attributes().value("textColor").toString()));

            if (reader.attributes().hasAttribute("isAlternativeTextAvailable"))
                setAlternativeTextAvailable(reader.attributes().value("isAlternativeTextAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeText"))
                setAlternativeText(reader.attributes().value("alternativeText").toString());

            if (reader.attributes().hasAttribute("alternativeTextColor"))
                setAlternativeTextColor(QColor(reader.attributes().value("alternativeTextColor").toString()));

            if (reader.attributes().hasAttribute("pixmap"))
                setPixmap(reader.attributes().value("pixmap").toString());

            if (reader.attributes().hasAttribute("isPixmapVisible"))
                setPixmapVisible(reader.attributes().value("isPixmapVisible").toString().toInt());

            if (reader.attributes().hasAttribute("alternativePixmap"))
                setAlternativePixmap(reader.attributes().value("alternativePixmap").toString());

            if (reader.attributes().hasAttribute("isAlternativePixmapAvailable"))
                setAlternativePixmapAvailable(reader.attributes().value("isAlternativePixmapAvailable").toString().toInt());

            if (reader.attributes().hasAttribute("image"))
                setImage(reader.attributes().value("image").toString());

            if (reader.attributes().hasAttribute("isImageVisible"))
                setImageVisible(reader.attributes().value("isImageVisible").toString().toInt());

            if (reader.attributes().hasAttribute("alternativeImage"))
                setAlternativeImage(reader.attributes().value("alternativeImage").toString());

            if (reader.attributes().hasAttribute("isAlternativeImageAvailable"))
                setAlternativeImageAvailable(reader.attributes().value("isAlternativeImageAvailable").toString().toInt());

        } else if (reader.isEndElement())
		{
		}
        else if (reader.isCharacters()) {
            QString characters = reader.text().toString();

            if (characters != "" && characters != "\n" && characters != "\r" && characters !="\r\n")
                setData(0, characters);
        }

        reader.readNext();
    }

	renew();
}

// Class MItem destructor
MItem::~MItem()
{
    //foreach(LinkT *link, myLinkT)
    //    delete link;
}



// Return outline rectangle
QRectF MItem::outlineRect() const
{
    QRectF rect(this->x(), this->y(), m_width, m_height);

    rect.adjust(-m_padding, -m_padding, +m_padding, +m_padding);
    rect.translate(-rect.center());

    return rect;
}

// Return bounding rectangle
QRectF MItem::boundingRect() const
{
    return outlineRect().adjusted(-m_margin, -m_margin, +m_margin, +m_margin);
}

// Shape control
QPainterPath MItem::shape() const
{
    QPainterPath path;
    QRectF rect = this->outlineRect();

    if (m_figure == "RECTANGLE")
        path.addRect(rect);
    else if (m_figure == "ELLIPSE")
        path.addEllipse(rect);
    else if (m_figure == "ROUND_RECTANGLE")
        path.addRoundRect(rect, 100 * 12 / int(rect.width()), 100 * 12 / int(rect.height()));

    return path;
}

// Paint control
void MItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    if (!this->isVisible())
        return;
    
    if (this->painter()) {
        painter = this->painter();
        return;
    }

    // initialize
    QRectF rect = this->outlineRect();

    // set painter pen
    QPen pen(m_color);
    if (m_isOutlineAvailable && (option->state & QStyle::State_Selected)) {
        pen.setColor(m_outlineColor);
        pen.setStyle(m_outlineStyle);
        pen.setWidth(m_outlineWidth);
    } else {
        pen.setWidth(0);
    }
    painter->setPen(pen);

    // draw figure & its outline
    if (m_isFigureVisible)
    {
        if (!m_isAlternativeFigureAvailable
            || !(option->state & QStyle::State_Selected)) {
            painter->setBrush(m_figureColor);

            if (m_figure == "RECTANGLE")
                painter->drawRect(rect);
            else if (m_figure == "ELLIPSE")
                painter->drawEllipse(rect);
            else if (m_figure == "ROUND_RECTANGLE")
                painter->drawRoundRect(rect, 100 * 12 / int(rect.width()), 100 * 12 / int(rect.height()));

        } else { // draw alternative figure
            painter->setBrush(m_alternativeFigureColor);

            if (m_alternativeFigure == "RECTANGLE")
                painter->drawRect(rect);
            else if (m_alternativeFigure == "ELLIPSE")
                painter->drawEllipse(rect);
            else if (m_alternativeFigure == "ROUND_RECTANGLE")
                painter->drawRoundRect(rect, 100 * 12 / int(rect.width()), 100 * 12 / int(rect.height()));

        }
    }

    // draw pixmap
    if (m_isPixmapVisible)
    {
        if (!m_isAlternativePixmapAvailable
            || !(option->state & QStyle::State_Selected)) {
            QRectF target(rect);
            QPixmap pixmap(m_pixmap);
            QRectF source(pixmap.rect());

            painter->drawPixmap(rect, pixmap, source);

        } else { // draw alternative pixmap
            QRectF target(rect);
            QPixmap pixmap(m_alternativePixmap);
            QRectF source(pixmap.rect());

            painter->drawPixmap(rect, pixmap, source);

        }
    }

    // draw image
    if (m_isImageVisible)
    {
        if (!m_isAlternativeImageAvailable
            || !(option->state & QStyle::State_Selected)) {
            QRectF target(rect);
            QImage image(m_image);
            QRectF source(image.rect());

            painter->drawImage(rect, image, source);

        } else { // draw alternative image
            QRectF target(rect);
            QImage image(m_alternativeImage);
            QRectF source(image.rect());

            painter->drawImage(rect, image, source);

        }
    }

    // draw text
    if (m_isTextVisible)
    {
        if (!m_isAlternativeTextAvailable
            || !(option->state & QStyle::State_Selected)) {
            painter->setPen(m_textColor);
            painter->setFont(m_textFont);
            painter->drawText(rect, Qt::AlignCenter, m_text);

        } else { // draw alternative text
            painter->setPen(m_alternativeTextColor);
            painter->setFont(m_alternativeTextFont);
            painter->drawText(rect, Qt::AlignCenter, m_alternativeText);

        }
    }

    return;
}



// Renew MItem display
void MItem::renew()
{
    if (m_isSelectable && m_isMovable) {
        this->setFlags(QGraphicsItem::ItemIsSelectable
                       | QGraphicsItem::ItemIsMovable
                       | QGraphicsItem::ItemSendsScenePositionChanges);
    } else if (m_isSelectable) {
        this->setFlags(QGraphicsItem::ItemIsSelectable
                       | QGraphicsItem::ItemSendsScenePositionChanges);
    } else if (m_isMovable) {
        this->setFlags(QGraphicsItem::ItemIsMovable
                       | QGraphicsItem::ItemSendsScenePositionChanges);
    } else
        this->setFlags(QGraphicsItem::ItemSendsScenePositionChanges);

    this->update();

    return;
}



// Process MItem change event
QVariant MItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemPositionHasChanged)
    {
        //foreach (LinkT* link, myLinkT)
        //    link->trackNodes();

    }

    return QGraphicsItem::itemChange(change, value);
}



//Process MItem mouse double click event - formally
void MItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	qDebug() << "double click in mitem";
	return QGraphicsItem::mouseDoubleClickEvent(event);
}

/*
// Process MItem mouse move event - formally
void MItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    return QGraphicsItem::mouseMoveEvent(event);
}

// Process MItem mouse press event - formally
void MItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    return QGraphicsItem::mousePressEvent(event);
}

// Process MItem mouse release event - formally
void MItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    return QGraphicsItem::mouseReleaseEvent(event);
}
*/
