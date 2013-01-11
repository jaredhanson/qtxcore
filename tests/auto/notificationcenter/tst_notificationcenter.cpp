#include "tst_notificationcenter.h"


void tst_NotificationCenter::init()
{
    mNotificationCenter = new NotificationCenter();
    mPoster = new MockPoster();
    mPoster->setNotificationCenter(mNotificationCenter);
}

void tst_NotificationCenter::cleanup()
{
    if (mPoster) {
        delete mPoster;
        mPoster = 0;
    }

    if (mNotificationCenter) {
        delete mNotificationCenter;
        mNotificationCenter = 0;
    }
}

void tst_NotificationCenter::observeSpecificPosterAndNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    obs->observe(mPoster, "notify");
    mPoster->post("notify");
    QCOMPARE(obs->count(), 1);
    mPoster->post("no-notify");
    QCOMPARE(obs->count(), 1);
    mPoster->post("notify");
    QCOMPARE(obs->count(), 2);
    
    delete obs;
}

void tst_NotificationCenter::unobserveSpecificPosterAndNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    obs->observe(mPoster, "notify");
    mPoster->post("notify");
    QCOMPARE(obs->count(), 1);
    
    obs->unobserve(mPoster, "notify");
    mPoster->post("notify");
    QCOMPARE(obs->count(), 1);
    
    delete obs;
}


QTEST_APPLESS_MAIN(tst_NotificationCenter)
