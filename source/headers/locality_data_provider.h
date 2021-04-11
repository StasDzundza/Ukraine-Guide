#pragma once

#include <QJsonObject>

#include "locality_list_model.h"

class LocalityModel;

class LocalityDataProvider {
public:
    explicit LocalityDataProvider();

    void fillLocalityModel(const QString &keyName, LocalityModel &model) const;
    QVector<LocalityListEntity> getLocalitiesList() const;
private:
    QJsonObject mLocalitiesObject;
};
