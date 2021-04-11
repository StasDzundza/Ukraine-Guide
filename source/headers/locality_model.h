#pragma once

#include <QObject>
#include <QVector>
#include <QPair>

#include "locality_data_provider.h"
#include "locality_type.h"

class LocalityModel : public QObject {
    Q_ENUMS(LocalityType::Type)
public:
    explicit LocalityModel(QObject *parent = nullptr);

    friend class LocalityDataProvider;

private:
    QString mKeyName{}, mUkrName{}, mEngName{};
    QString mOblast{}, mRegion{};
    unsigned int mPopulation{}, mArea{};
    QPair<QString, QString> mCoordinates{};
    QVector<QString> mNeighbours{};
    LocalityType mType = LocalityType::CITY;
};
