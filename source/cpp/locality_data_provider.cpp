#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <algorithm>

#include "locality_data_provider.h"
#include "locality_model.h"

namespace  {
static const QString LOCALITY_JSON_PATH = ":/app_data/localities.json";
static const QString FAVORITE_LOCALITIES_JSON_PATH = ":/todo.json";
static const QString ROUTES_JSON_PATH = ":/todo.json";
}

LocalityDataProvider::LocalityDataProvider() {
    QJsonParseError parseError;
    QFile fin(LOCALITY_JSON_PATH);
    fin.open(QIODevice::ReadOnly);
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fin.readAll(), &parseError);
    Q_ASSERT(parseError.error == QJsonParseError::NoError);
    mLocalitiesObject = jsonDoc.object();
}

void LocalityDataProvider::fillLocalityModel(const QString &keyName, LocalityModel &model) const {
    const QJsonObject &localityObject = mLocalitiesObject.value(keyName).toObject();
    model.mKeyName = keyName;
    model.mEngName = localityObject.value("engName").toString("");
    model.mUkrName = localityObject.value("ukrName").toString("");
    model.mPopulation = localityObject.value("population").toInt(0);
    model.mArea = localityObject.value("area").toDouble(0);
    model.mOblast = localityObject.value("oblast").toString("");
    model.mRegion = localityObject.value("region").toString("");
    const QString &localityType = localityObject.value("type").toString("city");
    if (localityType == "city"){
        model.mType = LocalityType::CITY;
    } else if (localityType == "settlement") {
        model.mType = LocalityType::SETTLEMENT;
    } else {
        model.mType = LocalityType::VILLAGE;
    }
    const QJsonArray &coordinatesArray = localityObject.value("coordinates").toArray();
    model.mCoordinates = {coordinatesArray.at(0).toDouble(0), coordinatesArray.at(1).toDouble(0)};

    const QJsonArray &cityNeighboursArray = localityObject.value("neighbours").toArray();
    model.mNeighbours.clear();
    std::transform(cityNeighboursArray.cbegin(), cityNeighboursArray.cend(), std::back_inserter(model.mNeighbours), [](const QJsonValue &value) {
        return value.toString();
    });
}

QVector<LocalityListEntity> LocalityDataProvider::getLocalitiesList() const {
    QVector<LocalityListEntity> localitiesList(mLocalitiesObject.keys().size());
    size_t i = 0;
    foreach(const QString& key, mLocalitiesObject.keys()) {
        const QJsonObject &localityObject = mLocalitiesObject.value(key).toObject();
        localitiesList[i++] = {key, localityObject.value("ukrName").toString(), localityObject.value("engName").toString(),
                               localityObject.value("type").toString()};
    }
    return localitiesList;
}
