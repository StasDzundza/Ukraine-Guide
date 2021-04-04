QT += quick core network

CONFIG += c++17

DEFINES += _CRT_SECURE_NO_WARNINGS QT_DEPRECATED_WARNINGS

RESOURCES += \
        resources/qml.qrc

SOURCES += \
        source/cpp/main.cpp \
        source/cpp/resource_provider.cpp

HEADERS += \
    source/headers/resource_provider.h

INCLUDEPATH += $$PWD/source/headers

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a arm64-v8a x86 x86_64
