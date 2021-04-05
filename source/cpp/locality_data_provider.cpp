#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <algorithm>

#include "locality_data_provider.h"
#include "locality_model.h"

namespace  {
static const QString LOCALITY_JSON_PATH = "qrc:/app_data/locality.json";
}

LocalityDataProvider::LocalityDataProvider() {
    QJsonParseError parseError;
    QFile fin(LOCALITY_JSON_PATH);
    fin.open(QIODevice::ReadOnly);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fin.readAll(), &parseError);
    Q_ASSERT(parseError.error == QJsonParseError::NoError);
    mLocalitiesObject = jsonDoc.object();
}

void LocalityDataProvider::fillLocalityModel(const QString &keyName, LocalityModel &model) {
    const QJsonObject &localityObject = mLocalitiesObject.value(keyName).toObject();
    model.mEngName = localityObject.value("engName").toString("");
    model.mUkrName = localityObject.value("ukrName").toString("");
    model.mPopulation = localityObject.value("population").toInt(0);
    model.mArea = localityObject.value("area").toInt(0);
    model.mOblast = localityObject.value("oblast").toString("");
    model.mRegion = localityObject.value("region").toString("");
    const QJsonArray &coordinatesArray = localityObject.value("coordinates").toArray();
    model.mCoordinates = {coordinatesArray.at(0).toString("0 0 0"), coordinatesArray.at(1).toString("0 0 0")};

    const QJsonArray &cityNeighboursArray = localityObject.value("city-neighbours").toArray();
    model.mCityNeighbours.clear();
    std::transform(cityNeighboursArray.cbegin(), cityNeighboursArray.cend(), std::back_inserter(model.mCityNeighbours), [](const QJsonValue &value) {
        return value.toString();
    });

    const QJsonArray &settlementNeighboursArray = localityObject.value("settlement-neighbours").toArray();
    model.mSettlementNeighbours.clear();
    std::transform(settlementNeighboursArray.cbegin(), settlementNeighboursArray.cend(), std::back_inserter(model.mSettlementNeighbours), [](const QJsonValue &value) {
        return value.toString();
    });

    const QJsonArray &villageNeighboursArray = localityObject.value("village-neighbours").toArray();
    model.mVillageNeighbours.clear();
    std::transform(villageNeighboursArray.cbegin(), villageNeighboursArray.cend(), std::back_inserter(model.mVillageNeighbours), [](const QJsonValue &value) {
        return value.toString();
    });
}
