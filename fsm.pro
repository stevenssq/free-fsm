TEMPLATE = app
TARGET =fsm

QT -= core
QT -= gui

CONFIG += c++11

LIBS +=  -L$$PWD -lzlog

SOURCES += $$PWD/*.cpp \
                       $$PWD/*.c \
                      $$PWD/threadbase/*.c \
                      $$PWD/signalbase/*.c

HEADERS += $$PWD/*.h \
                       $$PWD/threadbase/*.h \
                       $$PWD/signalbase/*.h
