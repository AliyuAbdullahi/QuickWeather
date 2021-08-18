#ifndef PUBLISHRELAY_H
#define PUBLISHRELAY_H

#include <QVector>
#include "ui/Isubscriber.h"
#include "models/WeatherResponse.h"

/**
 * @brief The PublishRelay is a subject observer pattern object that publishes events to all subscribers.
 * Smart Pointers isn't used here because Qt favor raw pointers on UI
 * <a href="response for why https://stackoverflow.com/questions/34433435/why-dont-the-official-qt-examples-and-tutorials-use-smart-pointers">
 * See this Stack Overflow response for details
 * </a>
 */
class PublishRelay
{
public:
    PublishRelay();
    void accept(const WeatherResponse &data);
    void subscribe(Isubscriber& subscriber);

private:
    QVector<Isubscriber*> *subscribers;
};

#endif // PUBLISHRELAY_H
