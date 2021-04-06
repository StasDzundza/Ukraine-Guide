#pragma once

#include <QQmlEngine>

#include "locality_data_provider.h"
#include "locality_model.h"

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);

    // properties
    Q_PROPERTY(LocalityModel *currentLocalityModel READ getCurrentLocalityModel NOTIFY currentLocalityModelChanged)
    LocalityModel *getCurrentLocalityModel();
    Q_SIGNAL void currentLocalityModelChanged(LocalityModel *);

    // qml invokable methods
    Q_INVOKABLE void loadLocalityModel(const QString &localityKeyName);

private:
    LocalityModel mCurrentLocalityModel;
    LocalityDataProvider mLocalityDataProvider;
};
