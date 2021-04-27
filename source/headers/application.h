#pragma once

#include <QQmlEngine>

#include "locality_data_provider.h"
#include "locality_model.h"
#include "routes_list_model.h"

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);
    ~Application();

    // properties
    Q_PROPERTY(LocalityModel *currentLocalityModel READ getCurrentLocalityModel NOTIFY currentLocalityModelChanged)
    LocalityModel *getCurrentLocalityModel();
    Q_SIGNAL void currentLocalityModelChanged();

    Q_PROPERTY(LocalityListModel *localityListModel READ getLocalityListModel NOTIFY localityListModelChanged)
    LocalityListModel *getLocalityListModel();
    Q_SIGNAL void localityListModelChanged();

    Q_PROPERTY(LocalityListModel *favoriteFocalityListModel READ getFavoriteLocalityListModel NOTIFY favoriteLocalityListModelChanged)
    LocalityListModel *getFavoriteLocalityListModel();
    Q_SIGNAL void favoriteLocalityListModelChanged();

    Q_PROPERTY(LocalityListModel *currentRouteListModel READ getCurrentRouteListModel NOTIFY currentRouteListModelChanged)
    LocalityListModel *getCurrentRouteListModel();
    Q_SIGNAL void currentRouteListModelChanged();

    Q_PROPERTY(RoutesListModel *routesListModel READ getRoutesListModel NOTIFY routesListModelChanged)
    RoutesListModel *getRoutesListModel();
    Q_SIGNAL void routesListModelChanged();

    // qml invokable methods
    Q_INVOKABLE void loadLocalityModel(const QString &localityKeyName);
    Q_INVOKABLE void loadCurrentRoute(const QString &routeName);
    Q_INVOKABLE void createRoute(const QString &routeName, const QStringList &localities);
    Q_INVOKABLE void saveCurrentRoute();
    Q_INVOKABLE void removeRoute(const int index);

    // slots
    Q_SLOT void onFavoriteLocalityAdded(const LocalityListEntity &locality);
    Q_SLOT void onFavoriteLocalityRemoved(const LocalityListEntity &locality);

private:
    void setupConnections();

    LocalityDataProvider mLocalityDataProvider;
    LocalityListModel mAllLocalitiesListModel;
    LocalityListModel mFavoriteLocalitiesListModel;
    LocalityListModel mCurrentRouteListModel;
    LocalityModel mCurrentLocalityModel;
    RoutesListModel mRoutesListModel;
};
