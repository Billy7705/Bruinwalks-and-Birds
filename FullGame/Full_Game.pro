#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T18:36:38
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Full_Game
TEMPLATE = app

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
        main.cpp \
    game.cpp \
    player.cpp \
    bruinwalk_player.cpp \
    bullet.cpp \
    MyTimer.cpp \
    BruinwalkMiniGame2.cpp \
    TrojanMiniGame1.cpp \
    FlyerObstacle.cpp \
    BirdObstacle.cpp \
    trojans_player.cpp \
    TrojanObstacle.cpp \
    Button.cpp

HEADERS += \
    Player.h \
    BruinwalkMiniGame2.h \
    TrojanMiniGame1.h \
    mytimer.h \
    game.h \
    button.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc

DISTFILES +=
