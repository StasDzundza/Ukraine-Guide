#pragma once

#include <QQmlEngine>

#include "locality_data_provider.h"
#include "locality_model.h"
#include "locality_list_model.h"

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);
    ~Application();

    // properties
    Q_PROPERTY(LocalityModel *currentLocalityModel READ getCurrentLocalityModel NOTIFY currentLocalityModelChanged)
    LocalityModel *getCurrentLocalityModel();
    Q_SIGNAL void currentLocalityModelChanged(LocalityModel *);

    Q_PROPERTY(LocalityListModel *localityListModel READ getLocalityListModel NOTIFY localityListModelChanged)
    LocalityListModel *getLocalityListModel();
    Q_SIGNAL void localityListModelChanged(LocalityListModel *);

    // qml invokable methods
    Q_INVOKABLE void loadLocalityModel(const QString &localityKeyName);

private:
    LocalityModel mCurrentLocalityModel;
    LocalityDataProvider mLocalityDataProvider;
    LocalityListModel mLocalitiesListModel;
};
