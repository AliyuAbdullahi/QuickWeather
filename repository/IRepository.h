#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <QString>

class IRepository {
public:
    virtual void requestWeatherData(QString place) = 0;
};

#endif // IREPOSITORY_H
