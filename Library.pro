QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adduserdialog.cpp \
    admindatawidget.cpp \
    book.cpp \
    bookdao.cpp \
    bookwidget.cpp \
    changelogindialog.cpp \
    changepassworddialog.cpp \
    databasemanager.cpp \
    edituserdialog.cpp \
    librarydatawidget.cpp \
    login.cpp \
    logindao.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    searchwidget.cpp \
    sha256.cpp \
    user.cpp \
    userdao.cpp \
    userdatawidget.cpp \
    usersadminwidget.cpp \
    userwidget.cpp

HEADERS += \
    adduserdialog.h \
    admindatawidget.h \
    book.h \
    bookdao.h \
    bookwidget.h \
    changelogindialog.h \
    changepassworddialog.h \
    databasemanager.h \
    edituserdialog.h \
    librarydatawidget.h \
    login.h \
    logindao.h \
    mainwindow.h \
    person.h \
    searchwidget.h \
    sha256.h \
    user.h \
    userdao.h \
    userdatawidget.h \
    usersadminwidget.h \
    userwidget.h

FORMS += \
    adduserdialog.ui \
    admindatawidget.ui \
    bookwidget.ui \
    changelogindialog.ui \
    changepassworddialog.ui \
    edituserdialog.ui \
    librarydatawidget.ui \
    login.ui \
    mainwindow.ui \
    searchwidget.ui \
    userdatawidget.ui \
    usersadminwidget.ui \
    userwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
