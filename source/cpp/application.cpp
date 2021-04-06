#include <application.h>

Application::Application(QObject *parent): QObject(parent), mCurrentLocalityModel(this) {
    QQmlEngine::setObjectOwnership(&mCurrentLocalityModel, QQmlEngine::ObjectOwnership::CppOwnership);
}

LocalityModel *Application::getCurrentLocalityModel() {
    return &mCurrentLocalityModel;
}

void Application::loadLocalityModel(const QString &localityKeyName) {
   mLocalityDataProvider.fillLocalityModel(localityKeyName, mCurrentLocalityModel);
   currentLocalityModelChanged(&mCurrentLocalityModel);
}

Application::~Application() {

}
