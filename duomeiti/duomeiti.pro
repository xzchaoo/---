#-------------------------------------------------
#
# Project created by QtCreator 2014-07-03T12:30:40
#
#-------------------------------------------------

QT       += core gui \
      multimedia \
      multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = duomeiti
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    layer.cpp \
    myview.cpp \
    gamepanel.cpp \
    gameobject.cpp \
    animation.cpp \
    animationgroup.cpp \
    chainitem.cpp \
    linkservice.cpp \
    musicplayer.cpp \
    timeslot.cpp \
    gametimer.cpp \
    toolmanager.cpp \
    pixmapitem.cpp \
    tooleffect.cpp \
    scorepanel.cpp \
    scoreservice.cpp \
    gametoolbar.cpp \
    iconmanager.cpp \
    gametoolbutton.cpp \
    gametool.cpp \
    icontypedispeltooleffect.cpp \
    tooleffectfactory.cpp \
    gametoolbuttoneffectfactory.cpp \
    bladestormtooleffect.cpp \
    gameicon.cpp \
    settingdialog.cpp \
    gameconfig.cpp \
    animationfunction.cpp \
    spiralfunction.cpp \
    inversespiralfunction.cpp \
    gameiconeffectfactory.cpp \
    gameiconmask.cpp \
    autolinktooleffect.cpp \
    randomvanishtooleffect.cpp \
    iconhinttooleffect.cpp \
    bombtooleffect.cpp \
    randomizeicontooleffect.cpp \
    imageloader.cpp \
    pngsitem.cpp \
    openingshow.cpp \
    controlpanel.cpp \
    gamebutton.cpp \
    basicconfig.cpp \
    gamesaveandrestore.cpp \
    iserializable.cpp

HEADERS  += mainwindow.h \
    layer.h \
    myview.h \
    gamepanel.h \
    gameobject.h \
    Animation.h \
    animationgroup.h \
    chainitem.h \
    linkservice.h \
    musicplayer.h \
    timeslot.h \
    gametimer.h \
    toolmanager.h \
    pixmapitem.h \
    tooleffect.h \
    scorepanel.h \
    scoreservice.h \
    gametoolbar.h \
    iconmanager.h \   
    gametoolbutton.h \
    gametool.h \
    icontypedispeltooleffect.h \
    tooleffectfactory.h \
    gametoolbuttoneffectfactory.h \
    bladestormtooleffect.h \
    gameicon.h \
    settingdialog.h \
    gameconfig.h \
    animationfunction.h \
    spiralfunction.h \
    inversespiralfunction.h \
    gameiconeffectfactory.h \
    gameiconmask.h \
    autolinktooleffect.h \
    randomvanishtooleffect.h \
    iconhinttooleffect.h \
    bombtooleffect.h \
    randomizeicontooleffect.h \
    imageloader.h \
    pngsitem.h \
    openingshow.h \
    controlpanel.h \
    gamebutton.h \
    basicconfig.h \
    gamesaveandrestore.h \
    iserializable.h

FORMS    += mainwindow.ui \
    settingdialog.ui

RESOURCES +=

OTHER_FILES += \
    gametoolbar.txt \
    gametoolbar.cpp.txt \
    iconmanager.h.txt \
    iconmanager.cpp.txt \
    iconrenderer.h.txt \
    iconrenderer.cpp.txt

RC_FILE = myico.rc
