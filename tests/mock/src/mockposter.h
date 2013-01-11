#ifndef MOCK_MOCKPOSTER_H
#define MOCK_MOCKPOSTER_H

#include "notificationcenter.h"
#include <QtCore>

QTX_USE_NAMESPACE


class MockPoster : public QObject
{
    Q_OBJECT

public:
    MockPoster();
    ~MockPoster();

    void post(const QString & notification);
    
    void setNotificationCenter(NotificationCenter *center);
    
private:
    NotificationCenter *mNotificationCenter;
};

#endif // MOCK_MOCKPOSTER_H