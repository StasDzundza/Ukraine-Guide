#pragma once

#include <QJsonDocument>
#include <QQmlEngine>

class LocalityType : public QObject {
    Q_OBJECT

public:
    enum Type {
        CITY,
        SETTLEMENT,
        VILLAGE
    };
    Q_ENUMS(Type)

    LocalityType() = default;
    LocalityType(const LocalityType &other){ mType = other.mType; }
    LocalityType(const Type type){ mType = type; }

    LocalityType & operator=(const Type &type){
        mType = type;
        return *this;
    }

    static void declareQML() {
        qmlRegisterType<LocalityType>("com.UkraineGuide.LocalityType", 1, 0, "LocalityType");
    }

private:
    Type mType;
};

Q_DECLARE_METATYPE(LocalityType)
Q_DECLARE_METATYPE(LocalityType::Type)
