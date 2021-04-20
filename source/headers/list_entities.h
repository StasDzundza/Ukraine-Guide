#pragma once

#include <QObject>
#include <QString>

struct LocalityListEntity {
    QString mKeyName, mUkrName, mEngName, mType;
    double mArea;
    int mPopulation;
};

struct EstablishmentsListEntity {
    QString mUkrName, mEngName, mType, mMoreInfoUrl;
};

Q_DECLARE_METATYPE(LocalityListEntity);
Q_DECLARE_METATYPE(EstablishmentsListEntity);
