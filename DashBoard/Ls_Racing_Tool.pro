#-------------------------------------------------
#
# Project created by QtCreator 2022-02-02T00:09:53
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ls_Racing_Tool
TEMPLATE = app
# 下面这行为了消除C4819警告
#QMAKE_CXXFLAGS += /wd"4819"
#添加应用程序图标
RC_ICONS = logo.ico
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        configserial_dialog.cpp \
        main.cpp \
        mainwindow.cpp \
        myqcustomplot.cpp \
        myserialport.cpp \
        qcustomplot.cpp \
        textdata_extract_engine.cpp

HEADERS += \
        configserial_dialog.h \
        mainwindow.h \
        myqcustomplot.h \
        myserialport.h \
        qcustomplot.h \
        textdata_extract_engine.h

FORMS += \
        configserial_dialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#添加第三方开源控件库
INCLUDEPATH += $$PWD/sdk

CONFIG(debug, debug|release){
LIBS += -L$$PWD/sdk/ -lqucd
} else {
LIBS += -L$$PWD/sdk/ -lquc
}
