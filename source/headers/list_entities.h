#pragma once

#include <QObject>
#include <QString>

struct LocalityListEntity {
    QString mKeyName, mUkrName, mEngName, mType;
};

struct EstablishmentsListEntity {
    QString mUkrName, mEngName, mMoreInfoUrl;
};

Q_DECLARE_METATYPE(LocalityListEntity);
Q_DECLARE_METATYPE(EstablishmentsListEntity);
