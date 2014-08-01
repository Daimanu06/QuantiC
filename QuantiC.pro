message("This project requires Qt version 5.1 and C++11")

lessThan(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 1) {
	error("This project require at least Qt 5.1")
}

#### Modules ####
QT += core gui xml widgets

#### Compiler settings ####
TARGET   = QuantiC
TEMPLATE = app
CONFIG  += C++11
#CONFIG  += static
#QMAKE_CXXFLAGS += -lgmp -lgmpxx
#QMAKE_LFLAGS += -lgmp -lgmpxx

#LIBS += gmpxx gmp

OBJECTS_DIR = obj/
MOC_DIR = moc/
#DESTDIR = bin/


#### Files ####
HEADERS += \
	mainwindow.h \
	centralwidget.h \
	banner.h \
	stackedwidget.h \
	homewidget.h \
	listwidget.h \
	tilewidget.h \
	tilelayout.h \
	quantitywidget.h \
	unitwidget.h \
	numberinput.h \
	prefixwidget.h \
	dialogabout.h \
	dialogsettings.h \
	browsefileswidget.h \
	data.h \
	datamanager.h \
	settings.h

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	centralwidget.cpp \
	banner.cpp \
	stackedwidget.cpp \
	homewidget.cpp \
	listwidget.cpp \
	tilewidget.cpp \
	tilelayout.cpp \
	quantitywidget.cpp \
	unitwidget.cpp \
	prefixwidget.cpp \
	numberinput.cpp \
	dialogabout.cpp \
	dialogsettings.cpp \
	browsefileswidget.cpp \
	data.cpp \
	datamanager.cpp \
	settings.cpp

TRANSLATIONS += \
	QuantiC.en.ts \
	QuantiC.fr_FR.ts

#VERSION = 0.5.1
ICON = "res/icon064.png"

linux-g++-32 {
	message("GNU/Linux 32 bits")
}
linux-g++-64 {
	message("GNU/Linux 64 bits")
}
win32 {
	message("Windows 32 bits")
}

RESOURCES += ressources.qrc
