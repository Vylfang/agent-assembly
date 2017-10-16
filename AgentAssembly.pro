TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib -lSDL2
LIBS += -L/usr/local/lib -lSDL2_image
LIBS += -L/usr/local/lib -lSDL2_ttf
LIBS += -L/usr/local/lib -lSDL2_mixer

SOURCES += main.cpp \
    cbullet.cpp \
    ccharacter.cpp \
    ctexture.cpp \
    cplayer.cpp

HEADERS += \
    cbullet.h \
    ccharacter.h \
    ctexture.h \
    cplayer.h



