QT       += core gui
#添加多媒体文件
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

HEADERS += \
    include/coordinate.h \
    include/levelwindow.h \
    include/mainwindow.h \
    include/utils.h

SOURCES += \
    main.cpp \
    src/coordinate.cpp \
    src/levelwindow.cpp \
    src/mainwindow.cpp \
    src/utils.cpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
