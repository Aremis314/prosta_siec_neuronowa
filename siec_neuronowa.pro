TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        elementy_nauki.cpp \
        inicjalizacja_sieci.cpp \
        main.cpp \
        nauka_sieci.cpp \
        neuron.cpp \
        obliczanie_bledu.cpp \
        odczyt_plikow.cpp \
        wypiszSIecWKonsoli.cpp

HEADERS += \
    elementy_nauki.h \
    inicjalizacja_sieci.h \
    nauka_sieci.h \
    neuron.h \
    obliczanie_bledu.h \
    odczyt_plikow.h \
    wypiszSIecWKonsoli.h
