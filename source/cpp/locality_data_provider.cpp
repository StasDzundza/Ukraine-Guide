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
static const QString FAVORITE_LOCALITIES_JSON_PATH = "favorite_localities.json";
static const QString ROUTES_JSON_PATH = "routes.json";
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
    // main info
    model.mShortInfo = getLocalityShortDescription(keyName);
    model.mKeyName = keyName;
    model.mEngName = localityObject.value("engName").toString("");
    model.mUkrName = localityObject.value("ukrName").toString("");
    model.mPopulation = localityObject.value("population").toInt(0);
    model.mArea = localityObject.value("area").toDouble(0);
    model.mOblast = localityObject.value("oblast").toString("");
    model.mRegion = localityObject.value("region").toString("");
    model.mFoundationDate = localityObject.value("foundationDate").toString("");
    model.mMoreInfoUrl = localityObject.value("moreInfoUrl").toString("");

    // type
    const QString &localityType = localityObject.value("type").toString("city");
    if (localityType == "city"){
        model.mType = LocalityType::CITY;
    } else if (localityType == "settlement") {
        model.mType = LocalityType::SETTLEMENT;
    } else {
        model.mType = LocalityType::VILLAGE;
    }

    // coordinates
    const QJsonArray &coordinatesArray = localityObject.value("coordinates").toArray();
    model.mCoordinates = {coordinatesArray.at(0).toDouble(0), coordinatesArray.at(1).toDouble(0)};

    // neighbours
    const QJsonArray &cityNeighboursArray = localityObject.value("neighbours").toArray();
    model.mNeighbours.clear();
    std::transform(cityNeighboursArray.cbegin(), cityNeighboursArray.cend(), std::back_inserter(model.mNeighbours), [](const QJsonValue &value) {
        return value.toString();
    });

    // establishments
    model.mEstablishmentsListModel.resetList(getEstablishmentsList(localityObject.value("topEspablishments").toArray()));

    // preview images
    const QJsonArray &previewImagesArray = localityObject.value("images").toArray();
    model.mPreviewImages.clear();
    std::transform(previewImagesArray.cbegin(), previewImagesArray.cend(), std::back_inserter(model.mPreviewImages),
                   [&keyName](const QJsonValue &value) {
        return "qrc:/app_data/localities_data/" + keyName + "/" + value.toString();
    });
}

QVector<LocalityListEntity> LocalityDataProvider::getLocalitiesList() const {
    return getSpecificLocalitiesList(mLocalitiesObject.keys());
}

QVector<LocalityListEntity> LocalityDataProvider::getFavoritesList() const {
    // read json file
    QFile fin(FAVORITE_LOCALITIES_JSON_PATH);
    if (fin.open(QIODevice::ReadOnly)) {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fin.readAll(), &parseError);
        Q_ASSERT(parseError.error == QJsonParseError::NoError);

        // parse json doc
        QVariantList favoriteLocalities = jsonDoc.object().value(QStringLiteral("favorite_localities")).toArray().toVariantList();
        QStringList favoriteLocalitiesKeys;
        std::transform(favoriteLocalities.begin(), favoriteLocalities.end(), std::back_inserter(favoriteLocalitiesKeys),
                       [](const QVariant &variant){
            return variant.toString();
        });
        return getSpecificLocalitiesList(favoriteLocalitiesKeys);
    } else {
        return {};
    }
}

QVector<LocalityListEntity> LocalityDataProvider::getSpecificLocalitiesList(const QStringList &keyNames) const{
    QVector<LocalityListEntity> localitiesList(keyNames.size());
    size_t i = 0;
    foreach(const QString& key, keyNames) {
        localitiesList[i++] = createLocalityListEntity(key);
    }
    return localitiesList;
}

QVector<EstablishmentsListEntity> LocalityDataProvider::getEstablishmentsList(const QJsonArray &establishmentsArray) const {
    QVector<EstablishmentsListEntity> establishmentsList;
    std::transform(establishmentsArray.cbegin(), establishmentsArray.cend(), std::back_inserter(establishmentsList), [](const QJsonValue &value) -> EstablishmentsListEntity {
        const QJsonObject &establishmentObject = value.toObject();
        return {
            establishmentObject.value("ukrName").toString(),
                    establishmentObject.value("engName").toString(),
                    establishmentObject.value("type").toString(),
                    establishmentObject.value("moreInfoUrl").toString()
        };
    });
    return establishmentsList;
}

QString LocalityDataProvider::getLocalityShortDescription(const QString &keyName) const {
    QFile file(":/app_data/localities_data/" + keyName + "/description.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        return QStringLiteral("Помилка читання");
    }
    QTextStream in(&file);
    QString result = in.readAll();
    file.close();
    return result;
}

QStringList LocalityDataProvider::getRoutesList() const {
    // read json file
    QFile fin(ROUTES_JSON_PATH);
    if (fin.open(QIODevice::ReadOnly)) {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fin.readAll(), &parseError);
        Q_ASSERT(parseError.error == QJsonParseError::NoError);

        // parse json doc
        QVariantList routes = jsonDoc.object().value(QStringLiteral("routes")).toArray().toVariantList();
        QStringList routeNames;
        std::transform(routes.begin(), routes.end(), std::back_inserter(routeNames),
                       [](const QVariant &variant){
            return variant.toString();
        });
        return routeNames;
    } else {
        return {};
    }
}

QVector<LocalityListEntity> LocalityDataProvider::getLocalitiesFromRoute(const QString &routeName) {
    const QString fileName = routeNameToFileName(routeName);
    QFile fin(fileName);
    if (fin.open(QIODevice::ReadOnly)) {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(fin.readAll(), &parseError);
        Q_ASSERT(parseError.error == QJsonParseError::NoError);

        // parse json doc
        QVariantList localities = jsonDoc.object().value(QStringLiteral("route")).toArray().toVariantList();
        QStringList localityKeyNames;
        std::transform(localities.begin(), localities.end(), std::back_inserter(localityKeyNames),
                       [](const QVariant &variant){
            return variant.toString();
        });
        QVector<LocalityListEntity> result(localityKeyNames.size());
        size_t i = 0;
        for (const QString &keyName: localityKeyNames) {
            result[i++] = createLocalityListEntity(keyName);
        }
        return result;
    } else {
        return {};
    }
}

LocalityListEntity LocalityDataProvider::createLocalityListEntity(const QString &keyName) const{
    const QJsonObject &localityObject = mLocalitiesObject.value(keyName).toObject();
    return {keyName,
                localityObject.value("ukrName").toString(),
                localityObject.value("engName").toString(),
                localityObject.value("type").toString(),
                localityObject.value("area").toDouble(),
                localityObject.value("population").toInt(),
                localityObject.value("oblast").toString()
    };
}

void LocalityDataProvider::saveFavoriteLocalities(const QStringList &favoriteLocalities) {
    saveData(FAVORITE_LOCALITIES_JSON_PATH, QStringLiteral("favorite_localities"), favoriteLocalities);
}

void LocalityDataProvider::saveRoute(const QString &routeName, const QStringList &localities) const {
    saveData(routeNameToFileName(routeName), QStringLiteral("route"), localities);
}

void LocalityDataProvider::removeRoute(const QString &routeName) const {
    QFile file (routeNameToFileName(routeName));
    file.remove();
}

void LocalityDataProvider::saveRoutesList(const QStringList &routes) const {
    saveData(ROUTES_JSON_PATH, QStringLiteral("routes"), routes);
}

QString LocalityDataProvider::routeNameToFileName(const QString &routeName) const {
    QString res = routeName;
    return res.replace(' ', '_').toLower() + QStringLiteral(".json");
}

void LocalityDataProvider::saveData(const QString &fileName, const QString &arrayName, const QStringList &keys) const {
    // create json doc
    QJsonDocument jsonDoc;
    QJsonObject rootObject;
    QJsonArray array;
    for(int i = 0; i < keys.size(); i++) {
        array.append(keys.at(i));
    }
    rootObject.insert(arrayName, array);
    jsonDoc.setObject(rootObject);

    // write to file
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(jsonDoc.toJson());
}
