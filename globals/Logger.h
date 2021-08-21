#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <QDebug>

struct Logger {
    template<typename T>
    static void warn(T &messageData) {
        qWarning() << messageData;
    }

    template<typename T>
    static void warn(T &key, T &messageData) {
        qWarning() << key << messageData;
    }

    template<typename T>
    static void debug(T &messageData) {
        qDebug() << messageData;
    }

    template<typename T>
    static void debug(T &key, T &messageData) {
        qDebug() << key <<  messageData;
    }

    template<typename T>
    static void error(T &data) {
        qDebug() << "Error : " << data;
    }
};

#endif // LOGGER_H
