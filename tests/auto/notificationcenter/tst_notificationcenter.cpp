#include "tst_notificationcenter.h"
#include "../../mock/src/mockposter.h"
#include "../../mock/src/mockobserver.h"


void tst_NotificationCenter::init()
{
    mNotificationCenter = new NotificationCenter();
}

void tst_NotificationCenter::cleanup()
{
    if (mNotificationCenter) {
        delete mNotificationCenter;
        mNotificationCenter = 0;
    }
}

void tst_NotificationCenter::observeAnyPosterAndAnyNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe();
    poster1->post("notify");
    QCOMPARE(obs->count(), 1);
    poster1->post("no-notify");
    QCOMPARE(obs->count(), 2);
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    poster2->post("no-notify");
    QCOMPARE(obs->count(), 4);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::observeAnyPosterAndSpecificNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe("notify");
    poster1->post("notify");
    QCOMPARE(obs->count(), 1);
    poster1->post("no-notify");
    QCOMPARE(obs->count(), 1);
    poster2->post("notify");
    QCOMPARE(obs->count(), 2);
    poster2->post("no-notify");
    QCOMPARE(obs->count(), 2);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::observeSpecificPosterAndAnyNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1);
    poster1->post("notify");
    QCOMPARE(obs->count(), 1);
    poster1->post("no-notify");
    QCOMPARE(obs->count(), 2);
    poster1->post("notify");
    QCOMPARE(obs->count(), 3);
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::observeSpecificPosterAndSpecificNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1, "notify");
    poster1->post("notify");
    QCOMPARE(obs->count(), 1);
    poster1->post("no-notify");
    QCOMPARE(obs->count(), 1);
    poster1->post("notify");
    QCOMPARE(obs->count(), 2);
    poster2->post("notify");
    QCOMPARE(obs->count(), 2);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::unobserveAnyPosterAndAnyNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1, "notify");
    obs->observe(poster1, "notify-again");
    obs->observe(poster2, "notify");
    poster1->post("notify");
    poster1->post("notify-again");
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    obs->unobserve();
    poster1->post("notify");
    QCOMPARE(obs->count(), 3);
    poster1->post("notify-again");
    QCOMPARE(obs->count(), 3);
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::unobserveAnyPosterAndSpecificNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1, "notify");
    obs->observe(poster1, "notify-again");
    obs->observe(poster2, "notify");
    poster1->post("notify");
    poster1->post("notify-again");
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    obs->unobserve("notify");
    poster1->post("notify");
    QCOMPARE(obs->count(), 3);
    poster1->post("notify-again");
    QCOMPARE(obs->count(), 4);
    poster2->post("notify");
    QCOMPARE(obs->count(), 4);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::unobserveSpecificPosterAndAnyNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1, "notify");
    obs->observe(poster1, "notify-again");
    obs->observe(poster2, "notify");
    poster1->post("notify");
    poster1->post("notify-again");
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    obs->unobserve(poster1);
    poster1->post("notify");
    QCOMPARE(obs->count(), 3);
    poster1->post("notify-again");
    QCOMPARE(obs->count(), 3);
    poster2->post("notify");
    QCOMPARE(obs->count(), 4);
    
    delete poster2;
    delete poster1;
    delete obs;
}

void tst_NotificationCenter::unobserveSpecificPosterAndSpecificNotification()
{
    MockObserver *obs = new MockObserver();
    obs->setNotificationCenter(mNotificationCenter);
    
    MockPoster *poster1 = new MockPoster();
    poster1->setNotificationCenter(mNotificationCenter);
    MockPoster *poster2 = new MockPoster();
    poster2->setNotificationCenter(mNotificationCenter);
    
    
    obs->observe(poster1, "notify");
    obs->observe(poster1, "notify-again");
    obs->observe(poster2, "notify");
    poster1->post("notify");
    poster1->post("notify-again");
    poster2->post("notify");
    QCOMPARE(obs->count(), 3);
    
    obs->unobserve(poster1, "notify");
    poster1->post("notify");
    QCOMPARE(obs->count(), 3);
    poster1->post("notify-again");
    QCOMPARE(obs->count(), 4);
    poster2->post("notify");
    QCOMPARE(obs->count(), 5);
    
    delete poster2;
    delete poster1;
    delete obs;
}


QTEST_APPLESS_MAIN(tst_NotificationCenter)
