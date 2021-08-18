#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H

#include "models/WeatherResponse.h"
#include "globals/Logger.h"

class Isubscriber {
public:
    virtual void accept(const WeatherResponse& data) = 0;
    virtual ~Isubscriber() { Logger::debug("Deleting subscriber"); }
};

#endif // ISUBSCRIBER_H
