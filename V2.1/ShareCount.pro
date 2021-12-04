QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cagnotte.cpp \
    compte.cpp \
    comptePartage.cpp \
    connexion.cpp \
    gestionnaireDialogue.cpp \
    serveurMail.cpp \
    shareCount.cpp \
    connexioninscription.cpp \
    inscription.cpp \
    main.cpp

HEADERS += \
    cagnotte.h \
    compte.h \
    comptePartage.h \
    connexion.h \
    gestionnaireDialogue.h \
    serveurMail.h \
    shareCount.h \
    connexioninscription.h \
    inscription.h \
    gestionnaireBDD.h

FORMS += \
    connexion.ui \
    connexioninscription.ui \
    inscription.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TEMPLATE = app
CONFIG += console
