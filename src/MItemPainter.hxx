/****************************************************************************
**
** NOTICE: THIS HEADER FILE IS INTENDED TO BE EXTENSIBLE
**
** MosQt 0.10.06 alpha (2010 Oct 6)
**
** Copyright (C) 2010 Mort Yao.
** All rights reserved.
** Contact: Mort Yao (mort.yao@gmail.com)
**
****************************************************************************/

#ifndef MItemPainter_hxx
#define MItemPainter_hxx

#include "MItem.h"

#include <QPainter>

QPainter* MItem::painter()
{
    QPainter* tempPainter;

    if (this->category() == "democat") {

    } else
        tempPainter = 0;

    return tempPainter;
}

#endif
