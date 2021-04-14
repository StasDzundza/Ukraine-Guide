#pragma once

#include <QQmlEngine>

#include "locality_data_provider.h"
#include "locality_model.h"

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

    Q_PROPERTY(LocalityListModel *favoriteFocalityListModel READ getFavoriteLocalityListModel NOTIFY favoriteLocalityListModelChanged)
    LocalityListModel *getFavoriteLocalityListModel();
    Q_SIGNAL void favoriteLocalityListModelChanged(LocalityListModel *);

    // qml invokable methods
    Q_INVOKABLE void loadLocalityModel(const QString &localityKeyName);

    // slots
    Q_SLOT void onFavoriteLocalityAdded(const LocalityListEntity &locality);
    Q_SLOT void onFavoriteLocalityRemoved(const LocalityListEntity &locality);

private:
    void setupConnections();

    LocalityModel mCurrentLocalityModel;
    LocalityDataProvider mLocalityDataProvider;
    LocalityListModel mAllLocalitiesListModel;
    LocalityListModel mFavoriteLocalitiesListModel;
};
