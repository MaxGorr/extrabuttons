QT       += core gui widgets xml xmlpatterns

TARGET = XtraBtns
TEMPLATE = app

SOURCES += \
    main.cpp \
    ControlButton.cpp \
    EditButton.cpp \
    ExtraButton.cpp \
    MainWindow.cpp \
    Parser.cpp \
    Path.cpp \
    VariablesManager.cpp

HEADERS += \
    ControlButton.h \
    EditButton.h \
    ExtraButton.h \
    MainWindow.h \
    Parser.h \
    Path.h \
    VariablesManager.h

win32:RC_FILE = icon.rc
win32-g++:LIBS += libUser32
win32-msvc*:LIBS += User32.lib

RESOURCES += \
    resoures.qrc
