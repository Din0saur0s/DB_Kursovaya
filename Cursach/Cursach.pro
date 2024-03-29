QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    tablegroups.cpp \
    tablesmeny.cpp \
    tablestrotryady.cpp \
    tablestudents.cpp \
    tableworks.cpp

HEADERS += \
    login.h \
    mainwindow.h \
    tablegroups.h \
    tablesmeny.h \
    tablestrotryady.h \
    tablestudents.h \
    tableworks.h

FORMS += \
    login.ui \
    mainwindow.ui \
    tablegroups.ui \
    tablesmeny.ui \
    tablestrotryady.ui \
    tablestudents.ui \
    tableworks.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
