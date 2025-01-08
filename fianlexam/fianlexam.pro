QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TRANSLATIONS = calculator_zh_CN.ts calculator_en_US.ts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capacity.cpp \
    chengxuyuan.cpp \
    currency.cpp \
    date.cpp \
    main.cpp \
    mainwindow.cpp \
    normal.cpp \
    science.cpp

HEADERS += \
    capacity.h \
    chengxuyuan.h \
    currency.h \
    date.h \
    mainwindow.h \
    normal.h \
    science.h

FORMS += \
    capacity.ui \
    chengxuyuan.ui \
    currency.ui \
    date.ui \
    mainwindow.ui \
    normal.ui \
    science.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    language.qrc
