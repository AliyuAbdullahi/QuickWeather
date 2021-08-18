QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    relays/publishrelay.cpp \
    parser/jsonobjectparser.cpp \
    globals/appsingleton.cpp \
    main.cpp \
    repository/weatherrepository.cpp \
    ui/mainwindow.cpp \
    ui/weathersummarypresenter.cpp

HEADERS += \
    globals/Logger.h \
    ui/Isubscriber.h \
    globals/UrlBuilder.h \
    models/WeatherObject.h \
    globals/appsingleton.h \
    globals/apputil.h \
    models/WeatherResponse.h \
    parser/jsonobjectparser.h \
    models/City.h \
    relays/publishrelay.h \
    repository/IRepository.h \
    repository/weatherrepository.h \
    ui/WeatherSummaryView.h \
    ui/weathersummarypresenter.h \
    ui/mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
