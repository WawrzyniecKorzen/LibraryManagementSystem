QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    bookdao.cpp \
    bookwidget.cpp \
    changepassworddialog.cpp \
    databasemanager.cpp \
    librarydatawidget.cpp \
    login.cpp \
    logindao.cpp \
    main.cpp \
    mainwindow.cpp \
    sha256.cpp \
    user.cpp \
    userdao.cpp \
    userdatawidget.cpp

HEADERS += \
    book.h \
    bookdao.h \
    bookwidget.h \
    changepassworddialog.h \
    databasemanager.h \
    librarydatawidget.h \
    login.h \
    logindao.h \
    mainwindow.h \
    sha256.h \
    user.h \
    userdao.h \
    userdatawidget.h

FORMS += \
    bookwidget.ui \
    changepassworddialog.ui \
    librarydatawidget.ui \
    login.ui \
    mainwindow.ui \
    userdatawidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
