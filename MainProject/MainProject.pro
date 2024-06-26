QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    communicate.cpp \
    main.cpp \
    canmaster.cpp \
    messageview.cpp

HEADERS += \
    GlobalDataStruct.h \
    canmaster.h \
    communicate.h \
    messageview.h

FORMS += \
    canmaster.ui

TRANSLATIONS += \
    MainProject_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): {
    LIBS += -L$$OUT_PWD/../DeviceIO/release/ -lDeviceIO
    LIBS += -L$$PWD/../DeviceIO/3rd/QsLog/bin -llibQsLog2
    INCLUDEPATH += $$PWD/../DeviceIO/3rd/QsLog/include/
    INCLUDEPATH += $$PWD/../DeviceIO/3rd/pcan/include/
}

else:win32:CONFIG(debug, debug|release): {
LIBS += -L$$OUT_PWD/../DeviceIO/debug/ -lDeviceIO
LIBS += -L$$PWD/../DeviceIO/3rd/QsLog/bin -llibQsLog2
}

else:unix: {
    LIBS += -L$$OUT_PWD/../DeviceIO/ -lDeviceIO
    LIBS += -L$$PWD/../DeviceIO/3rd/QsLog/bin -lQsLog
    INCLUDEPATH += $$PWD/../DeviceIO/3rd/QsLog/include/
}


INCLUDEPATH += $$PWD/../DeviceIO

DEPENDPATH += $$PWD/../DeviceIO

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ModelDataManage/release/ -lModelDataManage
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ModelDataManage/debug/ -lModelDataManage
else:unix: LIBS += -L$$OUT_PWD/../ModelDataManage/ -lModelDataManage

INCLUDEPATH += $$PWD/../ModelDataManage
DEPENDPATH += $$PWD/../ModelDataManage

