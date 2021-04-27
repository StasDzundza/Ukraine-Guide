#pragma once

#include <QJsonObject>

#include "locality_list_model.h"

class LocalityModel;

class LocalityDataProvider {
public:
    explicit LocalityDataProvider();

    // read methods
    void fillLocalityModel(const QString &keyName, LocalityModel &model) const;
    QVector<LocalityListEntity> getLocalitiesList() const;
    QVector<LocalityListEntity> getFavoritesList() const;
    QVector<EstablishmentsListEntity> getEstablishmentsList(const QJsonArray &establishmentsArray) const;
    QString getLocalityShortDescription(const QString &keyName) const;
    QStringList getRoutesList() const;
    QVector<LocalityListEntity> getLocalitiesFromRoute(const QString &routeName);

    // write methods
    void saveFavoriteLocalities(const QStringList &favoriteLocalities);
    void saveRoute(const QString &routeName, const QStringList &localities) const;
    void removeRoute(const QString &routeName) const;
    void saveRoutesList(const QStringList &routes) const;

private:
    QVector<LocalityListEntity> getSpecificLocalitiesList(const QStringList &keyNames) const;
    LocalityListEntity createLocalityListEntity(const QString &keyName) const;
    QString routeNameToFileName(const QString &routeName) const;
    void saveData(const QString &fileName, const QString &arrayName, const QStringList &keys) const;

    QJsonObject mLocalitiesObject;
};
