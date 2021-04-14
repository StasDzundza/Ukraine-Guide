#include <QDebug>

#include <application.h>

Application::Application(QObject *parent): QObject(parent), mCurrentLocalityModel(this) {
    QQmlEngine::setObjectOwnership(&mCurrentLocalityModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mAllLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mFavoriteLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);

    setupConnections();

    mAllLocalitiesListModel.resetList(mLocalityDataProvider.getLocalitiesList());
    emit localityListModelChanged(&mAllLocalitiesListModel);

    // TODO read favorite localities from file
    // TODO read routes from file
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

void Application::loadLocalityModel(const QString &localityKeyName) {
   mLocalityDataProvider.fillLocalityModel(localityKeyName, mCurrentLocalityModel);
   bool isFavorite = mFavoriteLocalitiesListModel.contains(mCurrentLocalityModel.getKeyName());
   mCurrentLocalityModel.setFavorite(isFavorite);
   mCurrentLocalityModel.allPropertiesChanged();
   emit currentLocalityModelChanged(&mCurrentLocalityModel);
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
    // TODO write favorite localities to file
    // TODO write routes to file
}
