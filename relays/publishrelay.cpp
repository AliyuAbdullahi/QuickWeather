#include "relays/publishrelay.h"


PublishRelay::PublishRelay()
{
    subscribers = new QVector<Isubscriber*>();
}

void PublishRelay::accept(const WeatherResponse &data)
{
    for (int i = 0; i < subscribers->count(); i++)
    {
        auto subscriber =  subscribers->at(i);
        subscriber->accept(data);
    }
}

void PublishRelay::subscribe(Isubscriber& subscriber)
{
    subscribers->append(&subscriber);
}
