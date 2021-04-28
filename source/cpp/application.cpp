#include <QDebug>

#include <application.h>

Application::Application(QObject *parent): QObject(parent),
        mAllLocalitiesListModel(this),
        mFavoriteLocalitiesListModel(this),
        mCurrentRouteListModel(this),
        mCurrentLocalityModel(this),
        mRoutesListModel(this) {
    QQmlEngine::setObjectOwnership(&mCurrentLocalityModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mAllLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mFavoriteLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mRoutesListModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mCurrentRouteListModel, QQmlEngine::ObjectOwnership::CppOwnership);

    setupConnections();

    mAllLocalitiesListModel.resetList(mLocalityDataProvider.getLocalitiesList());
    emit localityListModelChanged();

    mFavoriteLocalitiesListModel.resetList(mLocalityDataProvider.getFavoritesList());
    emit favoriteLocalityListModelChanged();

    mRoutesListModel.resetList(mLocalityDataProvider.getRoutesList());
    emit routesListModelChanged();
}

LocalityModel *Application::getCurrentLocalityModel() {
    return &mCurrentLocalityModel;
}

LocalityListModel *Application::getLocalityListModel() {
    return &mAllLocalitiesListModel;
}

LocalityListModel *Application::getFavoriteLocalityListModel() {
    return &mFavoriteLocalitiesListModel;
}

LocalityListModel *Application::getCurrentRouteListModel() {
    return &mCurrentRouteListModel;
}

RoutesListModel *Application::getRoutesListModel() {
    return &mRoutesListModel;
}

void Application::loadLocalityModel(const QString &localityKeyName) {
   mLocalityDataProvider.fillLocalityModel(localityKeyName, mCurrentLocalityModel);
   bool isFavorite = mFavoriteLocalitiesListModel.contains(mCurrentLocalityModel.getKeyName());
   mCurrentLocalityModel.setFavorite(isFavorite);
   mCurrentLocalityModel.allPropertiesChanged();
   emit currentLocalityModelChanged();
}

void Application::loadCurrentRoute(const QString &routeName) {
    mCurrentRouteListModel.resetList(mLocalityDataProvider.getLocalitiesFromRoute(routeName));
    mCurrentRouteListModel.setRouteName(routeName);
    emit currentRouteListModelChanged();
}

void Application::createRoute(const QString &routeName, const QStringList &localities) {
    mLocalityDataProvider.saveRoute(routeName, localities);
    mRoutesListModel.append(routeName);
    routesListModelChanged();
}

void Application::saveCurrentRoute() {
    mLocalityDataProvider.saveRoute(mCurrentRouteListModel.getRouteName(),
                                    mCurrentRouteListModel.getKeyNames());
}

void Application::removeRoute(const int index) {
    const QString &routeName = mRoutesListModel.getRoutesList().at(index);
    mRoutesListModel.remove(index);
    mLocalityDataProvider.removeRoute(routeName);
}

void Application::renameCurrentRoute(const QString &newName) {
    const QString oldRouteName = mCurrentRouteListModel.getRouteName();
    mCurrentRouteListModel.setRouteName(newName);
    mLocalityDataProvider.renameRoute(oldRouteName, newName);
    mRoutesListModel.renameRoute(oldRouteName, newName);
}

void Application::onFavoriteLocalityAdded(const LocalityListEntity &locality) {
    mFavoriteLocalitiesListModel.append(locality);
}

void Application::onFavoriteLocalityRemoved(const LocalityListEntity &locality) {
    mFavoriteLocalitiesListModel.remove(locality);
}

void Application::setupConnections() {
    QObject::connect(&mCurrentLocalityModel, &LocalityModel::favoriteLocalityAdded, this, &Application::onFavoriteLocalityAdded);
    QObject::connect(&mCurrentLocalityModel, &LocalityModel::favoriteLocalityRemoved, this, &Application::onFavoriteLocalityRemoved);
}

Application::~Application() {
    mLocalityDataProvider.saveFavoriteLocalities(mFavoriteLocalitiesListModel.getKeyNames());
    mLocalityDataProvider.saveRoutesList(mRoutesListModel.getRoutesList());
}
