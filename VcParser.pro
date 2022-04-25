QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attribute.cpp \
    contentline.cpp \
    itemresult.cpp \
    main.cpp \
    mainwindow.cpp \
    mycheckbox.cpp \
    property.cpp \
    propertydefinition.cpp \
    streamreader.cpp \
    value.cpp \
    vcard.cpp

HEADERS += \
    attribute.h \
    contentline.h \
    itemresult.h \
    license.h \
    mainwindow.h \
    manifestconstants.h \
    mycheckbox.h \
    property.h \
    propertydefinition.h \
    streamreader.h \
    value.h \
    vcard.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
