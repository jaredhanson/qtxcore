TEMPLATE = app
TARGET = tst_notificationcenter

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_notificationcenter.h
SOURCES += tst_notificationcenter.cpp
