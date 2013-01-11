#include "mockposter.h"


MockPoster::MockPoster()
    : mNotificationCenter(0)
{
    mNotificationCenter = NotificationCenter::instance();
}

MockPoster::~MockPoster()
{
}

void MockPoster::post(const QString & notification)
{
    mNotificationCenter->post(this, notification);
}

void MockPoster::setNotificationCenter(NotificationCenter *center)
{
    mNotificationCenter = center;
}
