#############################################################################
##
## Copyright (C) 2010 Mort Yao.
## All rights reserved.
## Contact: Mort Yao (mort.yao@gmail.com)
##
#############################################################################

TARGET        = iGaME
TEMPLATE      = app
CONFIG        = qt debug console
QT            = core gui xml
HEADERS       = MItem.h \
                MItemPainter.hxx \
                MosQt \
                MScene.h \
                MSplashScreen.h \
                MView.h \
                MWidget.h
SOURCES       = iGaME.cpp \
                MItem.cpp \
                MScene.cpp \
                MSplashScreen.cpp \
                MView.cpp \
                MWidget.cpp
RC_FILE       = iGaME.rc
