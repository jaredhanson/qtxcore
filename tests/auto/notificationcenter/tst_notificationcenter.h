#ifndef TST_NOTIFICATIONCENTER_H
#define TST_NOTIFICATIONCENTER_H

#include "notificationcenter.h"
#include <QtTest/QtTest>

QTX_USE_NAMESPACE


class tst_NotificationCenter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    
private:
    //AppcastEnclosure *mEnclosure;
};

#endif // TST_NOTIFICATIONCENTER_H
