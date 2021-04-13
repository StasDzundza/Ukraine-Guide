#include <application.h>

Application::Application(QObject *parent): QObject(parent), mCurrentLocalityModel(this) {
    QQmlEngine::setObjectOwnership(&mCurrentLocalityModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mAllLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);
    QQmlEngine::setObjectOwnership(&mFavoriteLocalitiesListModel, QQmlEngine::ObjectOwnership::CppOwnership);

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
   // TODO check if locality is in favorite list and set corresponding property
   emit currentLocalityModelChanged(&mCurrentLocalityModel);
}

Application::~Application() {
    // TODO write favorite localities to file
    // TODO write routes to file
}
