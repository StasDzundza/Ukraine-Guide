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
    QVector<LocalityListEntity> getLocalitiesFromRoute(QString routeName);

    // write methods
    void saveFavoriteLocalities(LocalityListModel& favoriteLocalities);

private:
    QVector<LocalityListEntity> getSpecificLocalitiesList(const QStringList &keyNames) const;
    LocalityListEntity createLocalityListEntity(const QString &keyName) const;

    QJsonObject mLocalitiesObject;
};
