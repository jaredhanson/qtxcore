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

void MockObserver::observe()
{
    mNotificationCenter->observe(this, QTX_METHOD(onNotification()));
}

void MockObserver::observe(const QString & notification)
{
    mNotificationCenter->observe(notification, this, QTX_METHOD(onNotification()));
}

void MockObserver::observe(const QObject *poster)
{
    mNotificationCenter->observe(poster, this, QTX_METHOD(onNotification()));
}

void MockObserver::observe(const QObject *poster, const QString & notification)
{
    mNotificationCenter->observe(poster, notification, this, QTX_METHOD(onNotification()));
}

void MockObserver::unobserve()
{
    mNotificationCenter->unobserve(this);
}

void MockObserver::unobserve(const QString & notification)
{
    mNotificationCenter->unobserve(notification, this);
}

void MockObserver::unobserve(const QObject *poster)
{
    mNotificationCenter->unobserve(poster, this);
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
