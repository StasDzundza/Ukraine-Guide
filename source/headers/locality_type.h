#pragma once

#include <QJsonDocument>
#include <QQmlEngine>

class LocalityType : public QObject {
    Q_OBJECT

public:
    LocalityType() = default;

    enum Type {
        CITY,
        SETTLEMENT,
        VILLAGE
    };
    Q_ENUMS(Type)

    static void declareQML() {
        qmlRegisterType<LocalityType>("com.UkraineGuide.LocalityType", 1, 0, "LocalityType");
    }
};
