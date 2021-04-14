#pragma once

#include <QObject>
#include <QString>

struct LocalityListEntity {
    QString mKeyName, mUkrName, mEngName, mType;
};

Q_DECLARE_METATYPE(LocalityListEntity);
