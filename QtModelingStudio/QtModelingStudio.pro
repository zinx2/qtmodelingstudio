#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T21:59:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtModelingStudio
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


#SOURCES = $$files(*.cpp, true)
#HEADERS = $$files(*.h, true)
VPATH += ./src
SOURCES += \
design.cpp \
list_widget.cpp \
main.cpp \
mainwindow.cpp \
model_editor.cpp \
widget_adjustbar.cpp \
widget_editor.cpp \
widget_explorer.cpp \
widget_info.cpp \

HEADERS += \
abstract_list_model.h \
db_manager.h \
design.h \
item_model.h \
list_widget.h \
list_widget_item.h \
mainwindow.h \
model_editor.h \
qheader.h \
widget_adjustbar.h \
widget_editor.h \
widget_explorer.h \
widget_info.h \
wrapped_widget.h \

FORMS += \
        mainwindow.ui
