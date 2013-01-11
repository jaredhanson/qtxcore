#include "mockobserver.h"


MockObserver::MockObserver()
    : mNotificationCenter(0),
      mCount(0)
{
    mNotificationCenter = NotificationCenter::instance();
}

MockObserver::~MockObserver()
{
}

void MockObserver::observe(const QObject *poster, const QString & notification)
{
    mNotificationCenter->observe(poster, notification, this, QTX_METHOD(onNotification()));
}

void MockObserver::unobserve(const QObject *poster, const QString & notification)
{
    mNotificationCenter->unobserve(poster, notification, this);
}

int MockObserver::count() const
{
    return mCount;
}

void MockObserver::setNotificationCenter(NotificationCenter *center)
{
    mNotificationCenter = center;
}

void MockObserver::onNotification()
{
    mCount++;
}
