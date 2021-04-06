#pragma once

#include <QJsonObject>

class LocalityModel;

class LocalityDataProvider {
public:
    explicit LocalityDataProvider();

    void fillLocalityModel(const QString &keyName, LocalityModel &model);
private:
    QJsonObject mLocalitiesObject;
};
