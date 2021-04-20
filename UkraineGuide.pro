QT += quick core network svg webview quickcontrols2

CONFIG += c++17

DEFINES += _CRT_SECURE_NO_WARNINGS QT_DEPRECATED_WARNINGS

RESOURCES += \
        resources/qml.qrc \
        resources/icons.qrc \
        resources/app_data.qrc

SOURCES += \
        source/cpp/application.cpp \
        source/cpp/locality_data_provider.cpp \
        source/cpp/locality_list_model.cpp \
        source/cpp/establishments_list_model.cpp \
        source/cpp/locality_model.cpp \
        source/cpp/main.cpp

HEADERS += \
    source/headers/application.h \
    source/headers/list_entities.h \
    source/headers/locality_data_provider.h \
    source/headers/locality_list_model.h \
    source/headers/establishments_list_model.h \
    source/headers/locality_model.h \
    source/headers/locality_type.h

INCLUDEPATH += $$PWD/source/headers

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += \
                $$PWD/ \
                $$PWD/resources \
                $$PWD/resources/qml \
                $$PWD/resources/app_data


# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = arm64-v8a #x86 x86_64 armeabi-v7a

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
android: include(C:/Users/STAS/AppData/Local/Android/Sdk/android_openssl/openssl.pri) # FIXME add 3rdparty static lib
