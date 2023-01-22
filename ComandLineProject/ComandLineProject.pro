QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        comanddetails.cpp \
        comandfunc.cpp \
        comandlinefunc.cpp \
        command_handler.cpp \
        hashtable.cpp \
        helpfunc.cpp \
        libary_handler.cpp \
        main.cpp \
    statusController.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    comanddetails.h \
    comandfunc.h \
    comandlinefunc.h \
    command_handler.h \
    gas_cam.h \
    hashtable.h \
    helpfunc.h \
    libary_handler.h \
    queue.h \
    statusController.h



    statusController.h
