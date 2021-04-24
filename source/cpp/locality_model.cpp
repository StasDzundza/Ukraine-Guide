#include <QQmlEngine>

#include "locality_model.h"

LocalityModel::LocalityModel(QObject *parent) : QObject(parent){
    QQmlEngine::setObjectOwnership(&mEstablishmentsListModel, QQmlEngine::ObjectOwnership::CppOwnership);
}

// properties
QString LocalityModel::getShortInfo() const { return mShortInfo; }

QString LocalityModel::getKeyName() const { return mKeyName; }

QString LocalityModel::getUkrName() const { return mUkrName; }

QString LocalityModel::getEngName() const { return mEngName; }

QString LocalityModel::getOblast() const { return mOblast; }

QString LocalityModel::getRegion() const { return mRegion; }

QString LocalityModel::getFoundationDate() const { return mFoundationDate; }

int LocalityModel::getPopulation() const { return mPopulation; }

float LocalityModel::getArea() const { return mArea; }

LocalityType::Type LocalityModel::getType() const { return mType.getType(); }

QPointF LocalityModel::getCoordinates() const { return mCoordinates; }

QVector<QString> LocalityModel::getPreviewImages() const { return mPreviewImages; }

int LocalityModel::getNumOfPreviewImages() const { return mPreviewImages.size(); }

bool LocalityModel::isFavorite() const { return mIsFavorite; }

void LocalityModel::setFavorite(const bool isFavorite) { mIsFavorite = isFavorite; }

QString LocalityModel::getMoreInfoUrl() const { return mMoreInfoUrl; }

EstablishmentsListModel *LocalityModel::getEstablishments() { return &mEstablishmentsListModel; }

//qml methods
void LocalityModel::changeFavoriteStatus() {
    mIsFavorite = !mIsFavorite;
    emit isFavoriteChanged();
    LocalityListEntity locality{mKeyName, mUkrName, mEngName, LocalityType::toString(mType), mArea, mPopulation};
    if (mIsFavorite) {
        emit favoriteLocalityAdded(locality);
    } else {
        emit favoriteLocalityRemoved(locality);
    }
}

void LocalityModel::declareQML() {
    qmlRegisterType<LocalityListModel>("com.UkraineGuide.LocalityModel", 1, 0, "LocalityModel");
}

void LocalityModel::allPropertiesChanged() {
    emit shortInfoChanged();
    emit keyNameChanged();
    emit ukrNameChanged();
    emit engNameChanged();
    emit oblastChanged();
    emit regionChanged();
    emit populationChanged();
    emit areaChanged();
    emit typeChanged();
    emit isFavoriteChanged();
    emit moreInfoUrlChanged();
    emit coordinatesChanged();
    emit establishmentsChanged();
    emit previewImagesChanged();
    emit numOfPreviewImagesChanged();
}
