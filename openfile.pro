#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T17:06:48
#
#-------------------------------------------------

QT       += core gui axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openfile
TEMPLATE = app


SOURCES += main.cpp\
        file.cpp \
    entrance.cpp \
    flietwo.cpp \
    excel.cpp \
    pack.cpp \
    infwrong.cpp \
    wrongdialog_1.cpp \
    wrongdialog_2.cpp

HEADERS  += file.h \
    entrance.h \
    flietwo.h \
    excel.h \
    pack.h \
    infwrong.h \
    wrongdialog_1.h \
    wrongdialog_2.h

INCLUDEPATH += include \

FORMS    += file.ui \
    entrance.ui \
    flietwo.ui \
    infwrong.ui \
    wrongdialog_1.ui \
    wrongdialog_2.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lquazip
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lquazipd
else:unix: LIBS += -L$$PWD/lib/ -lquazip

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
