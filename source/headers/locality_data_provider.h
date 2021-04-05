#pragma once

#include <QJsonObject>

class LocalityModel;

class LocalityDataProvider {
public:
    explicit LocalityDataProvider();

    void fillLocalityModel(LocalityModel &model);
private:
    QJsonObject mLocalitiesObject;
};
