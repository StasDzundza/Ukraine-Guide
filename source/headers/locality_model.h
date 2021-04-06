#pragma once

#include <QObject>
#include <QVector>
#include <QPair>

#include "locality_data_provider.h"

class LocalityModel : public QObject {
public:
    explicit LocalityModel(QObject *parent = nullptr);

    friend class LocalityDataProvider;

private:
    QString mKeyName{}, mUkrName{}, mEngName{};
    QString mOblast{}, mRegion{};
    unsigned int mPopulation{}, mArea{};
    QPair<QString, QString> mCoordinates{};
    QVector<QString> mCityNeighbours{};
    QVector<QString> mSettlementNeighbours{};
    QVector<QString> mVillageNeighbours{};
};
