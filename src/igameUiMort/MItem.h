/****************************************************************************
**
** MosQt 0.10.14 alpha (2010 Oct 14)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#ifndef MItem_h
#define MItem_h

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QVariant>
#include <QGraphicsSceneMouseEvent>
#include "SpeciesData.h"

class MScene;
class MItem : public QGraphicsItem {

public:
	MItem(SPECIESTYPE type = SPEC_COMPARTMENT);
	MItem(const QString& filename, SPECIESTYPE type=SPEC_COMPARTMENT);
    virtual ~MItem();

    QRectF outlineRect() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainter* painter();

    void renew();

    const QString& id() { return m_id; }
    void setId(QString id) 
	{ 
		m_id = id; 
		setText(m_id); 
		this->renew(); 
	}

    QString name() { return m_name; }
    void setName(QString name) { m_name = name; this->renew(); }

    QString category() { return m_category; }
    void setCategory(QString category) { m_category = category; this->renew(); }



    QColor color() { return m_color; }
    void setColor(QColor color) { m_color = color; this->renew(); }

    qreal width() { return m_width; }
    void setWidth(qreal width) { m_width = width; this->renew(); }

    qreal height() { return m_height; }
    void setHeight(qreal height) { m_height = height; this->renew(); }

    qreal padding() { return m_padding; }
    void setPadding(qreal padding) { m_padding = padding; this->renew(); }

    qreal margin() { return m_margin; }
    void setMargin(qreal margin) { m_margin = margin; this->renew(); }



    bool isSelectable() { return m_isSelectable; }
    void setSelectable(bool isSelectable) { m_isSelectable = isSelectable; this->renew(); }

    bool isMouseOverSelectable() { return m_isMouseOverSelectable; }
    void setMouseOverSelectable(bool isMouseOverSelectable) { m_isMouseOverSelectable = isMouseOverSelectable; this->renew(); }

    bool isMovable() { return m_isMovable; }
    void setMovable(bool isMovable) { m_isMovable = isMovable; this->renew(); }



    QColor outlineColor() { return m_outlineColor; }
    void setOutlineColor(QColor outlineColor) { m_outlineColor = outlineColor; this->renew(); }

    int outlineWidth() { return m_outlineWidth; }
    void setOutlineWidth(int outlineWidth) { m_outlineWidth = outlineWidth; this->renew(); }

    Qt::PenStyle outlineStyle() { return m_outlineStyle; }
    void setOutlineStyle(Qt::PenStyle outlineStyle) { m_outlineStyle = outlineStyle; this->renew(); }

    bool isOutlineAvailable() { return m_isOutlineAvailable; }
    void setOutlineAvailable(bool isOutlineAvailable) { m_isOutlineAvailable = isOutlineAvailable; this->renew(); }



    QString text() { return m_text; }
    void setText(QString text) { m_text = text; this->renew(); }

    QFont textFont() { return m_textFont; }
    void setTextFont(QFont textFont) { m_textFont = textFont; this->renew(); }

    QColor textColor() { return m_textColor; }
    void setTextColor(QColor textColor) { m_textColor = textColor; this->renew(); }

    bool isTextVisible() { return m_isTextVisible; }
    void setTextVisible(bool isTextVisible) { m_isTextVisible = isTextVisible; this->renew(); }



    QString alternativeText() { return m_alternativeText; }
    void setAlternativeText(QString alternativeText) { m_alternativeText = alternativeText; this->renew(); }

    QFont alternativeTextFont() { return m_alternativeTextFont; }
    void setAlternativeTextFont(QFont alternativeTextFont) { m_alternativeTextFont = alternativeTextFont; this->renew(); }

    QColor alternativeTextColor() { return m_alternativeTextColor; }
    void setAlternativeTextColor(QColor alternativeTextColor) { m_alternativeTextColor = alternativeTextColor; this->renew(); }

    bool isAlternativeTextAvailable() { return m_isAlternativeTextAvailable; }
    void setAlternativeTextAvailable(bool isAlternativeTextAvailable) { m_isAlternativeTextAvailable = isAlternativeTextAvailable; this->renew(); }



    QString figure() { return m_figure; }
    void setFigure(QString figure) { m_figure = figure; setFigureVisible(true); }

    QColor figureColor() { return m_figureColor; }
    void setFigureColor(QColor figureColor) { m_figureColor = figureColor; this->renew(); }

    bool isFigureVisible() { return m_isFigureVisible; }
    void setFigureVisible(bool isFigureVisible) { m_isFigureVisible = isFigureVisible; this->renew(); }



    QString alternativeFigure() { return m_alternativeFigure; }
    void setAlternativeFigure(QString alternativeFigure) { m_alternativeFigure = alternativeFigure; setAlternativeFigureAvailable(true); }

    QColor alternativeFigureColor() { return m_alternativeFigureColor; }
    void setAlternativeFigureColor(QColor alternativeFigureColor) { m_alternativeFigureColor = alternativeFigureColor; this->renew(); }

    bool isAlternativeFigureAvailable() { return m_isAlternativeFigureAvailable; }
    void setAlternativeFigureAvailable(bool isAlternativeFigureAvailable) { m_isAlternativeFigureAvailable = isAlternativeFigureAvailable; this->renew(); }



    QString pixmap() { return m_pixmap; }
    void setPixmap(QString pixmap) { m_pixmap = pixmap; setPixmapVisible(true); }

    bool isPixmapVisible() { return m_isPixmapVisible; }
    void setPixmapVisible(bool isPixmapVisible) { m_isPixmapVisible = isPixmapVisible; this->renew(); }



    QString alternativePixmap() { return m_alternativePixmap; }
    void setAlternativePixmap(QString alternativePixmap) { m_alternativePixmap = alternativePixmap; setAlternativePixmapAvailable(true); }

    bool isAlternativePixmapAvailable() { return m_isAlternativePixmapAvailable; }
    void setAlternativePixmapAvailable(bool isAlternativePixmapAvailable) { m_isAlternativePixmapAvailable = isAlternativePixmapAvailable; this->renew(); }



    QString image() { return m_image; }
    void setImage(QString image) { m_image = image; setImageVisible(true); }

    bool isImageVisible() { return m_isImageVisible; }
    void setImageVisible(bool isImageVisible) { m_isImageVisible = isImageVisible; this->renew(); }



    QString alternativeImage() { return m_alternativeImage; }
    void setAlternativeImage(QString alternativeImage) { m_alternativeImage = alternativeImage; setAlternativeImageAvailable(true); }

    bool isAlternativeImageAvailable() { return m_isAlternativeImageAvailable; }
    void setAlternativeImageAvailable(bool isAlternativeImageAvailable) { m_isAlternativeImageAvailable = isAlternativeImageAvailable; this->renew(); }

	MScene* getScene();
	void setScene(MScene* sce);

	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

	int sceneId() {return sene_id; }
	void setSceneId(int id) { sene_id = id; }

	SPECIESTYPE type() { return m_type; }

protected:
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value);

    //void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    //void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	int sene_id;
    QString m_id;
    QString m_name;
    QString m_category;

    QColor m_color;
    qreal m_width;
    qreal m_height;
    qreal m_padding;
    qreal m_margin;

    bool m_isSelectable;
    bool m_isMouseOverSelectable;
    bool m_isMovable;

    QColor m_outlineColor;
    int m_outlineWidth;
    Qt::PenStyle m_outlineStyle;
    bool m_isOutlineAvailable;

    QString m_text;
    QFont m_textFont;
    QColor m_textColor;
    bool m_isTextVisible;

    QString m_alternativeText;
    QFont m_alternativeTextFont;
    QColor m_alternativeTextColor;
    bool m_isAlternativeTextAvailable;

    QString m_figure;
    QColor m_figureColor;
    bool m_isFigureVisible;

    QString m_alternativeFigure;
    QColor m_alternativeFigureColor;
    bool m_isAlternativeFigureAvailable;

    QString m_pixmap;
    bool m_isPixmapVisible;

    QString m_alternativePixmap;
    bool m_isAlternativePixmapAvailable;

    QString m_image;
    bool m_isImageVisible;

    QString m_alternativeImage;
    bool m_isAlternativeImageAvailable;

	MScene* m_scene;
	SPECIESTYPE m_type;
};

#endif
