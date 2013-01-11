TEMPLATE = app
TARGET = tst_notificationcenter

QT += testlib
macx:CONFIG -= app_bundle

include(../../../mkspecs/test.pri)

HEADERS += tst_notificationcenter.h \
           ../../mock/src/mockobserver.h \
           ../../mock/src/mockposter.h
SOURCES += tst_notificationcenter.cpp \
           ../../mock/src/mockobserver.cpp \
           ../../mock/src/mockposter.cpp
