QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addauthordialog.cpp \
    addbookdialog.cpp \
    adduserdialog.cpp \
    admindatawidget.cpp \
    book.cpp \
    bookdao.cpp \
    bookwidget.cpp \
    changeauthordialog.cpp \
    changelogindialog.cpp \
    changepassworddialog.cpp \
    databasemanager.cpp \
    editbookdialog.cpp \
    edituserdialog.cpp \
    librarydatawidget.cpp \
    loan.cpp \
    loandao.cpp \
    loanwidget.cpp \
    login.cpp \
    logindao.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    reservation.cpp \
    reservationadminwidget.cpp \
    reservationdao.cpp \
    reservationwidget.cpp \
    searchwidget.cpp \
    sha256.cpp \
    user.cpp \
    userdao.cpp \
    userdatawidget.cpp \
    userloansdialog.cpp \
    usersadminwidget.cpp \
    userwidget.cpp

HEADERS += \
    addauthordialog.h \
    addbookdialog.h \
    adduserdialog.h \
    admindatawidget.h \
    book.h \
    bookdao.h \
    bookwidget.h \
    changeauthordialog.h \
    changelogindialog.h \
    changepassworddialog.h \
    databasemanager.h \
    editbookdialog.h \
    edituserdialog.h \
    librarydatawidget.h \
    loan.h \
    loandao.h \
    loanwidget.h \
    login.h \
    logindao.h \
    mainwindow.h \
    person.h \
    reservation.h \
    reservationadminwidget.h \
    reservationdao.h \
    reservationwidget.h \
    searchwidget.h \
    sha256.h \
    user.h \
    userdao.h \
    userdatawidget.h \
    userloansdialog.h \
    usersadminwidget.h \
    userwidget.h

FORMS += \
    addauthordialog.ui \
    addbookdialog.ui \
    adduserdialog.ui \
    admindatawidget.ui \
    bookwidget.ui \
    changeauthordialog.ui \
    changelogindialog.ui \
    changepassworddialog.ui \
    editbookdialog.ui \
    edituserdialog.ui \
    librarydatawidget.ui \
    loanwidget.ui \
    login.ui \
    mainwindow.ui \
    reservationadminwidget.ui \
    reservationwidget.ui \
    searchwidget.ui \
    userdatawidget.ui \
    userloansdialog.ui \
    usersadminwidget.ui \
    userwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
